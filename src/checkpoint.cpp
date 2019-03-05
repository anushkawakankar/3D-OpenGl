#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float y, float z){
  this->position = glm::vec3(x, y, z);
  this->rotation = 0;
  this->speed=2;
  this->active = true;
  this->arrow = false;
  GLfloat vertex_buffer_data[] = {
    0.5,0,-0.5,
    0.5,0,0.5,
    -0.5,0,0.5,

    -0.5,0,0.5,
    -0.5,0,-0.5,
    0.5,0,-0.5
  };
  GLfloat vertex_buffer_data2[] = {
    -0.35,0,-0.35,
    -0.35,0,0.35,
    0,0.5,0,

    -0.35,0,-0.35,
    0.35,0,-0.35,
    0,0.5,0,

    0.35,0,-0.35,
    0.35,0,0.35,
    0,0.5,0,

    0.35,0,0.35,
    -0.35,0,0.35,
    0,0.5,0
  };
  GLfloat vertex_buffer_data3[] = {
    0,0.75,0,
    -1,1,0,
    1,1,0,

    -0.5,2.5,0,
    -0.5,1,0,
    0.5,1,0,

    -0.5,2.5,0,
    0.5,1,0,
    0.5,2.5,0
  };


  this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_ORCHID, GL_FILL);
  this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_PINK, GL_FILL);
  this->object3 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data3, COLOR_RED, GL_FILL);

}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    if(this->arrow)
      draw3DObject(this->object3);
  }

  void Checkpoint::tick(){
    // this->rotation += speed;
  }

  bounding_box_t Checkpoint::bounding_box() {
    float x = this->position.x;
    float z = this->position.z;
    bounding_box_t bbox = {x,z,0.5,2};
    return bbox;
  }
