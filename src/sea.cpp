#include "sea.h"
#include "main.h"

Sea::Sea(float y) {

    static const GLfloat vertex_buffer_data_1[] = {
        -800.0f,y,1000.0f, // triangle 1 : begin
        -800.0f,y,-1000.0f,
        800.0f,y, -1000.0f,  // triangle 1 : end
        800.0f,y,1000.0f, // triangle 1 : begin
        -800.0f,y,1000.0f,
        800.0f,y, -1000.0f,
    };

    // static const GLfloat vertex_buffer_data_2[] = {
    //     800,y,-1000.0,
    //     800,-y,-1000.0,
    //     -800,-y,-1000.0,
    //
    //     -800,y,-1000.0,
    //     800,y,-1000.0,
    //     -800,-y,-1000.0
    // };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_1, COLOR_SEABLUE, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_SKYBLUE, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    // draw3DObject(this->object2);
}
