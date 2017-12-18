/*
 Project "ConnectFour"
*/

//include all the appropiate libraries and header files
#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <TouchScreen.h>
#include "Communication.h"
#include "pvpcheck.h"
#include "screen.h"
#include "pvpmode.h"
#include "pvaicheck.h"

// define all the static variables
#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 6
#define YP A2
#define XM A3
#define YM 5
#define XP 4
#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//declare all the global variables and intialize some of them
int touchX, touchY;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int grid[6][7] = {0,0};
int columnSelected;
int tracker = 0, trackerOld = 0;
int turn;
int isWinNum = 0, tieNum = 0;
int player1Chip = 1, player2Chip = 2;
int comparePlacedChip, placedRow;
int index = 0;
int mode = 2; //start mode at starting screen
int compareColumn = -1, compareRow = -1; // outside the indexes of the grid array
int digitalInPin = 13;
int analogInPin = A1;
int readCounter = 0, messageloop = 0, screenLoop = 0;// message= top message, screen= prevent re-print.

void setup(){
	init();
	Serial.begin(9600);
	Serial3.begin(9600);
	pinMode(digitalInPin, OUTPUT);
	tft.begin();
	tft.fillScreen(ILI9341_BLACK);
	tft.setRotation(3);
}
// Draws the game board
void gameBoardSetup(){
	tft.fillScreen(ILI9341_BLACK);
	tft.fillRect(0, 16, TFT_WIDTH, TFT_HEIGHT - 15, ILI9341_BLUE);
	for (int column = 0; column < 7; column++){
		for (int row = 0; row < 6; row++){
			tft.fillCircle(22 + (column*45), 33 + (row*36), 15, ILI9341_BLACK);
		}
	}
}
// Runs the Player vs AI Mode
void PvAIMode(){
	trackerOld = tracker; //when play AI mode, set it again.
	messageloop = 0;
	while (true){
		// Player's turn
		if (turn == 1){
			if (messageloop == 0){
				tft.setCursor(0,0);
				tft.setTextColor(ILI9341_BLACK);
				tft.print("Waiting for AI");
				tft.setCursor(0,0);
				tft.setTextColor(ILI9341_WHITE);
				tft.print("Your Turn");
				messageloop = 1; //void the re-print
			}
			checkTouch();
			if (tracker != trackerOld && grid[0][columnSelected] == 0){
				player1Select();
				checkWin();
				if (isWinNum == 4){
					mode = 1;// change to the player vs AI win/lose screen
					break;
				}
				turn = 2;
				messageloop = 0;
			}
			trackerOld = tracker;
		}
		else {
			tft.setCursor(0,0);
			tft.setTextColor(ILI9341_BLACK);
			tft.print("Your Turn");
			tft.setCursor(0,0);
			tft.setTextColor(ILI9341_WHITE);
			tft.print("Waiting for AI");
			AICheckWin(); // Finds potential places to block player
			// If no moves were made to block player, the AI will randomly-generate a move
			if (turn != 1){
				while (true){
					delay(50);
					columnSelected = (analogRead(analogInPin)) % 7; // Returns values that are between 0 and 6
					if (grid[0][columnSelected] == 0){
						break;
					}
				}

				for (int counter = 5; counter > -1; counter--){
					if(grid[counter][columnSelected] == 0){
						grid[counter][columnSelected] = player2Chip;
						placedRow = counter;
						tft.fillCircle(22 + (columnSelected*45), 33 + (placedRow*36), 14, ILI9341_WHITE);
						break;
					}
				}
			}
			comparePlacedChip = player2Chip;
			checkWin(); // Check if AI made a chain of 4
			if (isWinNum == 4){
				mode = 1;
				break;
			}
			turn = 1;
		}
	}
}

int main(){
	setup();



	while(true){
		// Player Vs Player Mode
		if (mode == 0){
			tft.setTextSize(2);
			gameBoardSetup();
			// Reset grid to be empty
			for (int i = 0; i < 7; i++){
				for (int j = 0; j < 6; j++){
					grid[j][i] = 0;
				}
			}
			PvPMode();
		}
		// Win/Lose Screen for Player Vs AI Mode
		else if (mode == 1){
			if (screenLoop == 0){
				ScreenAI();
				screenLoop = 1;
			}
			checkTouchMode();
		}
		// Start Screen mode
		else if (mode == 2){
			if (screenLoop == 0){
				startScreen();
				screenLoop = 1;
			}
			checkTouchMode();
		}
		// Win/Lose Screen for Player Vs Player Mode
		else if (mode == 3){
			if (screenLoop == 0){
				Screen();
				screenLoop = 1;
			}
			checkTouchMode();
		}
		// Player vs AI Mode
		else {
			turn = 1;
			comparePlacedChip = player1Chip;
			tft.setTextSize(2);
			gameBoardSetup();
			// Reset grid to be empty
			for (int i = 0; i < 7; i++){
				for (int j = 0; j < 6; j++){
					grid[j][i] = 0;
				}
			}
			PvAIMode();
		}
	}

	Serial.end();
	return 0;
}
