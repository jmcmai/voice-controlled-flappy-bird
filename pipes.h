#pragma once

class Pipes {
    public:
        Pipes();
        int getXPosition();
        void setXPosition(int newXPosition);
        int getTopHeight();
        void setTopHeight(int newTopHeight);
        int getYGapRange();
        void setYGapRange(int newYGapRange);
        int getXGapRange();
        void setXGapRange(int newXGapRange);
        float getPipeVelocity();
        void setPipeVelocity(float newPipeVelocity);

    private:
        int _xPosition;
        int _topHeight;
        int _yGap;
        int _xGap;
        float _xVelocity;
};