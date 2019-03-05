#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float yaw);
    void tick();
    glm::vec3 position;
    float radius;
    bool active;
    float yaw;
    float xspeed;
    float yspeed;
    float acc;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object1;
};

#endif // BALL_H
