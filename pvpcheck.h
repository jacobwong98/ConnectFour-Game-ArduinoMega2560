#ifndef _PVPCHECK_H_
#define _PVPCHECK_H_

extern int grid[6][7];
extern int isWinNum;
extern int index;
extern int comparePlacedChip;
extern int placedRow;
extern int columnSelected;
extern int tieNum;

void checkVert();
void checkHoriz();
void checkDiaginolLeft();
void checkDiaginolRight();
void checkWin();

#endif
