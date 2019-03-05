#include "numbers.h"
#include "main.h"

Numbers::Numbers(float x, float y) {
  position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data1 [] = {
        0, -0.4, 0,
        0, 0, 0
    };
    this->object1 = create3DObject(GL_LINES, 2, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data2 [] = {
        0,0,0,
        -0.2,0,0,

        0,-0.2,0,
        0,0,0,
        //
        0,-0.2,0,
        -0.2,-0.2,0,
        //
        -0.2,-0.2,0,
        -0.2,-0.4,0,
        //
        -0.2,-0.4,0,
        0,-0.4,0,

    };
    this->object2 = create3DObject(GL_LINES, 10, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data3 [] = {
      0,0,0,
      -0.2,0,0,

      0,-0.2,0,
      0,0,0,
      //
      0,-0.2,0,
      -0.2,-0.2,0,
      //
      0,-0.2,0,
      0,-0.4,0,
      //
      -0.2,-0.4,0,
      0,-0.4,0,
    };
    this->object3 = create3DObject(GL_LINES, 10, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data4 [] = {
        -0.2,0,0,
        -0.2,-0.2,0,

        0,0,0,
        0,-0.2,0,

        -0.2,-0.2,0,
        0,-0.2,0,

        0,-0.2,0,
        0,-0.4,0
    };
    this->object4 = create3DObject(GL_LINES,8, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data5 [] = {
      0,0,0,
      -0.2,0,0,

      -0.2,0,0,
      -0.2,-0.2,0,

      0,-0.2,0,
      -0.2,-0.2,0,

      0,-0.2,0,
      0,-0.4,0,

      -0.2,-0.4,0,
      0,-0.4,0,
    };
    this->object5 = create3DObject(GL_LINES, 10, vertex_buffer_data5, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data6 [] = {
      0,0,0,
      -0.2,0,0,

      -0.2,0,0,
      -0.2,-0.2,0,

      0,-0.2,0,
      -0.2,-0.2,0,

      0,-0.2,0,
      0,-0.4,0,

      -0.2,-0.4,0,
      0,-0.4,0,

      -0.2,-0.2,0,
      -0.2,-0.4,0
    };
    this->object6 = create3DObject(GL_LINES, 12, vertex_buffer_data6, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data7 [] = {
        -0.2,0,0,
        0,0,0,

        0,0,0,
        0,-0.4,0,
    };
    this->object7 = create3DObject(GL_LINES, 4, vertex_buffer_data7, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data8 [] = {
      -0.2,0,0,
      0,0,0,

      -0.2,-0.2,0,
      0,-0.2,0,

      -0.2,-0.4,0,
      0,-0.4,0,


      0,0,0,
      0,-0.4,0,

      -0.2,0,0,
      -0.2,-0.4,0,
    };
    this->object8 = create3DObject(GL_LINES, 10, vertex_buffer_data8, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data9 [] = {
      -0.2,0,0,
      0,0,0,

      -0.2,-0.2,0,
      0,-0.2,0,

      -0.2,-0.4,0,
      0,-0.4,0,


      0,0,0,
      0,-0.4,0,

      -0.2,0,0,
      -0.2,-0.2,0,
    };
    this->object9 = create3DObject(GL_LINES, 10, vertex_buffer_data9, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_data0 [] = {
      -0.2,0,0,
      0,0,0,


      -0.2,-0.4,0,
      0,-0.4,0,

      -0.2,0,0,
      -0.2,-0.4,0,

      0,0,0,
      0,-0.4,0,
    };
    this->object0 = create3DObject(GL_LINES, 8, vertex_buffer_data0, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_dataA [] = {
      -0.2,0,0,
      0,0,0,

      -0.2,-0.2,0,
      0,-0.2,0,

      0,0,0,
      0,-0.4,0,

      -0.2,0,0,
      -0.2,-0.4,0,
    };
    this->objectA = create3DObject(GL_LINES, 8, vertex_buffer_dataA, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_dataF[] = {
      -0.2,0,0,
      0,0,0,

      -0.2,-0.2,0,
      0,-0.2,0,

      -0.2,0,0,
      -0.2,-0.4,0,
    };
    this->objectF = create3DObject(GL_LINES, 6, vertex_buffer_dataF, COLOR_BLACK, GL_FILL);
    static const GLfloat vertex_buffer_dataH[] = {
      
      -0.2,-0.2,0,
      0,-0.2,0,
    };
    this->objectH = create3DObject(GL_LINES, 2, vertex_buffer_dataH, COLOR_BLACK, GL_FILL);

}


void Numbers::draw(glm::mat4 VP, int i) {
    // if (!this->object1) return;
    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 rotate = glm::rotate(rotation, glm::vec3(0,0,1));
    glm::mat4 translate = glm::translate (this->position);        // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object1);
    if(i==1) draw3DObject(this->object1);
    if(i==2) draw3DObject(this->object2);
    if(i==3) draw3DObject(this->object3);
    if(i==4) draw3DObject(this->object4);
    if(i==5) draw3DObject(this->object5);
    if(i==6) draw3DObject(this->object6);
    if(i==7) draw3DObject(this->object7);
    if(i==8) draw3DObject(this->object8);
    if(i==9) draw3DObject(this->object9);
    if(i==0) draw3DObject(this->object0);
    if(i==10) draw3DObject(this->objectA);
    if(i==11) draw3DObject(this->objectF);
    if(i==12) draw3DObject(this->object5);
    if(i==13) draw3DObject(this->objectH);

}
