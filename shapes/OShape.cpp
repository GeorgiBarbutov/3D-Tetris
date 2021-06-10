#include "OShape.h"

OShape::OShape()
{
	_positions[0] = glm::vec3(-1.0f + _startPosition.x, 0.0f + _startPosition.y, 0.0f + _startPosition.z);
	_positions[1] = glm::vec3(0.0f + _startPosition.x, 0.0f + _startPosition.y, 0.0f + _startPosition.z);
	_positions[2] = glm::vec3(-1.0f + _startPosition.x, 1.0f + _startPosition.y, 0.0f + _startPosition.z);
	_positions[3] = glm::vec3(0.0f + _startPosition.x, 1.0f + _startPosition.y, 0.0f + _startPosition.z);
}

OShape::OShape(glm::vec3 positions[4])
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i] = positions[i];
	}
}

glm::vec3* OShape::RotateZ()
{
	return _positions;
}