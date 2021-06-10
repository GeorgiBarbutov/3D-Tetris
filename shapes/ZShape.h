#pragma once

#include "Shape.h"

class ZShape : public Shape
{
public:
	ZShape();
	ZShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};

