#include "bullet.h"
#include "main.h"
#include <math.h>
#define _USE_MATH_DEFINES

Bullet::Bullet(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->active = false;
    this->radius = 0.1;
    // float n = 360;
    // float r = this-> radius;
    // float theta = 2*M_PI/n;
    int i;
    this->rotationy =0;
    this->xspeed = 0.15;
    this->upspeed=0.3;
    this->downspeed = 0.0;
    this->acceleration=0.003;
      // GLfloat vertex_buffer_data[360*9];
      //
      // for(i=0;i<n;i++)
      // {
      //   float angle1=theta*i;
      //   float angle2 = angle1+theta;
      //
      //   vertex_buffer_data[i*9]= 0.0f;
      //   vertex_buffer_data[i*9+1]= 0.0f;
      //   vertex_buffer_data[i*9+2]=0.0f;
      //   vertex_buffer_data[i*9+3]= r*cos(angle1);
      //   vertex_buffer_data[i*9+4]=r*sin(angle1);
      //   vertex_buffer_data[i*9+5]=0.0f;
      //   vertex_buffer_data[i*9+6]=r*cos(angle2);
      //   vertex_buffer_data[i*9+7]=r*sin(angle2);
      //   vertex_buffer_data[i*9+8]=0.0f;
      //
      // }
      // this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_ORANGE, GL_FILL);
      const int n = 400;
      float initx = 0.03f, inity = 0.25f;
      static GLfloat vertex_buffer_data_cylinder[18*n];

     for (int i=0; i<n; i++)
     {
        vertex_buffer_data_cylinder[18*i] = initx;
        vertex_buffer_data_cylinder[18*i + 1] = 14.0f;
        vertex_buffer_data_cylinder[18*i + 2] = inity;
        vertex_buffer_data_cylinder[18*i + 3] = initx;
        vertex_buffer_data_cylinder[18*i + 4] = 0.0f;
        vertex_buffer_data_cylinder[18*i + 5] = inity;
        vertex_buffer_data_cylinder[18*i + 6] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
        vertex_buffer_data_cylinder[18*i + 7] = 0.0f;
        vertex_buffer_data_cylinder[18*i + 8] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
        vertex_buffer_data_cylinder[18*i + 9] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
        vertex_buffer_data_cylinder[18*i + 10] = 0.0f;
        vertex_buffer_data_cylinder[18*i + 11] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);
        vertex_buffer_data_cylinder[18*i + 12] = initx;
        vertex_buffer_data_cylinder[18*i + 13] = 0.0f;
        vertex_buffer_data_cylinder[18*i + 14] = inity;
        vertex_buffer_data_cylinder[18*i + 15] = initx*cos(2*3.14159/n) - inity*sin(2*3.14159/n);
        vertex_buffer_data_cylinder[18*i + 16] = 14.0f;
        vertex_buffer_data_cylinder[18*i + 17] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

        initx = vertex_buffer_data_cylinder[18*i + 6];
        inity = vertex_buffer_data_cylinder[18*i + 8];
      }
      this->object = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_cylinder, COLOR_ORANGE, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (30 * M_PI / 180.0f), glm::vec3(1, 0,0));
    glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0,1));
    glm::mat4 rotatey    = glm::rotate((float) (rotationy * M_PI / 180.0f), glm::vec3(0, 0,1));
    Matrices.model *= (translate*rotatex)*rotatey;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bullet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bullet::tick() {
  this->position.z += this->xspeed;
  if(this->upspeed >= 0)
  {
    this->position.y += this->upspeed;
    this->upspeed -= this->acceleration;
  }
  if(this->upspeed <= 0)
  {
    this->position.y -= this->downspeed;
    this->downspeed += this->acceleration;
  }
  if(this->position.y <= -2)
    this->active = false;
}

void Bullet::tick2(){
  this->rotationy += 1;
}

bounding_box_t Bullet::bounding_box() {
  float x = this->position.x;
  float z = this->position.z;
  bounding_box_t bbox = {x,z,0.2,1};
  return bbox;
}
