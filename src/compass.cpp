#include "compass.h"
#include "main.h"
#include <math.h>
#define _USE_MATH_DEFINES

Compass::Compass(float x, float y, float rot) {
  this->position = glm::vec3(x, y, 0);
    this->rotationy = rot;
    static GLfloat vertex_buffer_data[]={
      -0.2,0,0,
      0.2,0,0,
      0,0.5,0
    };

    static GLfloat vertex_buffer_data2[]={
      -0.2,0,0,
      0.2,0,0,
      0,-0.5,0
    };
      this->object = create3DObject(GL_TRIANGLES,3, vertex_buffer_data, COLOR_MAGRED, GL_FILL);
      this->object2 = create3DObject(GL_TRIANGLES,3, vertex_buffer_data2, COLOR_LIGHTGREY, GL_FILL);

}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (-(this->rotationy) * M_PI / 180.0f), glm::vec3(0, 0,1));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Compass::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
