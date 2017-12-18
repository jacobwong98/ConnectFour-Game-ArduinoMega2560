/*
Project Communication
*/

#include "Communication.h"
// Be used to randomly-generate a turn
void getGamekey(){
	// Voltage in analog pin changes randomly so we want to get values from there.
	int randomValue = analogRead(analogInPin);
	// By doing mod 2 will we only get 0 or 1 (Even or Odd numbers). We chose that
	// if the number read was even then it is player 1's turn and vice versa.
	if (randomValue%2 == 0){
		turn = 1;
	}
	else{
		turn = 2;
	}
}
// This function will check the serial3 port and see if anything can be read from there.
// If nothing is available to be read, or the number of bytes requested is not read in time
// this function will return false.
bool wait_on_serial3( uint8_t nbytes, long timeout ) {
	unsigned long deadline = millis() + timeout;
	while (Serial3.available()<nbytes && (timeout<0 || millis()<deadline))
	{
		delay(1);
	}
	return Serial3.available()>=nbytes;
}
// Finite State Machine used by player 1 to send the turn number to player 2
void sendTurnNum(){
	enum State {START, WaitingForAck, DataEXchange};
	State currentState = START;
	long timeout = 1000;
	// The state machine will run until we reach DataEXchange state, indicating the turn number was exchanged
	while (currentState != DataEXchange){
		if (currentState == START){
			Serial3.write('C'); // Send a 'C' to confirm connection to player 2
			currentState = WaitingForAck;
		}
		else if (currentState == WaitingForAck && wait_on_serial3(1,timeout)){
			char ACK = Serial3.read(); // Read serial 3 and if that value is 'A' then we can send the turn number
			if (ACK == 'A'){
				Serial3.write(turn);
				currentState = DataEXchange;
			}
		}
		// If above states fail, we want to loop back to START state
		else {
			currentState = START;
		}
	}
}
// Finite State Machine used by player 2 to receive the turn number from player 1
void receiveTurnNum(){
	enum State {LISTEN, WaitingForkey, DataExchange};
	State currentState = LISTEN;
	long timeout =1000;
	// State machine will run until the turn number has been exchanged between Arduinos
	while (currentState != DataExchange){
		if (currentState == LISTEN && wait_on_serial3(1, timeout)){
			char CR = Serial3.read();// If we get a 'C' means we have connected with other Ardunio
			if (CR == 'C' ){
				Serial3.write('A'); // Send an 'A' to acknowledge
				currentState = WaitingForkey;
			}
		}
		else if (currentState == WaitingForkey && wait_on_serial3(1, timeout)){
			turn = Serial3.read();
			if (turn == 1 || turn == 2 ){
				currentState = DataExchange;
			}
		}
		else{
			currentState = LISTEN;
		}
	}
}
