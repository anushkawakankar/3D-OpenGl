#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    float radius;
    float rotationy;
    bool active;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y);
private:
    VAO *object1;
};

#endif // BALL_H
