/*
 * Ian Crochet[squidjerky] April 24, 2021
 * Inspo-bot Project for the 
 * Dimensions of a basic 3 x 5 index card = 76.2 x 127 mm
 * Distance for each step = (12 * pi)/32 = 1.178 mm
 * 
 * Assume that for the x axis you want to fit 20 characters INCLUDING WHITESPACE per line
 * Assume that for the length of the y axis there are 11 divisions of new lines based on the lining of the notecard
 * 
 * Width of each character including character separation = 76.2 / 20 = 3.81mm (about 3 steps)
 * * 3.81mm = character width + character separation = 2.632(2 steps) + 1.178(1 step)
 * Maximum steps for the X axis = 76.2 / 1.178 = 64.6859 or just 64 steps maximum
 * 
 * Length of each character = 127 / 11 = 11.545mm (9.8 or 10 steps)
 * Maximum steps for the Y axis = 127 / 1.178 = 107.8 or just 107 steps maximum
 * 
 * Assume you want to only lift the pencil by half an inch
 * 0.5 inches = 12.7 mm or `13 mm
 * 13 / 1.178 = 11 steps
 */
#include <Stepper.h>
const float STEPS_PER_REV = 32;
const float GEAR_REDUCTION = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_REDUCTION;

const int MAX_X = 64;
const int MAX_Y = 107;
const int deltaZ = 11;

const int CHAR_WIDTH = 2;
const int CHAR_SPACE = 1;
const int CHAR_HEIGHT = 9;
const int LINE_HEIGHT = 10;

int countX = 0;
int countY = 0;
int strCurr = 0;

Stepper zStep(STEPS_PER_REV, 1, 2, 3, 4); //EDIT THE PINS LATER
Stepper xStep(STEPS_PER_REV, 5, 6, 7, 8); //EDIT THE PINS LATER
Stepper yStep(STEPS_PER_REV, 9, 10, 11, 12); //EDIT THE PINS LATER

String inputString = "test";

void setup() {
  zStep.setSpeed(500);
  xStep.setSpeed(500);
  yStep.setSpeed(500);
  zStep.step(-1 * deltaZ);
  //yStep.step(LINE_HEIGHT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  while(countY < MAX_Y){
    while(countX < MAX_X){
      if(strCurr < (inputString.length() - 1)){
        writeLetter(inputString.charAt(strCurr));
        strCurr++;
      }
      else{
        countX = MAX_X;
        countY = MAX_Y;
      }
    }
    xStep.step(-1 * countX);
    countX = 0;
    yStep.step(LINE_HEIGHT);
    countY += LINE_HEIGHT;
  }
  yStep.step(-1 * countY);
}

void writeLetter(char inp){ //for now it just makes a line to test whether character spacing works
  zStep.step(deltaZ);
  //xStep.step(CHAR_WIDTH);
  int fullL = CHAR_HEIGHT;
  int negFullL = -CHAR_HEIGHT;
  int fullW = CHAR_WIDTH;
  int negFullW = -CHAR_WIDTH;
  int halfL = CHAR_HEIGHT / 2;
  int negHalfL = -CHAR_HEIGHT / 2;
  int halfW = CHAR_WIDTH / 2;
  int negHalfW = -CHAR_WIDTH / 2;
  switch(inp){
    case 'a':
    case 'A':
        yStep.step(fullL);
        yStep.step(negHalfL);
        xStep.step(fullW);
        yStep.step(negHalfL);
        xStep.step(negFullW);
        yStep.step(halfL);
        xStep.step(fullW);
        yStep.step(halfL);
        yStep.step(negFullL);
    break;
    case 'b':
    case 'B':
        yStep.step(fullL);
        xStep.step(fullW);
        yStep.step(negFullL);
        xStep.step(negFullW);
        yStep.step(halfL);
        xStep.step(fullW);
        yStep.step(negHalfL);
    break;
    case 'c':
    case 'C':
         yStep.step(fullL);
         xStep.step(fullW);
         xStep.step(negFullW);
         yStep.step(negFullL);
         xStep.step(fullW);
    break;
    case 'd':
    case 'D':

    break;
    case 'e':
    case 'E':

    break;
    case 'f':
    case 'F':

    break;
    case 'g':
    case 'G':

    break;
    case 'h':
    case 'H':

    break;
    case 'i':
    case 'I':

    break;
    case 'j':
    case 'J':

    break;
    case 'k':
    case 'K':

    break;
    case 'l':
    case 'L':

    break;
    case 'm':
    case 'M':

    break;
    case 'n':
    case 'N':

    break;
    case 'o':
    case 'O':

    break;
    case 'p':
    case 'P':

    break;
    case 'q':
    case 'Q':

    break;
    case 'r':
    case 'R':

    break;
    case 's':
    case 'S':

    break;
    case 't':
    case 'T':

    break;
    case 'u':
    case 'U':

    break;
    case 'v':
    case 'V':

    break;
    case 'w':
    case 'W':

    break;
    case 'x':
    case 'X':

    break;
    case 'y':
    case 'Y':

    break;
    case 'z':
    case 'Z':

    break;
    default:
      xStep.step(fullW);
    break;
  }
  zStep.step(-1 * deltaZ);
  xStep.step(CHAR_SPACE);
}
