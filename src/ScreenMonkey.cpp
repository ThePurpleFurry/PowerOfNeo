#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/apix.h"
#include "pros/apix.h"
#include "display/lvgl.h"
#include <cstring>
#include <utility>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "Global.hpp"
#include "Sdimage.hpp"
#include "gif-pros/gifclass.hpp"

#include <vector>
#include <cstring>
#include <regex>
#include <utility>
#include "okapi/api.hpp"
//#include "demo.h"

#define GifFileDefinitioned "/usd/[Put file name here].gif"
int GifOffsetXOffset = 0;
int GifOffsetYOffset = 0;
/*Name                  |  X   | Y  | Description
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
sans                    | 000 | 000 | Comic Sans

    !NEW!
=-=-=-=
boop                    | 000 | 000 | Furry Boop
boredom                 | 000 | 000 | Hazbin Alasor Sheer Absolute Boredom!
fox_runs_the_world      | 000 | 000 | Fox running on top of the world
grav_billglitch         | 000 | 000 | Gravity falls bill cipher thing
grav_billrune           | 000 | 000 | Bill cipher rune thing
grav_billslotmachine    | 000 | 000 | Bill being a slot machine
grav_cops               | 000 | 000 | when theres no cops awound, anythings legal
grav_escape             | 000 | 000 | Escaping responsibilities
grav_fight              | 060 | 000 | Fight! Fight! Fight! gif
grav_gnomebarf          | 000 | 000 | Rainbow gnome barf
grav_mableloop          | 000 | 000 | Mable running on the ground
grav_pressstart         | 000 | 000 | Dipper pressing start
grav_unicorn            | 000 | 000 | Unicorn nyaa
grav_waddlebook         | 000 | 000 | Waddles chewing on a book
husk                    | 000 | 000 | Husk doin stuff.
mow                     | 118 | 000 | Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow. Mow.
=-=-=-=-=-=-=-
*/

#define TheStockMarketCrashOf1929 pros::E_MOTOR_GEARSET_18       //"who wants some jambalaya!" -Alastor, HH
#define TheIrishPotatoFamineOf1845 pros::E_MOTOR_ENCODER_DEGREES //Couldnt think of a reference for this

int liftspeed = 0;
double leftZero  =  999;
double rightZero  = 999;
std::string autoselected = "blu1";
std::string prevscreen = "none";
char outputtext[1024];
lv_obj_t * keyboard;
bool wideterminal = false;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller slave(pros::E_CONTROLLER_PARTNER);


/*====================================================*\
| GUI Making Functions                                 |
| Due to the inherent ability to make any code messy,  |
| all LVGL code is contained in this file.             |
|    and dont expect to be able to read it easily too, |
|     its hard enough to even get this to work         |
\*====================================================*/
std::string gifsource;
int coverimageslot = 0;
std::string screenTab = "atom";
std::string terminallog = "Event::Init::SuccessfullyBooted\n";
std::string printext;
bool doGifScreen = false;

void liftProtecc(void* param) {
  std::cout << "started LiftProtecc\n";
pros::Motor lift_mtr1 (6, TheStockMarketCrashOf1929, true,  TheIrishPotatoFamineOf1845);
pros::Motor lift_mtr2 (7, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
pros::Motor scoop1    (9, TheStockMarketCrashOf1929, false, TheIrishPotatoFamineOf1845);
pros::Motor scoop2    (10, TheStockMarketCrashOf1929, true, TheIrishPotatoFamineOf1845);
pros::ADIDigitalIn rightLimit (1);
pros::ADIDigitalIn leftLimit  (2);
while(true){
  if(slave.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_L2) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    if(slave.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      lift_mtr1.move_velocity(0);
      lift_mtr2.move_absolute(lift_mtr1.get_position(), 80);
    }else{
      lift_mtr1.move_absolute(lift_mtr2.get_position(), 80);
      lift_mtr2.move_velocity(0);
    }
  }else{
  if(liftspeed > 0){
      if (lift_mtr1.get_position() >= 1500){
        lift_mtr1.move_velocity(0);
      }else{
        lift_mtr1.move_velocity(liftspeed/1.5);
      }
      if (lift_mtr2.get_position() >= 1500){
        lift_mtr2.move_velocity(0);
      }else{
        lift_mtr2.move_velocity(liftspeed/1.5);
      }
  }else{
    if (rightLimit.get_value()){
      lift_mtr1.move_velocity(0);
      lift_mtr1.set_zero_position(0);
      }else{
      lift_mtr1.move_velocity(liftspeed/1.75);
    }
    if (leftLimit.get_value()){
      lift_mtr2.move_velocity(0);
      lift_mtr2.set_zero_position(0);
      }else{
      lift_mtr2.move_velocity(liftspeed/1.75);
    }
      leftZero = lift_mtr2.get_position();
      rightZero = lift_mtr1.get_position();
    }}
  pros::delay(50);
  }
}

