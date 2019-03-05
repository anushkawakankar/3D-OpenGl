#include "main.h"
#include "powerups.h"

Powerups::Powerups(float x, float y,float z) {
  this->active = true;
  this->position = glm::vec3(x, y, z);
  this->acceleration = 0.003;
  this->upspeed = 0.1;
  this->downspeed =0.0;


  static GLfloat vertex_buffer_data[]={
    0.2,0,0.2,
    -0.2,0,0.2,
    0,0.3,0,

    -0.2,0,0.2,
    -0.2,0,-0.2,
    0,0.3,0,

    -0.2,0,-0.2,
    0.2,0,-0.2,
    0,0.3,0,

    0.2,0,-0.2,
    0.2,0,0.2,
    0,0.3,0,

    0.2,0,0.2,
    -0.2,0,0.2,
    0,-0.3,0,

    -0.2,0,0.2,
    -0.2,0,-0.2,
    0,-0.3,0,

    -0.2,0,-0.2,
    0.2,0,-0.2,
    0,-0.3,0,

    0.2,0,-0.2,
    0.2,0,0.2,
    0,-0.3,0,
  };


  // if(incSpeed)
  {
    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, COLOR_ORCHID, GL_FILL);

  }
  // if(coinMagnet)
  // {
  //   this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
  //   this->object2 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data2, COLOR_LIGHTGOLD, GL_FILL);
  // }
}

void Powerups::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

  }

  void Powerups::tick() {
    if(this->upspeed>0)
    {
      this->position.y += this->upspeed;
      this->upspeed -= this->acceleration;
    }
    if(this->upspeed<0)
    {
      this->position.y -= this->downspeed;
      this->downspeed += this->acceleration;
    }

    if(this->downspeed > 0.1)
    {
      this->upspeed = 0.1;
      this->downspeed = 0;
    }
  }

  bounding_box_t Powerups::bounding_box() {
    float x = this->position.x;
    float z = this->position.z;
    bounding_box_t bbox = {x,z,0.2,0.5};
    return bbox;
  }
