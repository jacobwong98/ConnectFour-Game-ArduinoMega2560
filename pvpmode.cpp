/*
	Project: Player Vs Player Mode
	In this file are the functions that will run the player vs player mode when
	selected by both players.
*/
#include "pvpmode.h"
// Checks if the player has pressed the screen
void checkTouch(){
	TSPoint touch = ts.getPoint();
	// If no press is detected "skip" the below steps
	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE){
		return;
	}
	// Want to map the coordinates of the touches to fit on our display screen.
	touchY = map(touch.x, TS_MINX, TS_MAXX, 0, TFT_HEIGHT - 1);
	touchX = map(touch.y, TS_MINY, TS_MAXY, TFT_WIDTH - 1, 0);
	// Determine the column that the player has tapped on. The touch does not depend
	// on the row pressed because the chip should fall to the next empty row.
	for (int i = 0; i < 7; i++){
		if (touchX > 7 + (i*45) && touchX < 37 + (i*45)){
			columnSelected = i;
			tracker++;// Used in PvPMode() to run the rest of the steps once
			break;
		}
	}
	delay(100);
}
// Want to determine the next empty row based on the column selected by the player.
// So starting from the bottom row, we check if that row is empty and fill that row
// with player one chip.
void player1Select(){
	for (int counter = 5; counter > -1; counter--){
		if(grid[counter][columnSelected] == 0){
			grid[counter][columnSelected] = player1Chip;
			placedRow = counter;
			tft.fillCircle(22 + (columnSelected*45), 33 + (counter*36), 14, ILI9341_RED);
			break;
		}
	}
	// Change comparePlacedChip to player1Chip to be used in the checkWin() function.
	comparePlacedChip = player1Chip;
	delay(300);
}
// Also want to find the row that player 2's chip will fall into but place their chip
// in that position instead of player 1's chip.
void player2Select(){
	for (int counter = 5; counter > -1; counter--){
		if(grid[counter][columnSelected] == 0){
			grid[counter][columnSelected] = player2Chip;
			placedRow = counter;
			tft.fillCircle(22 + (columnSelected*45), 33 + (counter*36), 14, ILI9341_WHITE);
			break;
		}
	}
	// Change comparePlacedChip to player2Chip to check if player 2 wins in checkWin().
	comparePlacedChip = player2Chip;
	delay(300);
}

// This function is used by the player who is waiting for the other player to send
// the coordinates of where the chip has fallen into.
void getRowAndColumn(){
	// once we have read two numbers from serial3, we can move on with other stuff
	while (readCounter < 2){
		if (Serial3.available() > 0){
			// the first number sent through serial3 should be the row where the chip is
			if (readCounter == 0){
				placedRow = Serial3.read();
				readCounter++;
			}
			// the second number sent through serial3 should be the column chosen by the player
			else if (readCounter == 1){
				columnSelected = Serial3.read();
				readCounter++;
			}
		}
	}
}
// This function runs all the necessary steps to perform the player vs player mode.
void PvPMode(){
	// Reassign trackerOld because after a game of PvP has finished, trackerOld will be different
	// then tracker at the start of a new game, so the game would automatically play a turn.
	// So need to make sure trackerOld == tracker.
	trackerOld = tracker;
	messageloop = 0;// In case messageloop is not reset to 0.
	// To differentiate the two Arduinos, one will get the randomly-generated turn
	// and send it to the other player.
	if (digitalRead(digitalInPin) == HIGH){
		getGamekey();
		sendTurnNum();
	}
	else {
		receiveTurnNum();
	}
	while (true){
		// Player with Arduino 1 and turn 1 means it's their turn to play.
		if (turn == 1 && digitalRead(digitalInPin) == HIGH){
			// If statement will print message once
			if (messageloop == 0){
				// Overwrite previous message and write Your turn message on top bar of screen.
				tft.setCursor(0,0);
				tft.setTextColor(ILI9341_BLACK);
				tft.print("Waiting for other player");
				tft.setCursor(0,0);
				tft.setTextColor(ILI9341_WHITE);
				tft.print("Your Turn");
				messageloop = 1;
			}
			checkTouch();
			// Once a touch has been recognized and the column selected in not full, we can continue
			if (tracker != trackerOld && grid[0][columnSelected] == 0){
				player1Select();
				Serial3.write(placedRow);
				delay(20);
				Serial3.write(columnSelected);
				tieNum = 0;
				checkWin();
				// If chain of 4 has been reached switch to mode 3 (PvP Win/Lose Screen)
				if (isWinNum == 4){
					mode = 3;
					break;
				}
				// If no win occurs for player 1 switch turns to player 2
				turn = 2;
				messageloop = 0;
			}
			trackerOld = tracker;
		}
		// Player with Arduino 1 and turn 2 means that this player must wait to receive
		// info about the placed chip from player 2
		else if (turn == 2 && digitalRead(digitalInPin) == HIGH) {
			readCounter = 0, tieNum = 0; // reset any maniuplated variables
			tft.setCursor(0,0);// rewrite over previous message and write waiting message in top bar
			tft.setTextColor(ILI9341_BLACK);
			tft.print("Your Turn");
			tft.setCursor(0,0);
			tft.setTextColor(ILI9341_WHITE);
			tft.print("Waiting for other player");
			getRowAndColumn();
			// Draw and assign the position on grid[][] with player 2's chip
			grid[placedRow][columnSelected] = player2Chip;
			comparePlacedChip = player2Chip;
			tft.fillCircle(22 + (columnSelected*45), 33 + (placedRow*36), 14, ILI9341_WHITE);
			checkWin();
			if (isWinNum == 4){
				mode = 3;
				break;
			}
			// Switch back to player 1's turn if a win was not reached
			turn = 1;
			messageloop = 0;
		}
		// Player with Arduino 2 and turn 2 means it is player 2's turn to play their move
		// The steps are the same except we need to have repeated code for player 2 and
		// player 1 because when the turn equals a certain number, each Arduino should be
		// doing the opposite tasks of each other and swtich tasks when the turns swtich.
		// So everything below is the same as above but for player 2.
		else if (turn == 2 && digitalRead(digitalInPin) == LOW) {
			if (messageloop == 0) {
				tft.setCursor(0,0);
				tft.setTextColor(ILI9341_BLACK);
				tft.print("Waiting for other player");
				tft.setCursor(0,0);
				tft.setTextColor(ILI9341_WHITE);
				tft.print("Your Turn");
				messageloop = 1;
			}
			tieNum = 0;
			checkTouch();
			if (tracker != trackerOld && grid[0][columnSelected] == 0){
				player2Select();
				Serial3.write(placedRow);
				delay(20);
				Serial3.write(columnSelected);
				checkWin();
				if (isWinNum == 4){
					mode = 3;
					break;
				}
				turn = 1;
				messageloop = 0;
			}
			trackerOld = tracker;
		}
		else if (turn == 1 && digitalRead(digitalInPin) == LOW){
			readCounter = 0, tieNum = 0;
			tft.setCursor(0,0);
			tft.setTextColor(ILI9341_BLACK);
			tft.print("Your Turn");
			tft.setCursor(0,0);
			tft.setTextColor(ILI9341_WHITE);
			tft.print("Waiting for other player");
			getRowAndColumn();
			grid[placedRow][columnSelected] = player1Chip;
			comparePlacedChip = player1Chip;
			tft.fillCircle(22 + (columnSelected*45), 33 + (placedRow*36), 14, ILI9341_RED);
			checkWin();
			if (isWinNum == 4){
				mode = 3;
				break;
			}
			turn = 2;
			messageloop = 0;
		}
	}

}
