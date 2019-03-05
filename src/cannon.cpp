#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->active = true;
    this->rotationy = 0;
    const int n = 400;
    float initx = 0.05f, inity = 0.25f;
    static GLfloat vertex_buffer_data_cylinder[18*n];

   for (int i=0; i<n; i++)
   {
      vertex_buffer_data_cylinder[18*i] = initx;
      vertex_buffer_data_cylinder[18*i + 1] = 0.5f;
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
      vertex_buffer_data_cylinder[18*i + 16] = 0.5f;
      vertex_buffer_data_cylinder[18*i + 17] = initx*sin(2*3.14159/n) + inity*cos(2*3.14159/n);

      initx = vertex_buffer_data_cylinder[18*i + 6];
      inity = vertex_buffer_data_cylinder[18*i + 8];
    }
    this->object1 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data_cylinder, COLOR_YELLOW, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (30 * M_PI / 180.0f), glm::vec3(1, 0,0));
    glm::mat4 rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0,1));
    glm::mat4 rotatey    = glm::rotate((float) (rotationy * M_PI / 180.0f), glm::vec3(0, 0,1));
    Matrices.model *= (translate*rotatex)*rotatey;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
  }

void Cannon::tick(){
  this->rotationy += 1;
}
