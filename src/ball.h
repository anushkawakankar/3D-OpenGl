#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y);
    glm::vec3 position;
    float rotationx;
    float rotationy;
    float rotationz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    float fuel;
    double speed;
    double yspeed;
   float Yrotation;
   float upStep;
   float acc;
   float downyspeed;
private:
    VAO *objectbody;
    VAO *objectwings;

};

#endif // BALL_H
