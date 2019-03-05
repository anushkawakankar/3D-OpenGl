#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotationy = 0;
    this->rotationx = 0;
    this->rotationz = 0;
    this->speed = 0.1;
    this->yspeed = 0.0f;
    this->downyspeed = 0.0f;
    this->acc = 0.01f;
    this->Yrotation = 0.0f;
    this->upStep = 0.5f;
    this->fuel = 999;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_body[] = {
        0,0,0,
        0,0.5,0,
        0.5,0,0,

        0,0.5,0,
        0.5,0.5,0,
        0.5,0,0,

        0,0.5,2,
        0,0,2,
        0.5,0,2,

        0,0.5,2,
        0.5,0.5,2,
        0.5,0,2,

        0.5,0.5,0,
        0.5,0,0,
        0.5,0,2,

        0.5,0.5,2,
        0.5,0.5,0,
        0.5,0,2,

        0,0.5,2,
        0,0.5,0,
        0,0,0,

        0,0.5,2,
        0,0,2,
        0,0,0,

        0,0.5,0,
        0.5,0.5,0,
        0,0.5,2,

        0,0.5,2,
        0.5,0.5,2,
        0.5,0.5,0,

        0,0,0,
        0,0,2,
        0.5,0,0,

        0,0,2,
        0.5,0,0,
        0.5,0,2,
    };

    static const GLfloat vertex_buffer_data_wings[] = {
      0,0.25,0.2,
      0,0.25,1.5,
      -0.5,0.25,1.5,

      0.5,0.25,1.5,
      0.5,0.25,0,
      1,0.25,1.5,

      0.25,0.5,1,
      0.25,0.5,1.5,
      0.25,0.9,1,

    };


    this->objectbody = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_body, COLOR_RED, GL_FILL);
    this->objectwings = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data_wings, COLOR_GREEN, GL_FILL);
    }

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotatex          = rotatex * glm::translate(glm::vec3(0, 0, 0));
    rotatey          = rotatey * glm::translate(glm::vec3(0, -0.6, 0));
    rotatez          = rotatez * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotatex * rotatey * rotatez);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->objectbody);
    draw3DObject(this->objectwings);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
  this->fuel -= 0.025;
  this->position.x -= this->speed * sin(this->rotationy*M_PI/180);
  this->position.z -= this->speed * cos(this->rotationy*M_PI/180);
}

bounding_box_t Ball::bounding_box() {
  float x = this->position.x;
  float z = this->position.z;
  bounding_box_t bbox = {x,z,0.5,2};
  return bbox;
}
