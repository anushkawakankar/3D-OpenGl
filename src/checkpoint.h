#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    bool active;
    bool arrow;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif // BALL_H
