#pragma once

#include <memory>

#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

#include <glm/glm.hpp>
#include "shapes/Shape.h"

struct GLFWwindow;

class Application
{
public:
	void Run();

private:
	void Init();
	void Update(float dt, int level, int& result, float elapsedTime, float moveDownSlowdown, GLFWwindow* window);
	void Render(GLFWwindow* window);

	void ProcessInput(GLFWwindow* window, float dt, float& moveDownSlowdown, float level);

	friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool CanMoveDown();
	bool CanMoveLeft();
	bool CanMoveRight();
	bool CanMoveForward();
	bool CanMoveBack();
	bool areInside();
	void setNewShape();

private:
	const static int BOARD_WIDTH = 7;
	const static int BOARD_HEIGHT = 15;

	std::unique_ptr<VertexArray> _va;
	std::unique_ptr<Shader> _shader;
	std::unique_ptr<Shader> _lightCubeShader;

	std::unique_ptr<Texture> _diffuseTexture;
	std::unique_ptr<Texture> _specularTexture;

	glm::vec3 _lightPos = glm::vec3(0.2f, 30.0f, 10.0f);
	glm::vec3 _lightColor = glm::vec3(1.f, 1.f, 1.f);

	glm::vec3 _cameraPos = glm::vec3(3.0f, 15.0f, 15.0f);
	glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float _yaw = -90.0f;
	float _pitch = 0.0f;
	float _fov = 45.f;

	Shape* _currentShape;
	Shape* _nextShape;
	bool _placedCubes[BOARD_WIDTH][BOARD_HEIGHT + 4][BOARD_WIDTH];
	glm::vec3 _sideX[BOARD_HEIGHT * BOARD_WIDTH];
	glm::vec3 _sideZ[BOARD_HEIGHT * BOARD_WIDTH];

	float _newPieceTime;
	float _lastMoveDownTime;
};
