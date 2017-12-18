/*
	Project: Player Vs Player Win Condition checks
	In this file are the functions used in the player vs player game mode
	to check if a chain of 4 chips is reached. These checks will be used by both
	player 1 and player 2, so comparePlacedChip will be either player1Chip or player2Chip
*/
#include "pvpcheck.h"
// Check the vertical direction but only below from the last placed chip, because
// the chips fall to the bottom row that can be filled.
void checkVert(){
	while (true){
		// Check if the row below is the same chip as player's chip
		if (grid[placedRow + index][columnSelected] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		// If the next position is empty or the opponent's chip, it will break the chain
		else{
			break;
		}
	}
}
// Check the horizontal for a chain of 4
void checkHoriz(){
	// Check the right direction for the same chip as the player's last placed chip.
	while (true){
		if (grid[placedRow][columnSelected + index] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		// If a chain of 4 has been reached or the index is outside the boundaries.
		else if (isWinNum == 4 || columnSelected + index == 7){
			break;
		}
		else {
			break;
		}
	}
	// If a chain of 4 has not been reached, check the left direction.
	if (isWinNum < 4){
		// Start at the left position next to the player's last placed chip.
		index = 1;
		while (true){
			if (grid[placedRow][columnSelected - index] == comparePlacedChip ){
				isWinNum++;
				index++;
			}
			// Break if the chain of 4 is reached or indexing outside boundaries of the array.
			else if (isWinNum == 4 || columnSelected - index == -1) {
				break;
			}
			else {
				break;
			}
		}
	}
}
// Check the Diagonal left direction with the same checks as the horizontal function,
// but in diagonal direction.
void checkDiaginolLeft(){
	while (true){
		if (grid[placedRow + index][columnSelected + index] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		else {
			break;
		}
	}
	if (isWinNum < 4){
		index = 1;
		while(true){
			if (placedRow - index == -1){
				break;
			}
			if (grid[placedRow - index][columnSelected - index] == comparePlacedChip){
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}
	}
}
// Check the diagonal right direction, using same checks as in other functions.
void checkDiaginolRight(){
	while (true){
		if (grid[placedRow - index][columnSelected + index] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		else {
			break;
		}
	}
	if (isWinNum < 4){
		index = 1;
		while(true){
			if (grid[placedRow + index][columnSelected - index] == comparePlacedChip){
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}
	}
}
// Combines all the win condition checks and will reset isWinNum and index to zero
// at each direction check. If the isWinNum == 4 then it will skip any of the other
// direction checks because a chain of 4 was reached.
void checkWin(){
	isWinNum = 0;
	index = 0;
	checkVert();
	if (isWinNum < 4){
		isWinNum = 0;
		index = 0;
		checkHoriz();
	}
	if (isWinNum < 4){
		isWinNum = 0;
		index = 0;
		checkDiaginolLeft();
	}
	if (isWinNum < 4){
		isWinNum = 0;
		index = 0;
		checkDiaginolRight();
	}
	// If none of the directions got a chain of 4, then check if the board is full for a tie.
	if (isWinNum < 4){
		for (int i = 0; i < 7; i++){
			if (grid[0][i] != 0){
				tieNum++;
			}
		}
	}
}