bool screenDecoOverride = false;
std::vector<std::string> atomicConversion = {"NULL","red1","red2","blu1","blu2","gen1","gen2","none"};

lv_obj_t * gifobject= lv_obj_create(lv_scr_act(), NULL);
lv_obj_t * Mother  =  lv_obj_create(lv_scr_act(), NULL);
lv_obj_t * terminal =  lv_ta_create(lv_scr_act(), NULL);




namespace screen{
  //Externals
   //========--
  bool isLeftPressed(){
  }
  bool isRightPressed(){
  }
  bool isUpPressed(){
  }
  bool isDownPressed(){
  }
  bool isSelectPressed(){
  }








  char* strToChar(std::string input, bool doTrail=false){
    std::string textraw;
    if(doTrail){
      textraw = input + "                                  |";
    }else{
      textraw = input;
    }
    strcpy(outputtext, textraw.c_str());
    return outputtext;
  }
//Variables
 //Screen Tab Thingy
   // atom
   // main
   // menu
   // options
   // cavequote
   // poem
   // atomHelp


//Internal Functions
void terminalPush(lv_obj_t* terminal, std::string printext){
  //code to write things on the terminal screen,
    //when that part gets done that is...
    if(pushterminaltoserial)std::cout << printext;
    std::cout << terminal;
    printext = printext + "\n";
    terminallog = terminallog + printext;
    char* printec = strToChar(printext);
    lv_ta_add_text(terminal, printec);
}

void deleteScreen(){

}

void refreshScreen(){
  //Function called to update screen

}

void reloadScreen(){
  lv_obj_clean(Mother);
  lv_obj_align(terminal, NULL, LV_ALIGN_IN_TOP_LEFT, 500, 500);
  lv_obj_align(gifobject, NULL, LV_ALIGN_IN_TOP_LEFT, 480, 240);
  lv_obj_set_width(terminal, 1);
  lv_obj_set_height(terminal, 1);
  //Function called to reset the entire screen

}

void checkScreenChange(int id){
  if(screenTab == "atom"){
    if(id<=7 and id>=1){
    autoselected = atomicConversion[id];
    reloadScreen();}
    std::cout << autoselected << "\n";
    screenTab="main";
    Main();
  }elif(screenTab == "Atomichelp"){
    if(id==1){
      addCom("- -- --- -- -");terminalPush(terminal, "- -- --- -- -");
    }elif(id==2){
      saveAtomic();
    }elif(id==3){
      resetAtomic();}
}elif(screenTab == "main"){
  if(id==1){
    screenTab="menu";
    Menu();
    terminalPush(terminal, "EVENT::PUSHED::MENU.1");
  }elif(id==2){
    std::cout << "Event:Buttonpress:Pause\n";
    screenTab = "atom";
    reloadScreen();
    Atomic();
  }elif(id==3){
    reloadScreen();
    screenCover();
  }elif(id==666){
    if(wideterminal){
      wideterminal=false;
    }else{
      wideterminal=true;
    }Main();
  }
}elif(screenTab == "menu"){
  if(id==1){
    screenTab="main";
    Main();
  }elif(id==2){
    screenTab="software";
    Software();
  }elif(id==3){
    screenTab="hardware";
    Hardware();
  }elif(id==666){
    if(wideterminal){
      wideterminal=false;
    }else{
      wideterminal=true;
    }Menu();
  }
}elif(screenTab == "software"){
  if(id==1){
    screenTab="menu";
    Menu();
  }elif(id==2){
  }elif(id==3){
  }
}elif(screenTab == "hardware"){
  if(id==1){
    screenTab="menu";
    Menu();
  }elif(id==2){
  }elif(id==3){
  }
}elif(screenTab == "ScreenDeco"){
  if(id==1){
    doGifScreen=false;
  }
}
}


//Trigger event for created buttons and gets it's id
static lv_res_t btn_click_action(lv_obj_t * evntbtn){

  int id = lv_obj_get_free_num(evntbtn);
      screen::checkScreenChange(id);
     return LV_RES_OK;
  }

