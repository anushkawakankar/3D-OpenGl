#include "main.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float z);
    glm::vec3 position;
    float radius;
    bool active;
    float rotationy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    void tick();
    void tick2();
    double upspeed;
    double acceleration;
    double xspeed;
    double downspeed;
private:
    VAO *object;
};

#endif // BULLET_H
