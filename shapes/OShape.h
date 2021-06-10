#pragma once

#include "Shape.h"

class OShape : public Shape
{
public:
	OShape();
	OShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};