  lv_obj_t* terminalBlock(lv_coord_t x=0, lv_coord_t y=0, lv_coord_t w=200, lv_coord_t h=200, int id=0){
    static lv_style_t style_metaterm;
    lv_style_copy(&style_metaterm, &lv_style_plain);
    style_metaterm.body.main_color = LV_COLOR_HEX(0x540178);
    style_metaterm.body.grad_color = LV_COLOR_HEX(0x37004f);
    style_metaterm.body.border.color = LV_COLOR_HEX(0xe9b5ff);
    style_metaterm.body.border.width = 1;
    style_metaterm.body.border.opa = LV_OPA_70;
    style_metaterm.body.radius = 5;
    style_metaterm.body.opa = LV_OPA_60;
    style_metaterm.text.color = LV_COLOR_HEX(0xe9b5ff);
    style_metaterm.text.line_space = 1;
    style_metaterm.text.letter_space = 1;
    style_metaterm.text.font = &lv_font_dejavu_20;



    lv_obj_set_size(terminal, w, h);
    lv_obj_align(terminal, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);
    lv_obj_set_width(terminal, w);
    lv_obj_set_height(terminal, h);
    lv_obj_set_free_num(terminal, id);
    lv_obj_set_style(terminal, &style_metaterm);
    lv_ta_set_cursor_type(terminal, LV_CURSOR_OUTLINE);
    char* termlogchar = strToChar(terminallog);
    lv_ta_set_text(terminal, termlogchar);

  return terminal;}

//Create a button object with an id
  lv_obj_t* makeButton(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, int id, const char* label, int theme=0) {

    static lv_style_t style_metamain;
    lv_style_copy(&style_metamain, &lv_style_plain);
    style_metamain.body.main_color = LV_COLOR_HEX(0x540178);
    style_metamain.body.grad_color = LV_COLOR_HEX(0x37004f);
    style_metamain.body.border.color = LV_COLOR_HEX(0xe9b5ff);
    style_metamain.body.border.width = 1;
    style_metamain.body.border.opa = LV_OPA_70;
    style_metamain.body.radius = 8;
    style_metamain.body.opa = LV_OPA_60;
    style_metamain.text.color = LV_COLOR_HEX(0xe9b5ff);

    static lv_style_t style_metamainhi;
    lv_style_copy(&style_metamainhi, &lv_style_plain);
    style_metamainhi.body.main_color = LV_COLOR_HEX(0x8500bf);
    style_metamainhi.body.grad_color = LV_COLOR_HEX(0x710e87);
    style_metamainhi.body.border.color = LV_COLOR_HEX(0xff7de1);
    style_metamainhi.body.border.width = 1;
    style_metamainhi.body.border.opa = LV_OPA_70;
    style_metamainhi.body.radius = 8;
    style_metamainhi.body.opa = LV_OPA_60;
    style_metamainhi.text.color = LV_COLOR_HEX(0xff7de1);


    static lv_style_t style_selred;
    lv_style_copy(&style_selred, &lv_style_plain);
    style_selred.body.main_color = LV_COLOR_HEX(0xfa2352);
    style_selred.body.grad_color = LV_COLOR_HEX(0x37004f);
    style_selred.body.border.color = LV_COLOR_HEX(0xe9b5ff);
    style_selred.body.border.width = 1;
    style_selred.body.border.opa = LV_OPA_70;
    style_selred.body.radius = 8;
    style_selred.body.opa = LV_OPA_60;
    style_selred.text.color = LV_COLOR_HEX(0xe9b5ff);

    static lv_style_t style_selblu;
    lv_style_copy(&style_selblu, &lv_style_plain);
    style_selblu.body.main_color = LV_COLOR_HEX(0x37004f);
    style_selblu.body.grad_color = LV_COLOR_HEX(0x4a23fa);
    style_selblu.body.border.color = LV_COLOR_HEX(0xe9b5ff);
    style_selblu.body.border.width = 1;
    style_selblu.body.border.opa = LV_OPA_70;
    style_selblu.body.radius = 8;
    style_selblu.body.opa = LV_OPA_60;
    style_selblu.text.color = LV_COLOR_HEX(0xe9b5ff);

    lv_obj_t* btn = lv_btn_create(Mother, NULL);
    //lv_obj_set_event_cb(btn, bEventHandler);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);
    lv_obj_set_width(btn, w);
    lv_obj_set_height(btn, h);
    lv_obj_set_free_num(btn, id);   /*Set a unique number for the button*/
    lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_action);
    if(theme==0){lv_btn_set_style(btn,LV_BTN_STYLE_REL, &style_metamain);
    }elif(theme==1){lv_btn_set_style(btn,LV_BTN_STYLE_REL, &style_selred);
    }elif(theme==2){lv_btn_set_style(btn,LV_BTN_STYLE_REL, &style_selblu);
    }
    lv_btn_set_style(btn,LV_BTN_STYLE_PR, &style_metamainhi);
    //lv_obj_set_user_data(btn, id);

