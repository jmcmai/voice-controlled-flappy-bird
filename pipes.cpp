#include "pipes.h"
using namespace std;

Pipes::Pipes() {
    // constructor
    _xPosition = 5;
    _topHeight = 2;
    _yGap = 3;
    _xGap = 5;
    _xVelocity = 500.0;
}

int Pipes::getXPosition() {
    return _xPosition;
}

void Pipes::setXPosition(int newXPosition) {
    _xPosition = newXPosition;
}

int Pipes::getTopHeight() {
    return _topHeight;
}

void Pipes::setTopHeight(int newTopHeight) {
    _topHeight = newTopHeight;
}

int Pipes::getYGapRange() {
    return _yGap;
}

void Pipes::setYGapRange(int newYGapRange) {
    _yGap = newYGapRange;
}

void Pipes::setXGapRange(int newXGapRange) {
    _xGap = newXGapRange;
}

int Pipes::getXGapRange() {
    return _xGap;
}

float Pipes::getPipeVelocity() {
    return _xVelocity;
}

void Pipes::setPipeVelocity(float newPipeVelocity) {
    _xVelocity = newPipeVelocity;
}

