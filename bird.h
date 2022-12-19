#pragma once

class Bird {
    public:
        Bird();  // creates new Bird object
        int getXPosition();
        void setXPosition(int newXPosition);
        int getYPosition();
        void setYPosition(int newYPosition);
        float getYGravity();
        void setYGravity(float newYGravity);
        float getYVelocity();
        void setYVelocity(float newYVelocity);
        float getJumpForce();
        void setJumpForce(float newJumpForce);

        void jump(float jumpForce);

    private:
        int _xPosition;
        int _yPosition;
        float _yVelocity;
        float _yGravity;
        float _jumpForce;
};

