#include "main.h"

#ifndef POWERUPS_H
#define POWERUPS_H


class Powerups {
public:
    Powerups() {}
    Powerups(float x,float y, float z );
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    double upspeed;
    double acceleration;
    double downspeed;
    double acc;
    bool active;
    float rotation;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif
