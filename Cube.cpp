#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include <stdio.h>

Cube::Cube(float size, GLuint shader)
{
	c_rotationMatrix = glm::mat4(1.0f);
	c_translateMatrix = glm::mat4(1.0f);
	c_shader = shader;
	c_modelMatrixID = glGetUniformLocation(c_shader, "mm");

	GLfloat x = size;
	GLfloat y = size;
	GLfloat z = size;

	//cube = 6 faces
	GLfloat front[] =
	{
		-x,y,z,
		-x,-y,z,
		x,-y,z,
		x,-y,z,
		x,y,z,
		-x,y,z
	};
	GLfloat top[] =
	{
		x,y,z,
		x,y,-z,
		-x,y,-z,
		x,y,z,
		-x,y,-z,
		-x,y,z
	};
	GLfloat back[] =
	{
		x,y,-z,
		x,-y,-z,
		-x,-y,-z,
		-x,-y,-z,
		-x,y,-z,
		x,y,-z
	};
	GLfloat bottom[] =
	{
		x,-y,z,
		-x,-y,z,
		-x,-y,-z,
		x,-y,z,
		x,-y,-z,
		-x,-y,-z
	};
	GLfloat side_left[] =
	{
		x,y,z,
		x,y,-z,
		x,-y,-z,
		x,y,z,
		x,-y,z,
		x,-y,-z
	};
	GLfloat side_right[] =
	{
		-x,y,z,
		-x,y,-z,
		-x,-y,-z,
		-x,y,z,
		-x,-y,z,
		-x,-y,-z
	};


	//GLfloat c_vertexBufferData[18 * 6]
	for (int i = 0; i < 18; ++i)
	{
		c_vertexBufferData[i] = front[i];
	}
	for (int i = 18; i < 2 * 18; ++i)
	{
		c_vertexBufferData[i] = top[i - 18];
	}
	for (int i = 18 * 2; i < 3 * 18; ++i)
	{
		c_vertexBufferData[i] = back[i - 2 * 18];
	}
	for (int i = 18 * 3; i < 4 * 18; ++i)
	{
		c_vertexBufferData[i] = bottom[i - 3 * 18];
	}
	for (int i = 18 * 4; i < 5 * 18; ++i)
	{
		c_vertexBufferData[i] = side_left[i - 4 * 18];
	}
	for (int i = 18 * 5; i < 6 * 18; ++i)
	{
		c_vertexBufferData[i] = side_right[i - 5 * 18];
	}

	for (int i = 0; i < 18 * 6; ++i)
	{
		if (i % 2 == 0)
		{
			c_colorBufferData[i] = 0.50f;
		}
		else
		{
			c_colorBufferData[i] = 0.3f;
		}
	}
	Load();
}

Cube::~Cube()
{
}

void Cube::ChangeColor(float r, float g, float b)
{
	for (int i = 0; i < 18 * 6; i+=3)
	{
		c_colorBufferData[i] = r;
		c_colorBufferData[i+1] = g;
		c_colorBufferData[i+2] = b;
	}
	Load();
}

void Cube::Render()
{
	UpdateMatrix();
	glUniformMatrix4fv(c_modelMatrixID, 1, GL_FALSE, &t_matrix[0][0]);

	glBindVertexArray(c_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 2 * 2 * 2);
	glBindVertexArray(0);
}

void Cube::Load()
{
	glGenBuffers(1, &c_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(c_vertexBufferData)
		, c_vertexBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &c_vcb); //color buffer
	glBindBuffer(GL_ARRAY_BUFFER, c_vcb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(c_colorBufferData)
		, c_colorBufferData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &c_vao);
	glBindVertexArray(c_vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, c_vcb);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);

	c_modelMatrixID = glGetUniformLocation(c_shader, "mm");
}
