#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float rot);
    glm::vec3 position;
    float rotationy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
    VAO *object2;
};

#endif // BULLET_H
