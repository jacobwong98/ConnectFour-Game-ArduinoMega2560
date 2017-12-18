#ifndef _PVAICHECK_H_
#define _PVAICHECK_H_

#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;
extern int grid [6][7];
extern int placedRow, columnSelected, comparePlacedChip, player2Chip;
extern int isWinNum, index;
extern int compareColumn, compareRow;
extern int turn;

void AICheckVert();
void AICheckHoriz();
void AICheckDiaginolLeft();
void AICheckDiaginolRight();
void AICheckWin();


#endif
