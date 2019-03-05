#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x,float y, float z, float yaw) {
    this->position = glm::vec3(x, y, z);
    this->active = true;
    this->yaw = yaw;
    this->xspeed = 0.15;
    this->yspeed = 0;
    this->acc = 0.02;
    static GLfloat vertex_buffer_data[]= {
    -0.2f,2.0f,1.25f, // triangle 1 : begin
    -0.2f,2.0f, 1.75f,
    -0.2f, 2.5f, 1.75f, // triangle 1 : end

    0.2f, 2.5f,1.25f, // triangle 2 : begin
    -0.2f,2.0f,1.25f,
    -0.2f, 2.5f,1.25f, // triangle 2 : end

    0.2f,2.0f, 1.75f,
    -0.2f,2.0f,1.25f,
    0.2f,2.0f,1.25f,

    0.2f, 2.5f,1.25f,
    0.2f,2.0f,1.25f,
    -0.2f,2.0f,1.25f,

    -0.2f,2.0f,1.25f,
    -0.2f, 2.5f, 1.75f,
    -0.2f, 2.5f,1.25f,

    0.2f,2.0f, 1.75f,
    -0.2f,2.0f, 1.75f,
    -0.2f,2.0f,1.25f,

    -0.2f, 2.5f, 1.75f,
    -0.2f,2.0f, 1.75f,
    0.2f,2.0f, 1.75f,

    0.2f, 2.5f, 1.75f,
    0.2f,2.0f,1.25f,
    0.2f, 2.5f,1.25f,

    0.2f,2.0f,1.25f,
    0.2f, 2.5f, 1.75f,
    0.2f,2.0f, 1.75f,

    0.2f, 2.5f, 1.75f,
    0.2f, 2.5f,1.25f,
    -0.2f, 2.5f,1.25f,

    0.2f, 2.5f, 1.75f,
    -0.2f, 2.5f,1.25f,
    -0.2f, 2.5f, 1.75f,

    0.2f, 2.5f, 1.75f,
    -0.2f, 2.5f, 1.75f,
    0.2f,2.0f, 1.75f

    };


    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_FORESTGREEN, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotatex    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(1, 0,0));
    // glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0,1));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
  }

void Bomb::tick() {
  this->position.x -= this->xspeed * sin(this->yaw*M_PI/180);
  this->position.z -= this->xspeed * cos(this->yaw*M_PI/180);
  this->position.y -= this->yspeed;
  printf("%f %f %f\n",this->position.x, this->position.y, this->position.z);
  this->yspeed += this->acc;
  if(this->position.y < 0)
    this->active = false;
}
