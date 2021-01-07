#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "transform.h"

Transform::Transform()
{
	t_translateMatrix	= glm::mat4(1.0f);
	t_rotationMatrix	= glm::mat4(1.0f);
	t_matrix			= glm::mat4(1.0f);
}

Transform::~Transform()
{

}

void Transform::Translate(glm::vec3 p)
{
	t_translateMatrix = glm::mat4(1.0f);
	t_translateMatrix = glm::translate(t_translateMatrix, p);
}

void Transform::UpdateMatrix()
{
	t_matrix = t_translateMatrix * t_rotationMatrix;
}
