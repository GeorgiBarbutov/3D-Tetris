#include "Shape.h"

glm::vec3* Shape::MoveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].x -= 1.0f;
	}

	return _positions;
}

glm::vec3* Shape::MoveRight()
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].x += 1.0f;
	}

	return _positions;
}

glm::vec3* Shape::MoveForward()
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].z += 1.0f;
	}

	return _positions;
}

glm::vec3* Shape::MoveBack()
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].z -= 1.0f;
	}

	return _positions;
}

glm::vec3* Shape::MoveUp(float blocks)
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].y += blocks;
	}

	return _positions;
}

glm::vec3* Shape::MoveDown()
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].y -= 1.0f;
	}

	return _positions;
}

glm::vec3* Shape::MoveDown(float blocks)
{
	for (int i = 0; i < 4; i++)
	{
		_positions[i].y -= blocks;
	}

	return _positions;
}

glm::vec3* Shape::Positions()
{
	return _positions;
}