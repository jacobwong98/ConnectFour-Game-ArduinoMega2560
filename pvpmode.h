#ifndef _PVPMODE_H_
#define _PVPMODE_H_

#include "Communication.h"
#include "pvpcheck.h"
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
extern int touchX, touchY;
extern int counter, turn;
extern int grid[6][7];
extern int columnSelected, placedRow;
extern int player1Chip, player2Chip, comparePlacedChip;
extern int readCounter;
extern int digitalInPin;
extern int messageloop;
extern int tracker, trackerOld;
extern int isWinNum,tieNum, mode;

void checkTouch();
void player1Select();
void player2Select();
void getRowAndColumn();
void PvPMode();

#endif