    lv_obj_t* btntext = lv_label_create(btn, NULL);
    lv_label_set_text(btntext, label);

    //lv_btn_set_ink_in_time(btn, 400);
    //lv_btn_set_ink_wait_time(btn, 100);
    //lv_btn_set_ink_out_time(btn, 300);
  return btn;}

  lv_obj_t* makeimage(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, int id, const char* directory = "S:/usd/metatest.bin"){
    lv_fs_drv_t pcfs_drv;                         /*A driver descriptor*/
    memset(&pcfs_drv, 0, sizeof(lv_fs_drv_t));    /*Initialization*/

    pcfs_drv.file_size = sizeof(pc_file_t);       /*Set up fields...*/
    pcfs_drv.letter = 'S';
    pcfs_drv.open = pcfs_open;
    pcfs_drv.close = pcfs_close;
    pcfs_drv.read = pcfs_read;
    pcfs_drv.seek = pcfs_seek;
    pcfs_drv.tell = pcfs_tell;
    lv_fs_add_drv(&pcfs_drv);

    lv_obj_t * img_var = lv_img_create(Mother, NULL);
    lv_img_set_src(img_var, directory);
    lv_obj_set_pos(img_var, x, y);
    return img_var;
  }

//Creates a label with an id
  lv_obj_t* makeLabel(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, int id, const char* text) {
    lv_obj_t* label = lv_label_create(Mother, NULL);
    lv_label_set_text(label, text);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, x, y);
    lv_obj_set_width(label, w);
    lv_obj_set_height(label, h);

  return label;}

  bool wideterminalcheck(){
    if(wideterminal){
      makeButton( 0, 0, 20, 20, 666, "X");
      terminal = terminalBlock(20,  5, 450, 225, 30);

      return false;
    }else{return true;}
  }

//====================================================================================================
//====================================================================================================

  void Atomic(){
    reloadScreen();
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    makeButton( 20, 20, 140, 50, 1, "Red1", 1);
    makeButton(320, 20, 140, 50, 2, "Red2", 1);
    makeButton(20, 169, 140, 50, 3, "Blu1", 2);
    makeButton(320, 169,140, 50, 4, "Blu2", 2);
    makeButton(24,  94, 140, 50, 5, "Gen1");
    makeButton(312, 94, 140, 50, 6, "Gen2");
    makeButton(168, 94, 140, 50, 7, "NONE");
    makeimage(190, 30, 0, 0, 22, "S:/usd/MetaLogoHalf.bin");
    //makeButton(169, 169, 140, 50, 8, "AtomHelp");

     makeLabel(190, 75, 140, 50, 20,"Autonomous");
     makeLabel(205, 145, 140, 50, 21,"Selector");
  }


  void AtomicHelper(){
    reloadScreen();
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    makeButton( 10,  10, 40, 40, 1, "Line\nBreak");
    terminalBlock(50, 10, 400, 250, 30);
    makeButton( 10,  60, 40, 40, 2, "Save");
    makeButton( 10,  110, 40, 40, 3, "CLR");
    //makeButton(320,  60, 140, 50, 2, "Pause");
  }

  void Main(){
    //Main menu screen, visible terminal and a few buttons
    reloadScreen();
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    if(wideterminalcheck()){
    makeButton( 10, 100, 190, 50, 1, "Menu");
    makeButton( 10, 160, 190, 50, 2, "Autonomous Select");
    terminalBlock(220,  5, 250, 225, 30);
    makeimage(10, 10, 0, 0, 22, "S:/usd/MetaLogo.bin");
    makeButton( 10, 220, 80, 20, 666, "XLTerm");
    makeLabel(10, 80, 100, 50, 11,"Main Menu - V0.00.87");
    makeButton( 100, 220, 80, 20, 3, "Deco");}


  }

  void screenCover(){
    doGifScreen = true;
  }


