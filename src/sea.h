#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:
  Sea() {}
  Sea(float y);
  glm::vec3 position;
  void draw(glm::mat4 VP);
private:
  VAO *object1;
  VAO *object2;
};

#endif
