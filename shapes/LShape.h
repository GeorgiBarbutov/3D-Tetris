#pragma once

#include "Shape.h"

class LShape : public Shape
{
public:
	LShape();
	LShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};