void YifyGiffy(void* param){
  //Gif Handling Service
    //Stages:
    //1)No gif, either object was deleted or never existed
    //2)Request was made for gif, set other modules should respond to flag being set
    //3)Flag for gif was removed by something, delete all objects
    std::cout << "started Giffy Function\n";
    lv_obj_set_size(gifobject, 480, 240);
    lv_obj_set_style(gifobject, &lv_style_transp); // make the container invisible
    lv_obj_align(gifobject, NULL, LV_ALIGN_IN_TOP_LEFT, 500, 500);
    Gif gif(GifFileDefinitioned, gifobject);

    while(true){
    while(!doGifScreen){pros::c::task_delay(40);}
    //Escape while loop if variable true
    //Make all required objects
    prevscreen = screenTab;
    screenTab = "ScreenDeco";
    reloadScreen();
    //makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    lv_obj_align(gifobject, NULL, LV_ALIGN_IN_TOP_LEFT, 0+GifOffsetXOffset, 0+GifOffsetYOffset);

    makeButton( 0, 220, 80, 20, 1, "Menu");
	  while( doGifScreen){pros::c::task_delay(40);}
    //After told to turn off clean gif library and purge object
    reloadScreen();
    screenTab = prevscreen;
    returnScreen(screenTab);
    pros::c::task_delay(20);
  }
}


  void Menu(){
    reloadScreen();
    //Has many buttons to get to other screens and functions
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    makeimage(10, 10, 0, 0, 21, "S:/usd/MetaLogo.bin");
    makeimage(30, 30, 0, 0, 22, "S:/usd/MetaLogo.bin");
    makeimage(60, 60, 0, 0, 23, "S:/usd/MetaLogo.bin");
    makeimage(90, 90, 0, 0, 24, "S:/usd/MetaLogo.bin");
    makeimage(120, 120, 0, 0, 25, "S:/usd/MetaLogo.bin");
    makeimage(150, 150, 0, 0, 26, "S:/usd/MetaLogo.bin");
    makeButton( 10, 100, 190, 50, 1, "Main Menu");
    makeLabel(5, 5, 100, 50, 11,"Menu Selection - V0.00.02");
    makeButton( 10, 30, 190, 50, 2, "Software Info");
    makeButton( 40, 60, 190, 50, 3, "Hardware Info");
    makeButton( 70, 80, 190, 50, 4, "Run Autonomous");
    makeButton( 120, 100, 190, 50, 5, "Cave Johnson Rant");

  }

  void Software(){
    reloadScreen();
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    makeButton( 10, 100, 190, 50, 1, "Back to Menu");
    makeLabel(5, 5, 100, 50, 11,"Meta Robotics - Power of NEO for V5");
  }

  void Hardware(){
    reloadScreen();
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    makeButton( 10, 100, 190, 50, 1, "Back to Menu");
  }

  void Johnson(){
    reloadScreen();
    makeimage(0, 220, 0, 0, 22, "S:/usd/TRA.bin");
    makeButton( 10, 100, 190, 50, 1, "Back to Menu");
  }

  void returnScreen(std::string newTab = "main"){
    std::cout << "ReturnScreen call: " << newTab << "\nScreenTab value: " << screenTab << "\n";
    if(newTab=="main"){
      screen::Main();
    }elif(newTab=="auto"){
      screen::Atomic();
    }else{
      screen::Main();
    }
  }

//====================================================================================================
//====================================================================================================
void init(){

   /*=======================*\
  | Initialize screen stuffs |
  \*=======================*/

  	makeButton(10, 20, 100, 50, 0, "Hello world");
  	makeButton(110, 20, 100, 50, 1, "Hello world2");
  	makeButton(90, 70, 100, 50, 2, "Ree");
  	lv_obj_t* mainlabel = makeLabel(100, 60, 100, 50, 3, "O Hai Mark");
    makeLabel(100,90,100,50,4, "I did not hit her, its bullShit");

  	//Create checkbox for useing SD
  	lv_obj_t* cb = lv_cb_create(lv_scr_act(), NULL);
  	lv_cb_set_text(cb, "Use internal presets");
  	lv_obj_align(cb, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 300);
  	//lv_obj_set_user_data(cb, 4);
  	//lv_obj_set_event_cb(cb, cEventHandler);
}




}//End of Screen Namespace

void competition_initialize(){
  initialize();
}

