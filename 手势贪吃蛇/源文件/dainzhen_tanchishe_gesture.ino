/*
name:Snake game made with the Gesture Sensor
version:  1.0
Author:  Lin <824676271@qq.com>
Date:    2016-08-18
Description:  红外手势贪吃蛇
note: 首先,把 LedControl 和 SparkFun_APDS9960 的库通通丢进libraries里
*/
#include "LedControl.h" 


LedControl lc = LedControl(12, 11, 10, 1); //(DIN, CLK, CS, Amount of MAX7219)

int joyPin1 = 0; //Variable that gets the anolog value in the x direction.
int joyPin2 = 1; //Variable that gets the analog value in the y direction.
int xAxis = 0; //Variable that stores the value gotten from joyPin1.
int yAxis = 0; //Variable that stores the value gotten from joyPin2.

String direction; //Variable that stores the direction the snake is moving in.

int snakeX[36]; //Variable that stores all the x coordinates of the snake.
int snakeY[36]; //Variable that stores all the y coordinates of the snake.

int speed = 300; //Delay time for each movement.

int snakeSize; //Head + Body size of the snake.

int foodX; //Variable that stores the x coordinate of the food.
int foodY; //Variable that stores the y coordinate of the food.

boolean inGame = false; //Variable that tells us if the game is running.

//This method is called once on startup.
void setup() {
    lc.shutdown(0, false); //Turn off power saving, enables display
    lc.setIntensity(0, 8); //Brightness (0-15)
    lc.clearDisplay(0); //Clear Screen
    Serial.begin(9600);
    
    newGame(); //Call newGame() to setup everything.
}

//This method loops through itself.
void loop() {
    if(inGame) { //Checks if game is running. 
        lc.clearDisplay(0); //Clear screen.
      
        xAxis = simple(analogRead(joyPin1)); //Gets the value of the x axis.
        yAxis = simple(analogRead(joyPin2)); //Gets the value of the y axis.
      
        Serial.print(xAxis); //Prints the x axis to the serial for debugging.
        Serial.println(yAxis); //Prints the y axis to the serial for debugging.
        
        if(yAxis > 5 && direction != "up") { //If player moves the analog stick up, and if snake isn't going down.
            direction = "down";
        }
        if(yAxis < 3 && direction != "down") { //If player moves the analog stick down, and if snake isn't going up.
            direction = "up";
        }
        if(xAxis > 5 && direction != "left") { //If player moves the analog stick right, and if snake isn't going left.
            direction = "right";
        }
        if(xAxis < 3 && direction != "right") { //If player moves the analog stick left, and if snake isn't going right.
            direction = "left";
        }
        
        move(direction); //Move the snake in the direction.
        
        checkIfHitFood(); //Checks if the snake moves onto the food.
        checkIfHitSelf(); //Checks if the snake hits itself.
        
        drawSnake(); //Draws the snake on the MAX7219.
        drawFood(); //Draws the food on the MAX7219.
        
        delay(speed); //Delay with the configured time from above.
    }
}

//This method returns a more simple value to work with when reading the analogs.
//Returns and int that is 0-8.
int simple(int num) {
    return (num * 9 / 1024);
}

//This method makes the snake move in the direction provided in the param.
void move(String dir) {
    for(int i=snakeSize-1; i>0; i--){ //Go through all the snake body parts (excluding the head), and set it to the previous position.
        snakeX[i] = snakeX[i-1];
  snakeY[i] = snakeY[i-1];
    }

    if(dir == "up") {
  if(snakeY[0] == 0) { //If snake tries to get out of bounds, teleport him on the opposite side.
      snakeY[0] = 7;
  } else {
            snakeY[0]--;
  }
    } else if(dir == "down") {
  if(snakeY[0] == 7) { //If snake tries to get out of bounds, teleport him on the opposite side.
      snakeY[0] = 0;
  } else {
      snakeY[0]++;
        }
    } else if(dir == "left") {
  if(snakeX[0] == 0) { //If snake tries to get out of bounds, teleport him on the opposite side.
      snakeX[0] = 7;
  } else {
      snakeX[0]--;
  }
    } else if(dir == "right") {
  if(snakeX[0] == 7) { //If snake tries to get out of bounds, teleport him on the opposite side.
      snakeX[0] = 0;
  } else {
      snakeX[0]++;
  }
    }
}

//This method loops through all the snake parts and draws them on the MAX7219.
void drawSnake() {
    for (int i = 0; i < snakeSize; i++) {
        lc.setLed(0, snakeY[i], snakeX[i], true);
    }
}

//This method draws the food on the MAX7219.
void drawFood() {
    lc.setLed(0, foodY, foodX, true);
    delay(50); //Have a short delay here to make the food blink and differentiate from the snake parts.
    lc.setLed(0, foodY, foodX, false);
}

//This method sets a new location of the food randomly.
void newFood() {
    int newFoodX = random(0, 8);
    int newFoodY = random(0, 8);
    while(isSnake(newFoodX, newFoodY)){ //If the new food coordinates are in the snake, then keep trying until they're not.
        newFoodX = random(0, 8);
  newFoodY = random(0, 8);
    }
    foodX = newFoodX;
    foodY = newFoodY;
}

//This method checks if the snake moves onto the food.
void checkIfHitFood() {
    if(snakeX[0] == foodX && snakeY[0] == foodY) {
  snakeSize++; //Add a snake body part.
  newFood(); //Create a new food at a new location.
    }
}

//This method checks if the snake moves onto itself.
void checkIfHitSelf() {
    for(int i=1; i<snakeSize-1; i++){
  if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver(); //Call the gameOver() method.
  }
    }
}

//Checks if the given coordinates are part of the snake.
//Used when checking where to generate new food.
boolean isSnake(int x, int y){
    for(int i=0; i<snakeSize-1; i++){
        if((x == snakeX[i]) && (y == snakeY[i])){
            return true;
        }
    }
    return false;
}

//This method sets all the variables for a new game.
void newGame() {
    for(int i=0; i<36; i++) { //Set all the values in the snake array to be off the screen, just in case.
        snakeX[i] = -1;
        snakeY[i] = -1;
    }
  
    snakeX[0] = 4; //Start at x4.
    snakeY[0] = 8; //Start at y8.
    direction = "up"; //Start with moving upward.
    snakeSize = 1; //Start with only 1 snake part. (Which is the snake head)
    newFood(); //Randomly create a new food.
    inGame = true; //Set this variable to true so the loop() method could start.
}

//This method is called when the snake hits itself.
//It loops through all the coordinates of the MAX7219, making a fancy pattern.
void gameOver() {
    inGame = false; //Makes sure the game is stopped.
    for(int x=0; x<8; x++) {
       for(int y=0; y<8; y++) {
           lc.setLed(0, y, x, true);
           delay(20);
           lc.setLed(0, y, x, false);
       }
    }
    newGame(); //Starts a new game.
}
