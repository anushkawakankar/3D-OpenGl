#ifndef NUMBERS_H
#define NUMBERS_H

#include "main.h"

class Numbers  {
public:
  Numbers() {}
  Numbers(float x,float y);
  glm::vec3 position;
   void draw(glm::mat4 VP, int i);
   // void draw2(glm::mat4 VP);
   // void draw3(glm::mat4 VP);
   // void draw4(glm::mat4 VP);
   // void draw5(glm::mat4 VP);
   // void draw6(glm::mat4 VP);
   // void draw7(glm::mat4 VP);
   // void draw8(glm::mat4 VP);
   // void draw9(glm::mat4 VP);
   // void draw0(glm::mat4 VP);
 private:
   VAO *object1;
   VAO *object2;
   VAO *object3;
   VAO *object4;
   VAO *object5;
   VAO *object6;
   VAO *object7;
   VAO *object8;
   VAO *object9;
   VAO *object0;
   VAO *objectA;
   VAO *objectF;
   VAO *objectH;

};

#endif
