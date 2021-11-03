//Global Variables file for doing globals stuffs.
 //Used for storing AutonomousSelected, ScreenSettings
//std::string autoselected = "gen1";
//std::bool useExternal = false;
#include "pros/apix.h"
#include "main.h"
#include "gif-pros/gifclass.hpp"
#define elif else if

extern std::string red1;
extern std::string red2;
extern std::string blu1;
extern std::string blu2;
extern std::string gen1;
extern std::string gen2;
extern bool doOpLockout;
extern int liftspeed;
extern double leftZero;
extern double rightZero;
extern std::string autoselected;
extern std::string prevscreen;
extern std::string screenTab;
extern std::string terminallog;
extern lv_obj_t* terminal;
extern bool pushterminaltoserialdefault;
extern bool pushterminaltoserial;
extern int coverimageslot;
extern bool screenDecoOverride;
extern bool doGifScreen;
extern bool doGifOnAutonomous;

extern int autonomousFullSpeed;
extern int autonomousStrafeSpeed;

//Function call attepmt
void AtomicHelp();
void AtomicInsertion();

namespace screen{lv_obj_t* makeimage(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, int id, const char* directory);void AtomicHelper();void Atomic();void Main();void terminalPush(lv_obj_t* terminal, std::string printext);void screenCover();void Decoscreen(void* param);void returnScreen(std::string newTab);void Software(); void Hardware(); void Menu();
}
void resetAtomic();void saveAtomic();void dumpToSD(std::string);void addCom(std::string);
//void AtomicHelper();void Atomic();
