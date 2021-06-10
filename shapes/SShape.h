#pragma once

#include "Shape.h"

class SShape : public Shape
{
public:
	SShape();
	SShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};

