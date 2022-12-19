#include "bird.h"
#include "pipes.h"
#include "numbers.h"

enum states {START = 0, GAMELOOP, END};

// set up arduino
const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};
const byte AUDIO_INPUT_PIN = A5; 

// set up audio
const int MIDPOINT = 513;
const int SAMPLETHRESHOLD = 50;

// set up display
static int pattern[8][8];

// Flappy Bird Setup
Bird bird;
Pipes first_pipe;
Pipes second_pipe;

int score;

unsigned long yVelocityTimer;
unsigned long yGravityTimer;
unsigned long xPipeVelocityTimer;
const unsigned long MAXYVELOCITY = .7;

unsigned long restartTime;

int state;

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);

    // turn all pins "off"
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
  
  pinMode(AUDIO_INPUT_PIN, INPUT);
  Serial.begin(115200);

  state = START;
}

void loop() {

  switch(state) {
    case START:  // set up game / reset game
      // set up bird
      bird.setYPosition(3);
      bird.setYVelocity(0);

      // set up pipes
      first_pipe.setXPosition(6);
      second_pipe.setXPosition(11);

      clearDisplay(pattern);     
      display(pattern);

      score = 0;

      // setup timers
      yVelocityTimer = millis();
      yGravityTimer = millis();
      xPipeVelocityTimer = millis();
      restartTime = 0;

      state = GAMELOOP;    
      break;
    case END:  // display score
      setDisplayScore(score, pattern);
      display(pattern);   
      clearDisplay(pattern); 
       
      if (millis() > restartTime) {
        state = START; 
      }

      break;
    case GAMELOOP:  // in game
      // check bird jump
      int sample = getSample();
      if (abs(sample) > SAMPLETHRESHOLD) {
        bird.jump(bird.getJumpForce());
      }

      // check physics
      updateBirdVelocity(bird, yGravityTimer);
      updateBirdPosition(bird, yVelocityTimer);
      updatePipePosition(first_pipe, second_pipe, xPipeVelocityTimer);

      // display the bird and pipe to screen
      displayBird(bird);  
      displayPipes(first_pipe);
      displayPipes(second_pipe);

      if (hasCollided(bird, first_pipe, second_pipe)) {
        // Game over if bird collides with a pipe
        state = END; 
        restartTime = millis() + 3000;      
      }

      break;
    default: 
      Serial.println("Invalid state");
      break;
  }
}

// Helper functions

/*
 * PHYSICS FUNCTIONS
 */

// Function to detect collisions
bool hasCollided(Bird &bird, Pipes &first_pipe, Pipes &second_pipe) {
  int yBirdPosition = 7 - bird.getYPosition();
  if (bird.getXPosition() == first_pipe.getXPosition()) {
    if ((yBirdPosition < first_pipe.getTopHeight()) || (yBirdPosition > first_pipe.getTopHeight() + first_pipe.getYGapRange() - 1)) { // collided
      // Bird collided with pipe 1
      return true;
    }
  } else if (bird.getXPosition() == second_pipe.getXPosition()) {
    if ((yBirdPosition < second_pipe.getTopHeight()) || (yBirdPosition > second_pipe.getTopHeight() + second_pipe.getYGapRange() - 1)) {  // collided
      // Bird collided with pipe 2
      return true;            
    }
  }
  return false;
}

// Function to update the x-position of the pipes
void updatePipePosition(Pipes &first_pipe, Pipes &second_pipe, unsigned long&xPipeVelocityTimer) {
  // velocity is m/s, so timer is inverse of velocity
  unsigned long currPipeVelocityTime = first_pipe.getPipeVelocity();
  int pipesXGap = first_pipe.getXGapRange();
  if (millis() - xPipeVelocityTimer >= currPipeVelocityTime) {
    if (first_pipe.getXPosition() > 0) {
      first_pipe.setXPosition(first_pipe.getXPosition() - 1);
    } else {  // wrap around the map and change top pipe height btwn 1 and 4
      score++;      
      int randomTopHeight = random(1, 5);
      first_pipe.setTopHeight(randomTopHeight);
      first_pipe.setXPosition(second_pipe.getXPosition() + pipesXGap - 1); 
    }

    if (second_pipe.getXPosition() > 0) {
      second_pipe.setXPosition(second_pipe.getXPosition() - 1);
    } else {  // wrap around the map and change top pipe height btwn 1 and 4
      score++;
      int randomTopHeight = random(1, 5);
      second_pipe.setTopHeight(randomTopHeight);
      second_pipe.setXPosition(first_pipe.getXPosition() + pipesXGap);      
    }
    xPipeVelocityTimer = millis();            
  }
}

