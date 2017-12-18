# ConnectFour-Game-ArduinoMega2560
Project: ConnectFour

Accessories:
- 2x Arduino Mega Board (AMG)
- USB cable, A-B style
- Adafruit ILI9341 breakout board


Wiring Instructions:
Instructions to wiring the Adafruit_ILI9341 screen.
https://eclass.srv.ualberta.ca/pluginfile.php/3891315/mod_resource/content/1/cmput274-display-wiring.txt

- TX3 Pin Arduino A <--> RX3 Pin Arduino B
- TX3 Pin Arduino B <--> RX3 Pin Arduino A
- Pin 13 Arduino A <--> 5V Arduino B
- GND Arduino A <--> GND Arduino B
- NOTE: Leave analog pin A1 empty (nothing plugged in)

How to run the Code:
Using the Makefile that was given to us, make upload-0 the code into Arduino A
and make upload-1 the code into Arduino B and look at display screens.

Assumptions:
- There were a couple of bugs with the horizontal win condition checks for both PvP mode
	and Player vs AI mode. For the first, when the players had chains longer than 4 horizontally
	the win screen wouldn't show up and for the latter, the AI would block when 2 of the
	player's chip were in a row and then skip it's turn when 3 were in a row (Skip in the sense that
	the AI would place it's chip at -1 because of how the zero position is recorded).


Description:
This program is a program that implements the game ConnectFour with a Player Vs Player mode
as well as a Player Vs AI mode. In the Player Vs Player mode, two Arduinos will comminicate
with each other sending both players turns to each other. Once one player has achieved a
chain of 4 of their chips in a row, a win screen will be displayed on that player's Arduino
and a losing screen for the other player on their Arduino. It will also allow both players to
then select which game mode they want to play after each game mode.
Then in the Player Vs AI mode, is an AI that we implemented ourselves. This AI will look on
the game board and see if the player has any possible wins and try to block the player. If
the AI can not find any places to block the player, it will simply place it's chip in any
position it wants.