void initialize() {

  pros::delay(150);//Initialize fix
  lv_obj_align(terminal, NULL, LV_ALIGN_IN_TOP_LEFT, 500, 500);
  lv_obj_set_width(terminal, 1);
  lv_obj_set_height(terminal, 1);
  lv_obj_set_width(Mother, 480);
  lv_obj_set_height(Mother, 320);
  lv_obj_set_style(Mother, &lv_style_transp);


  screen::Atomic();
  pros::Task YiffyGif (screen::YifyGiffy, (void*)"7", "YiffyGif");
  pros::Task protect (liftProtecc, (void*)"PROS", "Protection");
  if(master.is_connected() and not(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) or master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_L1) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_L2)
or master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) or master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_R1) or slave.get_digital(pros::E_CONTROLLER_DIGITAL_R2))){
  pros::c::controller_set_text(pros::E_CONTROLLER_MASTER,  1, 1, "Running LiftInit     |");
  pros::c::controller_set_text(pros::E_CONTROLLER_PARTNER, 1, 1, "Running LiftInit     |");
  liftspeed = -150;
  pros::delay(4000);
  liftspeed = 100;
  pros::delay(1000);
  liftspeed = -100;
  pros::delay(2000);
  liftspeed = 0;}





  /*//command todo's
  -rotate to degree
  -sensor inputs
  -variables
  -per motor control
  */



  //screen::AtomicHelper();
  //screen::init();
}



/*=====================================
| Internally saved autonomous presets |
| to run: uncheck from SD on selector |
=====================================*/

//The internally saved autonomous BASIC scripts are saved as multiline strings
 //put a '\n' after each command and a '\'backslash at the end of each line.

//1sec = 10.5 inch



//Strings for autonomous since PROS hates recompiling header files

//Red Slot 1
std::string red1 = "100 END\n\
10 FlapOn -90\n\
20 Wait 300\n\
25 FlapOff\n\
30 Forward 1700\n\
40 Right 1050\n\
50 SetLift 90 2650\n\
80 Forward 700\n\
90 Back 100\n\
100 Right 100\n\
110 FlapOn -70\n\
120 Wait 1400\n\
130 FlapOff\n\
140 Back 850\n\
150 SetLift -90 3450";
//Red Slot 2
std::string red2 = "100 END\n\
10 SetLift 90 1700\n\
20 SetLift -90 0\n\
30 SetLift -90 2050\n\
40 SetLift 90 1850\n\
50 Wait -59136366\n\
55 FlapOff\n\
60 FlapOn -90\n\
70 Wait 2300\n\
75 FlapOff\n\
80 SetLift -90 2450";
//Blu Slot 1
std::string blu1 = "100 END\n\
10 FlapOn -90\n\
20 Wait 300\n\
25 FlapOff\n\
30 Forward 1700\n\
40 Left 1050\n\
50 SetLift 90 2650\n\
70 Right 300\n\
80 Forward 550\n\
90 Back 100\n\
100 Left 100\n\
110 FlapOn -90\n\
120 Wait 1400\n\
130 FlapOff\n\
140 Back 850\n\
150 SetLift -90 3450";
//Blu Slot 2
std::string blu2 = "100 END\n\
10 Back 2000";
//General Purpose Slot #1
std::string gen1 = "100 END\n\
10 Forward 3000\n\
20 Back 2000\n\
30 Print Hello wolrd";
//General Purpose Slot #2
std::string gen2 = "100 END\n\
10 FlapOn -90\n\
20 Wait 300\n\
25 FlapOff\n\
30 Forward 1700\n\
40 Left 1050\n\
50 SetLift 90 2650\n\
70 Right 300\n\
80 Forward 550\n\
90 Back 100\n\
100 Left 100\n\
110 FlapOn -90\n\
120 Wait 1400\n\
130 FlapOff\n\
140 Back 850\n\
150 SetLift -90 3450";

/*=- Command Helper -=*\
| Forward <time>
| Left <time>
| Right <time>
| Back <time>
| CWTurn <time>
| CCWTurn <time>
| X-Motor <port>, <>
| X-Sensor <port> - Returns bit
| END - stops the autonomous function
| Wait - Waits for x amount of milliseconds
| LiftU - Raises Lift
| LiftD - Lowers Lift
| Unfold - TODO, will most likely be yet another rBASIC script for defining schtuff.
|
\*=- -=+=-=++=-=+=- -=*/