// Function to update y-position of the bird depending on velocity
void updateBirdPosition(Bird &bird, unsigned long &yVelocityTimer) {
  if (bird.getYVelocity() != 0.0) {
    // velocity is m/ms, so to get milliseconds we take the inverse
    unsigned long currVelocityTime = abs(1/bird.getYVelocity());
    if (millis() - yVelocityTimer >= currVelocityTime) {
      // only need to change position when there is velocity and bird is above ground
      if (bird.getYVelocity() > 0.0 && bird.getYPosition() < 7) {
        bird.setYPosition(bird.getYPosition() + 1);
      } else if (bird.getYVelocity() < 0.0 && bird.getYPosition() > 0) {
        bird.setYPosition(bird.getYPosition() - 1);
      }
      yVelocityTimer = millis();
    }
  }
}

// Function to update y-velocity of bird (down only)
void updateBirdVelocity(Bird &bird, unsigned long &yGravityTimer) {
  // Gravity is m/ms^2, so to get ms^2 we take the inverse of gravity
  unsigned long currGravityTime = (unsigned long) abs(1/bird.getYGravity());
  // Check if the time is long enough to update the velocity of the bird
  if (millis() - yGravityTimer >= currGravityTime) {
    if (bird.getYPosition() == 7) {
      // Bird hit the ceiling, so the velocity should also be 0
      bird.setYVelocity(0.0);
      bird.setYPosition(6);  // bounces off the ceiling
    }

    // If bird is above ground, update velocity (subtract force of gravity)
    if (bird.getYPosition() > 0) {
      // Bird should be falling
      float newYVelocity = bird.getYVelocity() - bird.getYGravity();
      bird.setYVelocity(min(newYVelocity, MAXYVELOCITY));
    } else if (bird.getYPosition() <= 0 && bird.getYVelocity() != 0.0) {
      bird.setYVelocity(0.0);
      bird.setYPosition(0);
    }
    yGravityTimer = millis();
  }
}

/*
 * AUDIO FUNCTION
 */ 

/* Function: getSample
 * -------------------
 * Returns an unbiased sample of the audio signal. The returned value will be
 * "centered around zero", i.e., sometimes positive and sometimes negative.
 */
int getSample() {
  int sample = analogRead(AUDIO_INPUT_PIN); 
  sample -= MIDPOINT;
  return sample;
}

/*
 * DISPLAY FUNCTIONS
 */

// Function to display the bird
void displayBird(Bird &bird) {
  int yPosition = 7 - bird.getYPosition();
  digitalWrite(ANODE_PINS[yPosition], LOW);
  digitalWrite(CATHODE_PINS[bird.getXPosition()], LOW);
  
  delayMicroseconds(500);

  digitalWrite(ANODE_PINS[yPosition], HIGH);
  digitalWrite(CATHODE_PINS[bird.getXPosition()], HIGH);
}

// Function to display the pipes
void displayPipes(Pipes &pipe) {
  for (int row = 0; row < 8; row++) {
    digitalWrite(ANODE_PINS[row], LOW);
    if (row < pipe.getTopHeight() || row > pipe.getTopHeight() + pipe.getYGapRange() - 1) {
      digitalWrite(CATHODE_PINS[pipe.getXPosition()], LOW);
    }    
    delayMicroseconds(500);
    digitalWrite(ANODE_PINS[row], HIGH);
    digitalWrite(CATHODE_PINS[pipe.getXPosition()], HIGH); 
  }
}

// Function to clear display
void clearDisplay(int pattern[8][8]) {
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 8; j++) {
      pattern[i][j] = 0;
    }
  }  
}

// Function to set digit pattern
void setDisplayScore(int score, int pattern[8][8]) {
  int digit_pattern[8][3];

  // Logic to parse number places, if over 100 display 99
  if (score >= 100) {
    score = 99;
  }

  int onesPlace = score % 10;
  setDigitPattern(onesPlace, digit_pattern);
  drawDigit(true, digit_pattern, pattern);

  int tensPlace = score / 10;
  setDigitPattern(tensPlace, digit_pattern);
  drawDigit(false, digit_pattern, pattern);
}

// Display function to display pattern to LEDs
void display(int pattern[8][8]) {
    for (byte i = 0; i < 8; i++) {
      for (byte j = 0; j < 8; j++) {
        if (pattern[i][j] >= 1) {
           // activate cathode
          digitalWrite(CATHODE_PINS[j], LOW); 
        } else {
          // deactivate cathode
          digitalWrite(CATHODE_PINS[j], HIGH);
        }
      }
      // activate anode
      digitalWrite(ANODE_PINS[i], LOW);
      delayMicroseconds(500);
      // deactivate anode
      digitalWrite(ANODE_PINS[i], HIGH);
    }
}



