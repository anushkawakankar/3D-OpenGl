#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z){
  this->position = glm::vec3(x, y, z);
  GLfloat vertex_buffer_data[] = {
    0.75,0,-0.75,
    0.75,0,0.75,
    -0.75,0,0.75,

    -0.75,0,0.75,
    -0.75,0,-0.75,
    0.75,0,-0.75
  };
  GLfloat vertex_buffer_data3[] = {
    -0.55,0,-0.55,
    -0.55,0,0.55,
    0,0.65,0,

    -0.55,0,-0.55,
    0.55,0,-0.55,
    0,0.65,0,

    0.55,0,-0.55,
    0.55,0,0.55,
    0,0.65,0,

    0.55,0,0.55,
    -0.55,0,0.55,
    0,0.65,0
  };

  this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_RED, GL_FILL);
  // this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_SEABLUE, GL_FILL);
  this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data3, COLOR_GOLD, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    // draw3DObject(this->object3);
  }

  void Volcano::tick(){
    // this->rotation += speed;
  }
