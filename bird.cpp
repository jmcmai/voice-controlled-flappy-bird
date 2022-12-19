#include "bird.h"
using namespace std;

Bird::Bird() {
        _xPosition = 1;
        _yPosition = 3;
        _yVelocity = 0.0;
        _yGravity = 1/650.0; 
        _jumpForce = 0.001;
}

// getters and setters
int Bird::getXPosition() {
    return _xPosition;
}

int Bird::getYPosition() {
    return _yPosition;
}

void Bird::setYPosition(int newYPosition) {
    if (newYPosition <= 7 && newYPosition >= 0 ) {  // check if valid position to be in
        _yPosition = newYPosition;
    }
}

float Bird::getYVelocity() {
    return _yVelocity;
}

void Bird::setYVelocity(float newYVelocity) {
    _yVelocity = newYVelocity;
}

float Bird::getYGravity() {
    return _yGravity;
}

void Bird::setYGravity(float newYGravity) {
    _yGravity = newYGravity;
}

float Bird::getJumpForce() {
  return _jumpForce;
}
void Bird::setJumpForce(float newJumpForce) {
  _jumpForce = newJumpForce;
}

void Bird::jump(float jumpForce) {
    _yVelocity += jumpForce;
}

