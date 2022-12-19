#include "numbers.h"
#include <string.h>

int digit_zero[8][3] = {{1,1,1},
                        {1,0,1},
                        {1,0,1},
                        {1,0,1},
                        {1,0,1},
                        {1,0,1},
                        {1,0,1},
                        {1,1,1}};

int digit_one[8][3] = { {0,1,0},
                        {0,1,0},
                        {0,1,0},
                        {0,1,0},
                        {0,1,0},
                        {0,1,0},
                        {0,1,0},
                        {0,1,0}};

int digit_two[8][3] = { {1,1,1},
                    {1,0,1},
                    {1,0,1},
                    {0,0,1},
                    {0,1,0},
                    {1,0,0},
                    {1,0,0},
                    {1,1,1}};

int digit_three[8][3] = { {1,1,1},
                          {0,0,1},
                          {0,0,1},
                          {1,1,1},
                          {0,0,1},
                          {0,0,1},
                          {0,0,1},
                          {1,1,1}};

int digit_four[8][3] = { {1,0,1},
                          {1,0,1},
                          {1,0,1},
                          {1,0,1},
                          {1,1,1},
                          {0,0,1},
                          {0,0,1},
                          {0,0,1}};

int digit_five[8][3] = { {1,1,1},
                          {1,0,0},
                          {1,0,0},
                          {1,1,1},
                          {0,0,1},
                          {0,0,1},
                          {0,0,1},
                          {1,1,1}};  

int digit_six[8][3] = { {1,1,1},
                        {1,0,0},
                        {1,0,0},
                        {1,1,1},
                        {1,0,1},
                        {1,0,1},
                        {1,0,1},
                        {1,1,1}};

int digit_seven[8][3] = { {1,1,1},
                          {0,0,1},
                          {0,0,1},
                          {0,0,1},
                          {0,1,0},
                          {1,0,0},
                          {1,0,0},
                          {1,0,0}};

int digit_eight[8][3] = { {1,1,1},
                          {1,0,1},
                          {1,0,1},
                          {1,1,1},
                          {1,0,1},
                          {1,0,1},
                          {1,0,1},
                          {1,1,1}};
                        
int digit_nine[8][3] = { {1,1,1},
                        {1,0,1},
                        {1,0,1},
                        {1,1,1},
                        {0,0,1},
                        {0,0,1},
                        {0,0,1},
                        {1,1,1}};

// Set cooresponding digit pattern based on the digit num.
void setDigitPattern(int num, int digit_pattern[8][3]) {
    switch (num)
    {
    case 0:
        memcpy(digit_pattern, digit_zero, sizeof(int) * 8 * 3);     
        break;
    case 1:
    memcpy(digit_pattern, digit_one, sizeof(int) * 8 * 3);
        break;
    case 2:
        memcpy(digit_pattern, digit_two, sizeof(int) * 8 * 3);
        break;
    case 3:
        // digit_pattern = digit_three;
        memcpy(digit_pattern, digit_three, sizeof(int) * 8 * 3);
        break;
    case 4:
        // digit_pattern = digit_four;
        memcpy(digit_pattern, digit_four, sizeof(int) * 8 * 3);        
        break;
    case 5:
        memcpy(digit_pattern, digit_five, sizeof(int) * 8 * 3);
        break;
    case 6:
        memcpy(digit_pattern, digit_six, sizeof(int) * 8 * 3);
        break;
    case 7:
        memcpy(digit_pattern, digit_seven, sizeof(int) * 8 * 3);
        break;
    case 8:
        memcpy(digit_pattern, digit_eight, sizeof(int) * 8 * 3);
        break;
    case 9:
      memcpy(digit_pattern, digit_nine, sizeof(int) * 8 * 3);
        break;
    default:
        break;
    }
}

// Set pattern with the digit_pattern given that it is on the right side of display or left.
void drawDigit(bool isRight, int digit_pattern[8][3], int pattern[8][8]) {
    int offset = 0;
    if (isRight) { 
        offset = 5;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
          pattern[i][j + offset] = digit_pattern[i][j];
        }
    }
}
