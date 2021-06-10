#pragma once

#include "Shape.h"

class JShape : public Shape
{
public:
	JShape();
	JShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};

