#pragma once

#include <glm/glm.hpp>

class Shape
{
public:
	virtual glm::vec3* RotateZ() = 0;

	glm::vec3* MoveLeft();
	glm::vec3* MoveRight();
	glm::vec3* MoveForward();
	glm::vec3* MoveBack();
	glm::vec3* MoveUp(float blocks);
	glm::vec3* MoveDown();
	glm::vec3* MoveDown(float blocks);
	glm::vec3* Positions();

protected:
	const static int BOARD_WIDTH = 7;
	const static int BOARD_HIGHT = 15;
	const glm::vec3 _startPosition = glm::vec3((float)(BOARD_WIDTH / 2), (float)BOARD_HIGHT, (float)(BOARD_WIDTH / 2));

	glm::vec3 _positions[4];
};

