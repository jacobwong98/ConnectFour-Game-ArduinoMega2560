/*
	Project: Screen displays
	In this file, the functions will be used to display the Win/Lose/Start screens
	and will allow for the transition between these screens and select different game modes.
*/
#include "screen.h"
// Check if the player has touched the screen and if so, determine which mode is selected
void checkTouchMode(){
	TSPoint touch = ts.getPoint();
	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE){
		return;
	}
	touchY = map(touch.x, TS_MINX, TS_MAXX, 0, TFT_HEIGHT - 1);
	touchX = map(touch.y, TS_MINY, TS_MAXY, TFT_WIDTH - 1, 0);
	// Based on where the names are displayed, the first if will select PvP Mode
	if (touchX > TFT_WIDTH/2 -90 && touchX < TFT_WIDTH/2 + 90 && touchY > 115 && touchY <155 ){
		mode = 0; // Switch to PvP Mode
		screenLoop = 0;
	}
	else if (touchX > TFT_WIDTH/2 -100 && touchX < TFT_WIDTH/2 + 100 && touchY > 175 && touchY < 215 ){
		mode = 5; // Switch to Player Vs AI Mode
		screenLoop = 0;
	}
}
// This will display the Start screen
void startScreen(){
	tft.setCursor(0,0);
	tft.setTextSize(4);
	tft.setTextColor(0x8811);

	tft.print("ConnectFour");
	tft.setCursor(TFT_WIDTH/2 -115,55);
	tft.setTextSize(3);
	tft.print(" Pick a mode");
	tft.setCursor(TFT_WIDTH/2 -70,120);
	tft.setTextSize(4);
	tft.print("P Vs P");
	tft.setCursor(TFT_WIDTH/2 - 80,180);
	tft.print("P Vs AI");
}
// Displays the Player vs AI Win/Lose screen
void ScreenAI(){
	// Turn == 1 means that the player wins
	if (turn == 1){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU WIN");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}
	// Means the AI Won
	else if (turn == 2){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU LOSE");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}
}
// Displays the Win/Lose Screen for the Player vs Player mode
void Screen(){
	// If tieNum == 7 then the board is full and no cains of 4 were obtain so display a tie screen
	if (tieNum == 7){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU TIED");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}
	// On Arduino 1 and turn 1, then player 1 wins
	else if (turn == 1 && digitalRead(digitalInPin) == HIGH){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU WIN");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}
	// On Arduino 1 and turn 2, then player 1 loses
	else if (turn == 2 && digitalRead(digitalInPin) == HIGH){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU LOSE");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}
	// On Arduino 2 and turn 2, then player 2 wins
	else if (turn == 2 && digitalRead(digitalInPin) == LOW){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU WIN");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}
	// On Arduino 2 and turn 1, then player 2 loses
	else if (turn == 1 && digitalRead(digitalInPin) == LOW){
		tft.fillRect(0, 0, TFT_WIDTH, 16, ILI9341_BLACK);
		tft.setCursor(0,0);
		tft.setTextSize(4);
		tft.setTextColor(0x07E0);
		tft.print("YOU LOSE");
		tft.setCursor(0,50);
		tft.print(" Next G-mode");
		tft.setCursor(TFT_WIDTH/2 -70,120);
		tft.print("P Vs P");
		tft.setCursor(TFT_WIDTH/2 - 80,180);
		tft.print("P Vs AI");
	}

}
