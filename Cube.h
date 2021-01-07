#pragma once
#include <stdio.h>
#include <GLEW/GL/glew.h>
#include <glm/glm.hpp>
#include "transform.h"
class Cube : public Transform
{
public:
	Cube(float size, GLuint shader);
	~Cube();
	void ChangeColor(float r, float g, float b);
	void Render();
private:
	GLfloat c_vertexBufferData[18*6];
	GLfloat c_colorBufferData[18*6];
	GLuint c_vbo = 0;
	GLuint c_vao = 0;
	GLuint c_vcb = 0;
	GLuint c_modelMatrixID;
	glm::mat4 c_modelMatrix;
	glm::mat4 c_translateMatrix;
	glm::mat4 c_rotationMatrix;
	GLuint c_shader;
	void Load();
};

