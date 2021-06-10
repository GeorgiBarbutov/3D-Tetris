#include "IShape.h"

IShape::IShape()
{
	_positions[0] = glm::vec3(0.0f + _startPosition.x, 0.0f + _startPosition.y, 0.0f + _startPosition.z);
	_positions[1] = glm::vec3(0.0f + _startPosition.x, 1.0f + _startPosition.y, 0.0f + _startPosition.z);
	_positions[2] = glm::vec3(0.0f + _startPosition.x, 2.0f + _startPosition.y, 0.0f + _startPosition.z);
	_positions[3] = glm::vec3(0.0f + _startPosition.x, 3.0f + _startPosition.y, 0.0f + _startPosition.z);
}

IShape::IShape(glm::vec3 positions[4])
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i] = positions[i];
	}
}

glm::vec3* IShape::RotateZ()
{
	if (_positions[1].x < 1 || _positions[1].x > 4) {
		return _positions;
	}

	if (_positions[0].x == _positions[1].x)
	{
		_positions[0] = glm::vec3(-1.0f + _positions[0].x, 1.0f + _positions[0].y, 0.0f + _positions[0].z);
		_positions[2] = glm::vec3(1.0f + _positions[2].x, -1.0f + _positions[2].y, 0.0f + _positions[2].z);
		_positions[3] = glm::vec3(2.0f + _positions[3].x, -2.0f + _positions[3].y, 0.0f + _positions[3].z);
	}
	else
	{
		_positions[0] = glm::vec3(1.0f + _positions[0].x, -1.0f + _positions[0].y, 0.0f + _positions[0].z);
		_positions[2] = glm::vec3(-1.0f + _positions[2].x, 1.0f + _positions[2].y, 0.0f + _positions[2].z);
		_positions[3] = glm::vec3(-2.0f + _positions[3].x, 2.0f + _positions[3].y, 0.0f + _positions[3].z);
	}

	return _positions;
}