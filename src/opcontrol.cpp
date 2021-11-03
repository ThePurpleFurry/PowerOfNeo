#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/apix.h"
#include "Global.hpp"

//#define true false
//#define false true

#define TheStockMarketCrashOf1929 pros::E_MOTOR_GEARSET_18       //"who wants some jambalaya!"
#define TheIrishPotatoFamineOf1845 pros::E_MOTOR_ENCODER_DEGREES   //"I havent been that entertained since the stock market crash of 1929! haha, so many orphans"

#define dou double
//Config section


//There was a time when this was the most complicated code in the entire project...
   //But that was before I added a BASIC interpreter to it...


pros::ADIDigitalIn rightLimit (1);
pros::ADIDigitalIn leftLimit  (2);


//Settings and internal variables
bool isTestMode = true;  //If should run tasks such as autonomous, AtomicHelp+, or any other debug functions
int  deadzonestrf  = 10;  //Deadzone on Strafe direction
int   deadzoneleft  = 5;  //Deadzone on Left joystick
int   deadzonerght  = 5;  //Deadzone on right joystick
int    loop     =    40;  //How many cycles should run before updating controller screens, too fast will make the screen mostly white, too slow will provide out of date info
dou backspeedtoflap = 1;  //Divider for flaps speed while backing up
dou positionangmult = 0.0001;  //How much to multiply the flap speed based on the angle of the lift
int positionmiddle= 750;  //Where the middle of the lift's swing is
bool pushterminaltoserialdefault = false; //What value the resetterminalout should go to, true for posting all terminal events to serial terminal
bool pushterminaltoserial = pushterminaltoserialdefault;

bool doOpLockout= false;  //internal variable - If AtomicHelp+ is running, disables this file's code to prevent overriding
int positionmult    = 0;  //internal variable - Multiplies the speed of the flaps based on current angle to compensate for angular speed changes
bool shiftmode  = false;  //internal variable - If the controls are divided in half for reduced speed

          /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=/
         / /MHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHMHM/ /
        / /H/      \===/      \#hdddd/    ,_________/#dH/             /#+H/    ,______,    /# /
       / /M/    /#\     /#\    \#ddy/    /##########HMH/__,     ,____/#+M/    /#^#^#^/    /# /
      / /H/    /#M/    /#H/    /#dd/    /-----dddddddddMH/     /#####+MH/    /#MHMHM/    /# /
     / /M/    /#H/    /#M/    /#ds/   ,______/#*+dddddMH/     /#+ddddHM/    _______     /# /
    / /H/    /#M/    /#H/    /#dd/   /######+-dddddddMH/     /#+ddddMH/    /######/    /# /
   / /M/    /#H/    /#M/    /#do/   /-------ddddddddMH/     /#+ddddHM/    /#***HM/    /# /
  / /H/____/#M/____/#H/____/#dd/___________/#ddddddMH/_____/#+ddddMH/____/#***MH/____/# /
 / /#################################################################################/ /
/=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|
|#          R   --   O   --   B   --   O  --   T   --   I   --   C   --   S          #|
\*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void opcontrol() {
	doGifScreen = false;
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Controller slave(pros::E_CONTROLLER_PARTNER);
	pros::Motor left_mtr  (1, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
	pros::Motor right_mtr (2, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
	pros::Motor strafemtr (3, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);strafemtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::Motor lift_mtr1 (6, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);lift_mtr1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::Motor lift_mtr2 (7, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);lift_mtr2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	pros::Motor scoop1 (9, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);scoop1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::Motor scoop2 (10, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);scoop2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "User Control-Fast|");




//Main While loop
	while (true) {
		while(doOpLockout){}/*Disable opcontrols while AtomicHelp+ is running*/
  //Get values of driving joysticks
		int joyl = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);if (abs(joyl) < deadzoneleft){joyl = 0;}//deadzone
		int joyr = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);if (abs(joyr) < deadzonerght){joyr = 0;}//deadzone
		int josl = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);double absjosl = std::abs(josl);if (absjosl < deadzonestrf){josl = 0;}//make deadzone for strafing
  //Run AtomicHelp if Master-Y pressed
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) and isTestMode and !screenDecoOverride)AtomicHelp();
  //Divide speed if shifted speed enabled
		if(shiftmode){joyl = joyl/2; joyr = joyr/2; josl = josl/2;}

//Partner Controls Stuff
			int pjosl = slave.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);if (abs(pjosl) < deadzonestrf){pjosl = 0;}
			liftspeed = pjosl;
				leftZero = lift_mtr2.get_position();
				rightZero = lift_mtr1.get_position();
				//std::cout << leftZero << " | " << rightZero << "\n";
				char controltext[1024];
				std::string textraw = std::to_string((int)round(leftZero)) + " | " + std::to_string((int)round(rightZero)) + "                                         -";
				strcpy(controltext, textraw.c_str());
				//std::string controllertext =
				if(loop >= 50){
					pros::c::controller_set_text(pros::E_CONTROLLER_PARTNER, 1, 1, controltext);
					loop = 0;
				}
				loop++;


  //Flap Control
			int pjosr = slave.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);if (abs(pjosr) < deadzonestrf){pjosr = 0;}

    //Add drivermirror to flap controls
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) or master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
				//ToDo: postionmult
				positionmult = (positionmiddle - leftZero)*positionangmult;


				pjosr = (pjosr + ((joyl/backspeedtoflap)+positionmult));
			}
    //Actually move the scoops
				scoop1.move(pjosr/1.5);
				scoop2.move(pjosr/1.5);



//Driving Control
		double left = joyr - joyl;        //Do math to get Arcade steering
		double right = joyr + joyl;
		left_mtr.move(left/1.5);           //Set motor speeds
		right_mtr.move(right/1.5);
		strafemtr.move(josl);

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) and isTestMode){std::cout << "Pushed autonomous button\n";autonomous();doGifScreen = false;pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "User Control-Fast|");shiftmode = false;}//Start autonomous code if digital A has been pressed

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			while(master.get_digital(pros::E_CONTROLLER_DIGITAL_X));
			if (shiftmode){
				shiftmode = false;
				pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "User Control-Fast       |");
			}else{
				shiftmode = true;
				pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "User Control-Slow       |");
			}
    }



		pros::delay(50);                //Wait a few milliseconds to save processor cycles
	}
}
