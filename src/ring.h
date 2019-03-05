#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float z);
    glm::vec3 position;
    float radius;
    bool active;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object1;
};

#endif // BALL_H
