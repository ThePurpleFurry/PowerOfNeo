#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/apix.h"
#include <utility>
//Eventually put the main includes in the Globals file
#include "Global.hpp"
#define TheStockMarketCrashOf1929 pros::E_MOTOR_GEARSET_18       //"who wants some jambalaya!"
#define TheIrishPotatoFamineOf1845 pros::E_MOTOR_ENCODER_DEGREES
int autonomousFullSpeed   = 100;
int autonomousStrafeSpeed = 100;
int flapmovespeed = 60;
int movespeed = 120;
bool doGifOnAutonomous = true;
std::string ScriptOutput;
int instructioncount;
std::string insertcommand;
#define getD get_analog
#define please .get_digital

//void AtomicInterruptHandler(){} //-Planned Feature, probably not going to be used
void addCom(std::string command){
  if (not(command == "- -- --- -- -")){
  instructioncount = instructioncount + 10;
  insertcommand = std::to_string(instructioncount)+" "+command+"\\n\\\n";
}else{insertcommand = command;}
  ScriptOutput = ScriptOutput + insertcommand;
}

void resetAtomic(){
  ScriptOutput = "-=-=-=-=-=-=-=-\n";
}

void saveAtomic(){
  dumpToSD(ScriptOutput);
  ScriptOutput = "-=-=-=-=-=-=-=-\n";
}


