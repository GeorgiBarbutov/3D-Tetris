#pragma once

#include "Shape.h"

class TShape : public Shape
{
public:
	TShape();
	TShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};

