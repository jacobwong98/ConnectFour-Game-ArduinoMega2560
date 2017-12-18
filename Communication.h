#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <Arduino.h>

extern int turn;
extern int digitalInPin;
extern int analogInPin;

void getGamekey();
bool wait_on_serial3(uint8_t nbytes, long timeout);
void sendTurnNum();
void receiveTurnNum();

#endif