//This whole file is going to be a trainwreck, starting off with naming the controller...
void AtomicHelp(){
  resetAtomic();
  pushterminaltoserial = true;
  prevscreen = screenTab;
  screenTab = "Atomichelp";
  //So, something interesting, this isnt running until the first instruction when it comes to serial stuff...
  std::cout << "attempting to boot AtomicHelp+\n";
  screen::AtomicHelper();
  doOpLockout = true;
  pros::Controller daddy(pros::E_CONTROLLER_MASTER);
  pros::Controller slave(pros::E_CONTROLLER_PARTNER);
  //"Even your code calls you daddy" -Jade R 2019

	pros::Motor left_mtr  (1, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
	pros::Motor right_mtr (2, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
	pros::Motor strafemtr (3, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);strafemtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::Motor lift_mtr1 (6, TheStockMarketCrashOf1929, true , TheIrishPotatoFamineOf1845);lift_mtr1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::Motor lift_mtr2 (7, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);lift_mtr2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Motor scoop1 (9, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
  pros::Motor scoop2 (10, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);
  //Function to get values from a user doing things
  int startTime;
  int scoopTime;
  int donetime;
  int scoopdone;
  pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "Atomic Help     |");
  screen::terminalPush(terminal, "Started AtomicHelper+ Successfully");
  while(true){

    left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);liftspeed = 0;
    int joyLY = daddy.getD(pros::E_CONTROLLER_ANALOG_LEFT_Y );if (abs(joyLY) < 15){joyLY = 0;}//deadzone
		int joyRX = daddy.getD(pros::E_CONTROLLER_ANALOG_RIGHT_X);if (abs(joyRX) < 15){joyRX = 0;}//deadzone
		int joyLX = daddy.getD(pros::E_CONTROLLER_ANALOG_LEFT_X );if (abs(joyLX) < 15){joyLX = 0;}//make deadzone for strafing
    int patLY = slave.getD(pros::E_CONTROLLER_ANALOG_LEFT_Y );if (abs(joyLX) < 15){joyLX = 0;}

    //Turn and drive controls
    if(joyLY>0){startTime=pros::c::millis();while(daddy.getD(pros::E_CONTROLLER_ANALOG_LEFT_Y )> 15){/*Forward    */left_mtr.move(-1*autonomousFullSpeed/1.5 );right_mtr.move(autonomousFullSpeed/1.5   );strafemtr.move(0           );pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output Forward :" + std::to_string(donetime));addCom("Forward "+std::to_string(donetime)); left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);}
    if(joyLY<0){startTime=pros::c::millis();while(daddy.getD(pros::E_CONTROLLER_ANALOG_LEFT_Y )<-15){/*Backward   */left_mtr.move(autonomousFullSpeed/1.5    );right_mtr.move(-1*autonomousFullSpeed/1.5);strafemtr.move(0           );pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output Backward:" + std::to_string(donetime));addCom("Back "+std::to_string(donetime));  left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);}
    if(joyRX>0){startTime=pros::c::millis();while(daddy.getD(pros::E_CONTROLLER_ANALOG_RIGHT_X)> 15){/*TurnRight  */left_mtr.move(autonomousFullSpeed/1.5    );right_mtr.move( autonomousFullSpeed/1.5  );strafemtr.move(0           );pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output TurnRigt:" + std::to_string(donetime));addCom("Right "+std::to_string(donetime));  left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);}
    if(joyRX<0){startTime=pros::c::millis();while(daddy.getD(pros::E_CONTROLLER_ANALOG_RIGHT_X)<-15){/*TurnLeft   */left_mtr.move(-autonomousFullSpeed/1.5   );right_mtr.move( -autonomousFullSpeed/1.5 );strafemtr.move(0           );pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output TurnLeft:" + std::to_string(donetime));addCom("Left "+std::to_string(donetime));  left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);}
    //Strafe Controls, dont reccomend using them since the strafe wheel is so iffy
  //if(joyLX>0){startTime=pros::c::millis();while(daddy.getD(pros::E_CONTROLLER_ANALOG_LEFT_X )> 15){/*StrafeRight*/left_mtr.move(0           );right_mtr.move(0          );strafemtr.move(   autonomousStrafeSpeed);pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output StrfRigh:" + std::to_string(donetime)); left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);}
  //if(joyLX<0){startTime=pros::c::millis();while(daddy.getD(pros::E_CONTROLLER_ANALOG_LEFT_X )<-15){/*StrafeLeft */left_mtr.move(0           );right_mtr.move(0          );strafemtr.move(-1*autonomousStrafeSpeed);pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output:StrfLeft:" + std::to_string(donetime)); left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);}
    //Lift controls
/**/if(patLY>0){startTime=pros::c::millis();while(slave.getD(pros::E_CONTROLLER_ANALOG_LEFT_Y )> 15){/*Lift shit  */liftspeed =    movespeed;pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output:SetLift: "  + std::to_string(movespeed) + " time:" + std::to_string(donetime));addCom("SetLift " +std::to_string(movespeed)+" "+std::to_string(donetime));  liftspeed = 0;}
/**/if(patLY<0){startTime=pros::c::millis();while(slave.getD(pros::E_CONTROLLER_ANALOG_LEFT_Y )<-15){/*UnLift shit*/liftspeed = -1*movespeed;pros::delay(50);}donetime = pros::c::millis()-startTime; screen::terminalPush(terminal, "Output:SetLift:-" + std::to_string(movespeed) + " time:" + std::to_string(donetime)); addCom("SetLift -"+std::to_string(movespeed)+" "+std::to_string(donetime));  liftspeed = 0;}
    //Flap Controls and exit button
    if(slave please(pros::E_CONTROLLER_DIGITAL_X)){scoopdone = pros::c::millis()-scoopTime;while(slave please(pros::E_CONTROLLER_DIGITAL_X)){}/*Fill with set flaps*/scoop1.move(0);scoop2.move(0);            screen::terminalPush(terminal, "Output:Flaps:Off :: " + std::to_string(scoopdone) + " :: ms");addCom("Wait "+std::to_string(scoopdone)+"\\n\\\n[addnum] FlapOff"); }
    if(slave please(pros::E_CONTROLLER_DIGITAL_A)){scoopTime=pros::c::millis();while(slave please(pros::E_CONTROLLER_DIGITAL_A)){}/*Fill with set flasp*/scoop1.move(flapmovespeed);scoop2.move(flapmovespeed);screen::terminalPush(terminal, "Output:Flaps:On  :: " + std::to_string(flapmovespeed));       addCom("FlapOn " +std::to_string(flapmovespeed)); }
    if(slave please(pros::E_CONTROLLER_DIGITAL_Y)){scoopTime=pros::c::millis();while(slave please(pros::E_CONTROLLER_DIGITAL_A)){}/*Fill with set flasp*/scoop1.move(-1*flapmovespeed);scoop2.move(-1*flapmovespeed);screen::terminalPush(terminal, "Output:Flaps:Rev ::" + std::to_string(-1*flapmovespeed));addCom("FlapOn -"+std::to_string(flapmovespeed)); }
    if(daddy please(pros::E_CONTROLLER_DIGITAL_B)){doOpLockout=false;pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "User Control            |");pushterminaltoserial = pushterminaltoserialdefault;screenTab = prevscreen;screen::returnScreen(screenTab);break;} //Use this to instantly escape this program helper
    //left_mtr.move(0);right_mtr.move(0);strafemtr.move(0);
    //std::cout << "Output:" << donetime << "\n";

    pros::delay(100);}
}

void dumpToSD(std::string commandlist){
    int n = commandlist.length();
    char dumpfilelist[n + 1];
    strcpy(dumpfilelist, commandlist.c_str());

  FILE* usd_file_write = fopen("/usd/VixenBASICOutput.txt", "a");
  fputs(dumpfilelist, usd_file_write);
  fclose(usd_file_write);
  resetAtomic();
}

void AtomicInsertion(int interruptcode=0){
  //ToDo like the rest of my code. but this is actually kinda important since there is no other way to insert button presses
}
