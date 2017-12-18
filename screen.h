#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <Adafruit_ILI9341.h>
#include <TouchScreen.h>


#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
#define MINPRESSURE 10
#define MAXPRESSURE 1000
extern Adafruit_ILI9341 tft;
extern TouchScreen ts;
extern int mode;
extern int digitalInPin;
extern int turn;
extern int touchX, touchY;
extern int screenLoop;
extern int tieNum;

void checkTouchMode();
void Screen();
void startScreen();
void ScreenAI();

#endif
