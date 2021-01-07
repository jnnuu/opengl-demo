#include <stdio.h>
#include <vector>
#include <math.h>
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "Cube.h"

GLFWwindow* InitWindow()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW Failed.");
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		1024,
		768,
		"demo02",
		NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "failed to open window.");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		fprintf(stderr, "GLEW failed.");
		glfwTerminate();
		return NULL;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	return window;
}

int main(void)
{
	std::vector<Cube> objects;
	GLFWwindow* window = InitWindow();
	if (window == NULL)
	{
		return -1;
	}
	GLuint programID = LoadShaders(
		"shader_vertex.glsl",
		"shader_fragment.glsl"
	);
	glUseProgram(programID);
	Cube small_a = Cube(0.2f, programID);
	Cube small_b = Cube(0.2f, programID);
	Cube small_c = Cube(0.2f, programID);
	Cube small_d = Cube(0.2f, programID);
	Cube med = Cube(0.5f,programID);

	small_a.Translate(glm::vec3(-1.0f, 0.0f, 0.0f));
	small_b.Translate(glm::vec3(1.0f, 0.0f, 0.0f));
	small_c.Translate(glm::vec3(0.0f, 0.0f, 1.0f));
	small_d.Translate(glm::vec3(0.0f, 0.0f, -1.0f));

	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			Cube newCube = Cube(0.01f*i, programID);
			newCube.Translate(glm::vec3(i-15, -2, j-15));
			newCube.ChangeColor(0.02f*i,j*0.03f,i*0.02f);
			objects.push_back(newCube);
		}
		
	}

	double starttime = glfwGetTime();

	GLuint VMMatrixID = glGetUniformLocation(programID, "vm");
	GLuint PMMatrixID = glGetUniformLocation(programID, "pm");



	
	glEnable(GL_DEPTH_TEST);

	do
	{
		double deltaTime = glfwGetTime() - starttime;
		double sinwave = std::sin(deltaTime);
		double coswave = std::cos(deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f,0.0f,0.0f, 0.0f);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(-7 * -sinwave, 5, -7 * coswave),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);

		//med.ChangeColor(abs(sinwave));


		//med.Render();
		small_a.Translate(glm::vec3(0, abs(coswave/2)+0.2f, 0));
		small_b.Translate(glm::vec3(0, -abs(coswave/2)-0.2f, 0));
		small_c.Translate(glm::vec3(-abs(sinwave / 2) - 0.2f, 0, 0));
		small_d.Translate(glm::vec3(abs(sinwave / 2) + 0.2f, 0, 0));

		small_a.ChangeColor(abs(sinwave), abs(coswave), abs(sinwave));
		small_b.ChangeColor(abs(sinwave), abs(coswave), abs(sinwave));

		small_c.ChangeColor(abs(coswave), abs(sinwave), abs(coswave));
		small_d.ChangeColor(abs(coswave), abs(sinwave), abs(coswave));

		small_a.Render();
		small_b.Render();
		small_c.Render();
		small_d.Render();

		for (int i = 0; i < objects.size(); ++i)
		{
			objects[i].Render();
		}

		glUniformMatrix4fv(VMMatrixID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(PMMatrixID, 1, GL_FALSE, &projection[0][0]);


		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwTerminate();
}