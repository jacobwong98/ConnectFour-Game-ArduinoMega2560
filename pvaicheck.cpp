/*
	Project: Player Vs AI Win Condition Checks
	In this file are all the functions used by the "AI" to check where it should
	place it's chip to block the player
*/
#include "pvaicheck.h"

// Check the chips below the user's last place chip
void AICheckVert(){
	while (true){
		if (grid[placedRow + index][columnSelected] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		else{
			break;
		}
	}
	// If there is a chain of 3 and the position above the user's chip is empty,
	// have the AI place it's chip in that position.
	if (isWinNum == 3 && (placedRow - 1) == 0){
		grid[placedRow - 1][columnSelected] = player2Chip;
		tft.fillCircle(22 + (columnSelected*45), 33 + ((placedRow - 1)*36), 14, ILI9341_WHITE);
		turn = 1; // switch turns
	}
}
// Check the chips to the right and left of the user's placed chips, with condition
// that a single empty position could complete the 4 in a row.
void AICheckHoriz(){
	// Check the chips to the right of the user's placed chip
	while (true){
		if(isWinNum == 4){
			break;
		}
		// Check if the next right position is a zero (empty)
		else if (grid[placedRow][columnSelected + index] == 0){
			// Check if the position below the empty position is filled or in the bottom
			// row of the gameboard. As well we wanted to make sure that an empty cell
			// was already not being stored.
			if ((grid[placedRow + 1][columnSelected + index] != 0 || placedRow == 5)
					&& compareColumn == -1){
				compareColumn = columnSelected + index;
				isWinNum++;
				index++;
			}
			else{
				// Some boundary cases, when the chip is placed in the rightmost or second from
				// the right position, wanted to check other positions to the left to see
				// if we should ignore the empty cell on the right. isWinNum == 2 is the case
				// when the user's chip is the rightmost chip and isWinNum is the user's chip
				// placed in the second from the right position with another one of the user's
				// chip next to it.
				if ((isWinNum == 2 && (grid[placedRow][columnSelected -2] == 0 || grid[placedRow][columnSelected - 1] == 0))
						|| (isWinNum == 3 && (grid[placedRow][columnSelected - 1] == 0 || grid[placedRow][columnSelected + 1] == 0))){
					compareColumn = -1;
				}
				break;
			}
		}
		// Check if the next right position is the user's chip
		else if (grid[placedRow][columnSelected + index] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		else {
			break;
		}
	}
	// If the right direction did not create a chain of 4, check the left direction.
	if (isWinNum < 4){
		// Start from position left position next to the user's placed chip.
		index = 1;
		while (true){
			// Break if chain of 4 exists or accessing index outside boundaries of array.
			if(isWinNum == 4 || (columnSelected - index) == -1){
				break;
			}
			// Checks if zero similar to the right direction check. No need to "reset"
			// position of the zero because once we go thorugh left direction and there
			// are two zero positions, we want to record at least one of the positions.
			else if (grid[placedRow][columnSelected - index] == 0){
				if ((grid[placedRow + 1][columnSelected - index] != 0 || placedRow == 5) && compareColumn == -1){
					compareColumn = columnSelected - index;
					isWinNum++;
					index++;
				}
				else {
					break;
				}
			}
			// Check if the next left position is the same as the user's chip.
			else if (grid[placedRow][columnSelected - index] == comparePlacedChip){
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}
	}
	// If a chain of 4 is reached (with at least one position being empty), place in
	// the empty position.
	if (isWinNum == 4){
		grid[placedRow][compareColumn] = player2Chip;
		tft.fillCircle(22 + (compareColumn*45), 33 + (placedRow*36), 14, ILI9341_WHITE);
		turn = 1; // switch turnss
	}
}
// Check the Diagonal left direction.
void AICheckDiaginolLeft() {
	while (true){
		// Break if chain of 4 reached or indexes are outside the boundaries.
		// Also start our checks in the direction of downward right.
		if(isWinNum == 4 || (columnSelected + index) == 7 || (placedRow + index) == 6){
			break;
		}
		// Check if the next position is empty.
		else if (grid[placedRow + index][columnSelected + index] == 0){
			// Check if the position below the empty position is filled or
			// if the index of the empty cell is the bottom right corner of the gameboard.
			// Also want to make sure that an empty cell has not already been recorded.
			if ((grid[placedRow + index + 1][columnSelected + index] != 0
					|| (placedRow + index) == 5 || (columnSelected + index == 6)) && compareColumn == -1 && compareRow == -1){
				compareColumn = columnSelected + index;
				compareRow = placedRow + index;
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}
		// Check if the next position is the same chip as the user's chip.
		else if (grid[placedRow + index][columnSelected + index] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		else {
			break;
		}
	}
	// Want to check the upward left direction is a chain of 4 has not been reached.
	if (isWinNum < 4){
		// Start from the next upward left position from the user's last placed chip.
		// Run the same checks as the downward right direction but in opposite direction.
		index = 1;
		while (true){
			if(isWinNum == 4 || (columnSelected - index) == -1 || (placedRow - index) == -1){
				break;
			}
			else if (grid[placedRow - index][columnSelected - index] == 0){
				if ((grid[placedRow - index + 1][columnSelected - index] != 0) && compareColumn == -1 && compareRow == -1){
					compareColumn = columnSelected - index;
					isWinNum++;
					index++;
				}
				else {
					break;
				}
			}
			else if (grid[placedRow - index][columnSelected - index] == comparePlacedChip){
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}

	}
	// Place chip in the empty position if a chain of 4 has been reached.
	if (isWinNum == 4){
		grid[compareRow][compareColumn] = player2Chip;
		tft.fillCircle(22 + (compareColumn*45), 33 + (compareRow*36), 14, ILI9341_WHITE);
		turn = 1;
	}
}
// Checks the diagonal right direction. This function runs the same check as
// AICheckDiaginolLeft().
void AICheckDiaginolRight(){
	while (true){
		if(isWinNum == 4 || (columnSelected + index) == 7 || (placedRow + index) == 6){
			break;
		}
		else if (grid[placedRow - index][columnSelected + index] == 0){
			if ((grid[placedRow - index + 1][columnSelected + index] != 0) && compareColumn == -1 && compareRow == -1){
				compareColumn = columnSelected + index;
				compareRow = placedRow - index;
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}
		else if (grid[placedRow - index][columnSelected + index] == comparePlacedChip){
			isWinNum++;
			index++;
		}
		else {
			break;
		}
	}
	if (isWinNum < 4){
		index = 1;
		while (true){
			if(isWinNum == 4 || (columnSelected - index) == -1 || (placedRow - index) == -1){
				break;
			}
			else if (grid[placedRow + index][columnSelected - index] == 0){
				if ((grid[placedRow + index + 1][columnSelected - index] != 0
						|| (placedRow + index) == 5 || (columnSelected - index == 0)) && compareColumn == -1 && compareRow == -1){
					compareColumn = columnSelected - index;
					compareRow = placedRow + index;
					isWinNum++;
					index++;
				}
				else {
					break;
				}
			}
			else if (grid[placedRow + index][columnSelected - index] == comparePlacedChip){
				isWinNum++;
				index++;
			}
			else {
				break;
			}
		}

	}
	if (isWinNum == 4){
		grid[compareRow][compareColumn] = player2Chip;
		tft.fillCircle(22 + (compareColumn*45), 33 + (compareRow*36), 14, ILI9341_WHITE);
		turn = 1;
	}
}

void AICheckWin(){
	// Check the Vert, Horiz, Diagonal Left and Diagonal Right based on user's last
	// placed chip position
	isWinNum = 0;
	index = 0;
	AICheckVert();
	if (turn != 1){
		compareColumn = -1;
		isWinNum = 0;
		index = 0;
		AICheckHoriz();
	}
	if (turn != 1){
		compareColumn = -1;
		compareRow = -1;
		isWinNum = 0;
		index = 0;
		AICheckDiaginolLeft();
	}
	if (turn != 1){
		compareColumn = -1;
		compareRow = -1;
		isWinNum = 0;
		index = 0;
		AICheckDiaginolRight();
	}
	// Check the directions (except vertical) for the position above the user's last
	// placed chip to see if their placed chip set up a potential 4 in a row elsewhere
	placedRow -= 1;
	if (turn != 1){
		compareColumn = -1;
		isWinNum = 0;
		index = 0;
		AICheckHoriz();
	}
	if (turn != 1){
		compareColumn = -1;
		compareRow = -1;
		isWinNum = 0;
		index = 0;
		AICheckDiaginolLeft();
	}
	if (turn != 1){
		compareColumn = -1;
		compareRow = -1;
		isWinNum = 0;
		index = 0;
		AICheckDiaginolRight();
	}
	// Reset placeRow back to original value just in case
	placedRow += 1;
}
