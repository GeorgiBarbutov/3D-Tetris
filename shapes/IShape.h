#pragma once

#include "Shape.h"

class IShape : public Shape
{
public:
	IShape();
	IShape(glm::vec3 positions[4]);

	glm::vec3* RotateZ();
};