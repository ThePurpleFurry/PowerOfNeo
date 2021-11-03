#include "api.h"
#include "main.h"
#include <vector>
#include <cstring>
#include <regex>
#include <map>
#include <utility>
#include "okapi/api.hpp"
#include "Global.hpp"


//std::string autoselected = "blu1";


#define shoudIUseTheWeirdBasicInterpreterAndDieALittleInsideBecauseIAmTooLazyToWriteABasicScriptThatDoesAnythingImportant true

//RWM Helper
 //Forward 1 ft =
 //Forward 1 inch =
 //Turn 01 degrees =
 //Turn 90 degrees =

 //ToDo: Make a module for using Real World Measurements easily without having to deal with the OKApi
//End of RWM Helper
//Setup needed for movement functions
#define gear pros::E_MOTOR_GEARSET_18
#define encodeg pros::E_MOTOR_ENCODER_DEGREES
#define TheStockMarketCrashOf1929 pros::E_MOTOR_GEARSET_18       //"who wants some jambalaya!"
#define TheIrishPotatoFamineOf1845 pros::E_MOTOR_ENCODER_DEGREES

pros::Motor left_mtr (1, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
pros::Motor right_mtr (2, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);
pros::Motor strafemtr (3, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
pros::Motor lift_mtr1 (6, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);
pros::Motor lift_mtr2 (7, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
pros::Motor scoop1 (9, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
pros::Motor scoop2 (10, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);
//pros::ADIDigitalIn rightLimit (1);
//pros::ADIDigitalIn leftLimit  (2);




namespace scmo{

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


//Robot supporting variant of VIXEN BASIC.
 //Eventually going to be ported to 6502 Assembly probably

//Good luck figuring out how this file does stuff.
 //Even I had trouble figuring out what I was doing to make it work while writing it.

void aNormalScriptThatLiddleWillUnderstandAndCanFigureOutWhereItIsWithAVisionSensor(std::string auton = "gen1"){

}

#define maxCommandLenght 201   //Maximum length of command area
#define nextlineTerm "-NULL-"  //What to be used as a skipline string
#define debugOn true           //Can be true/false or 1/0, some extra printlines
#define escapetovariable "/-%" //What the code should use internally to define a string as a variable


//==================//
// Output Functions //
//==================//
    //For easier porting.
  //===========================================================================//
  void printTerminal(std::string printext){
    //Where to send strings to be pushed to terminal
    screen::terminalPush(terminal, printext);
    std::cout << printext;
  }
  void terminalFunction(int instruction){
    //Where to send special interactions such as clear screen and vram poking
    //screen::terminalFunction(instruction);
  }
  void forward(int milliseconds = 1000){
        left_mtr.move(-1*autonomousFullSpeed/1.5);           //Set motor speeds
        right_mtr.move(autonomousFullSpeed/1.5);
        strafemtr.move(0);
      pros::delay(milliseconds);
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(0);
  }
  void backward(int milliseconds = 1000){
        left_mtr.move(autonomousFullSpeed/1.5);           //Set motor speeds
        right_mtr.move(-1*autonomousFullSpeed/1.5);
        strafemtr.move(0);
      pros::delay(milliseconds);
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(0);
  }
  void left(int milliseconds = 1000){
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(-1*autonomousStrafeSpeed);
      pros::delay(milliseconds);
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(0);
  }
  void right(int milliseconds = 1000){
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(autonomousStrafeSpeed);
      pros::delay(milliseconds);
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(0);
  }
  void turnleft(int milliseconds = 1000){
        left_mtr.move(-autonomousFullSpeed/1.5);           //Set motor speeds
        right_mtr.move(-autonomousFullSpeed/1.5);
        strafemtr.move(0);
      pros::delay(milliseconds);
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(0);
  }
  void turnright(int milliseconds = 1000){
        left_mtr.move(autonomousFullSpeed/1.5);           //Set motor speeds
        right_mtr.move(autonomousFullSpeed/1.5);
        strafemtr.move(0);
      pros::delay(milliseconds);
        left_mtr.move(0);           //Set motor speeds
        right_mtr.move(0);
        strafemtr.move(0);
  }
  void setflap(int speed = 0){
    scoop1.move(speed);
    scoop2.move(speed);
  }
  void setlift(int speed = 0, int time = 250){
    liftspeed = speed;
    pros::delay(time);
    liftspeed = 0;
  }
  void raiselift(int milliseconds = 1000){
        //What to do when raiselift command used
  }
  void lowerlift(int milliseconds = 1000){
        //What to do when lowerlift command used
  }
  void unfold(int milliseconds = 1000){
    //Function to run as "unfolding" the bot
      //Should not use millisecond variable
        //But the code was copy pasted and im too lazy to change it now
        //and I dont want to upset the legacy code when I dont have access to a compiler.
        //std::cout << "ran unfold function";
  }
  void motor(int milliseconds = 1000){
        //Used to move a motor without having to define it. Currently have no idea what to do.
  }
  void wait(int milliseconds = 1000){
        //WAIT command. missing from most BASIC's but is important in this version
        pros::delay(milliseconds);
  }
  void print(std::string text){
        //PRINT command to push a string to console(s)
        std::cout << text;
  }
  void gotoo(){
        std::cout << "!ERROR - ran goto function, this is a forloop function and should not be run.\n";
  }



//=====================================================================//
//  END OF EXTERNAL LINKING SECTION                                    //
//=====================================================================//


//===============//
// Variables     //
//=-=+=-=+=-=+=-=//

std::vector<std::string> linetokens;
std::map<int, std::vector<std::string>> commands;

  //Assistiant Functions
  //Split function with key
    std::vector<std::string> chop(std::string str, std::string c = "\\s+"){
        std::regex reg(c);
        std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> vec(iter, end);
        return vec;}

    std::map<int,std::vector<std::string>> tokenate(std::string str, std::string c = "\\s+"){
  //Fill the command memmory with nextline commands
      std::map<int, std::vector<std::string>> commands;
      std::vector<std::string> blankVector={nextlineTerm};
      for (int i=0; i<maxCommandLenght; i++) {
            commands.insert({i,blankVector});}
  //Get the commands vector
      std::vector<std::string> linebroken = chop(str, "\n");
      //Split each line and get number
      for (int i=0; i<linebroken.size(); i++) { //For each item in linebroken vector
            std::vector<std::string> workingline = chop(linebroken[i]);
            std::vector<std::string> workingtext = workingline;
            workingtext.erase(workingtext.begin());
            try{
                //std::cout << "\nOutput: " << workingline[0] << " ! + " << workingtext[0] << " ! \n";
              commands[std::stoi(workingline[0])] = workingtext;
            }catch(int e){}
      }
        return commands;}

      //This function calls the other functions based off of the string.
	   //probably better ways of doing this but whatever, This works I guess.
      void commandrun(std::vector<std::string> it, int i=1){
		  //ToDo: Variables: Any word inside a variable escape is to be redefined to its respective variable at commandtime
		   //The more variables defined in code, the longer it will take to run through the command stack.
        if(it[0]=="Forward" or it[0]=="FORWARD"){
            forward(std::stoi(it[1]));
          }elif(it[0]=="Back" or it[0]=="BACK"){
            backward(std::stoi(it[1]));
          }elif(it[0]=="Left" or it[0]=="LEFT"){
            turnleft(std::stoi(it[1]));
          }elif(it[0]=="Right" or it[0]=="RIGHT"){
            turnright(std::stoi(it[1]));
          }elif(it[0]=="CWTurn" or it[0]=="CWTURN"){
            turnright(std::stoi(it[1]));
          }elif(it[0]=="CCWTurn" or it[0]=="CCWTURN"){
            turnleft(std::stoi(it[1]));
          }elif(it[0]=="FlapOn" or it[0]=="FLAPON"){
            setflap(std::stoi(it[1]));
          }elif(it[0]=="FlapOff" or it[0]=="FLAPOFF"){
            setflap(0);
          }elif(it[0]=="SetLift" or it[0]=="SETLIFT"){
            setlift(std::stoi(it[1]),std::stoi(it[2]));
          }elif(it[0]=="SetFlap" or it[0]=="SETFLAP"){
            setflap(std::stoi(it[1]));
          }elif(it[0]=="LiftUp" or it[0]=="LIFTUP"){
            setlift(std::stoi(it[1]),std::stoi(it[2]));
          }elif(it[0]=="LiftDown" or it[0]=="LIFTDOWN"){
            setlift(-1*std::stoi(it[1]));
          }elif(it[0]=="LiftStop" or it[0]=="LIFTSTOP"){
            setlift(0);
          }elif(it[0]=="Print" or it[0]=="PRINT"){
            std::string itstring = "";
            for (int b=1; b<it.size(); b++){
              itstring = itstring + it[b] + " ";}
            print(it[1]);
            screen::terminalPush(terminal, itstring);
          }elif(it[0]=="Goto" or it[0]=="GOTO"){
            gotoo();
            i=std::stoi(it[1]);
          }elif(it[0]=="Wait" or it[0]=="WAIT"){
            wait(std::stoi(it[1]));
          }elif(it[0]=="END"){
            i=9999999;
          }else{
            //std::cout << "Did nothing on loop '" << i << "' \n";
          }
      }

    //Runs the BASIC script
      void scriptrun(std::map<int,std::vector<std::string>> commands){
        //Code that converts organized strings to function calls
         //Probably belongs on R/BadCode...
          //But oh well. it works I guess
      //Main for loop for each step
          for (int i=0; i<maxCommandLenght-1; i++) {
            std::vector<std::string> it = commands[i]; //Gets first vector of commands list
//ToDO: Make all strings in vector lowercase
            commandrun(it, i);
            pros::delay(5);
          }
      }
    void init(){

      //Commodore style boot text to match ViXeN kernal
       //-40 Columns wide, 25 Rows tall - 'Classic' VIXEN graphics mode style
      printTerminal("Running Auonomous mode :"+autoselected+"");
      printTerminal("-=+=-=+=-=+=-=+=-<++>-=+=-=+=-=+=-=+=-");
      printTerminal("* META ROBOTICS - R-VIXEN BASIC V0.1 *");
      printTerminal("-=+=-=+=-=+=-=+=-=++=-=+=-=+=-=+=-=+=-");
      printTerminal("128M RAM SYSTEM 38911 INSTR BYTES FREE");
      printTerminal("READY.");
      printTerminal("Running: "+autoselected+"");

    }



    std::string getString(std::string auton){
      if (auton == "red1"){
        return red1;
      }elif (auton == "red2"){
        return red2;
      }elif (auton == "blu1"){
        return blu1;
      }elif (auton == "blu2"){
        return blu2;
      }elif (auton == "gen1"){
        return gen1;
      }elif (auton == "gen2"){
        return gen2;
      }else{
        std::string fuckywucky = "10 PRINT OOPSIE WOOPSIE!! Uwu We made a fucky wucky!! A wittle fucko boingo! The code monkey at our headquarters is working VEWY HAWD to fix this! (but not wewwy)\n20 END";
        return fuckywucky;
      }
    }


  void main(std::string auton = "gen1"){

    if(shoudIUseTheWeirdBasicInterpreterAndDieALittleInsideBecauseIAmTooLazyToWriteABasicScriptThatDoesAnythingImportant){
    scmo::init();

    if(doGifOnAutonomous){screen::screenCover();}

    std::string atom = getString(auton);
    std::map<int,std::vector<std::string>> commands = scmo::tokenate(atom, "\n");//Function that makes a command list to be run. all unused memory slots are filled with a skip character

    if(debugOn){
      //Debug info, dumps program memory to serial terminal
        /*for (int i=0; i<maxCommandLenght; i++) {
          std::vector<std::string> it = commands[i];
          std::cout << "Final Check " << i << " : ";
            for (int b=0; b<it.size(); b++){
            std::cout << it[b] << " ";}
          std::cout << "\n";
        }*/}
    scriptrun(commands);//Function actually read the generated command list

  }else{
    scmo::aNormalScriptThatLiddleWillUnderstandAndCanFigureOutWhereItIsWithAVisionSensor(auton);
  }
}}

//All files related to autonomous have been merged into this file to reduce file amount and make it unnecessary to import this
 //entire file when it is the only one doing anything


void autonomous(){
    pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 1, "Autonomous+       |");
  //This whole project is kind of fuckey. since the initialize function didnt actually initialize anything, I guess I have to do it here...
    strafemtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift_mtr1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift_mtr2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  //ToDo: figure out how to set which autonomous to select
    scmo::main(autoselected);
  //Code didnt work, so im trying again with something new
}
