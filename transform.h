#pragma once
#include <glm/glm.hpp>
class Transform
{
public:
	glm::mat4 t_translateMatrix;
	glm::mat4 t_rotationMatrix;
	glm::mat4 t_matrix;
	Transform();
	~Transform();
	void Translate(glm::vec3 p);
	void UpdateMatrix();
};

