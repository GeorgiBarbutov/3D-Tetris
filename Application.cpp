#include "Application.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "shapes/IShape.h"
#include "shapes/LShape.h"
#include "shapes/JShape.h"
#include "shapes/ZShape.h"
#include "shapes/SShape.h"
#include "shapes/OShape.h"
#include "shapes/TShape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Shape* getRandomShape()
{
	switch (rand() % 7)
	{
	case 0:
		return new IShape();
		break;
	case 1:
		return new LShape();
		break;
	case 2:
		return new JShape();
		break;
	case 3:
		return new SShape();
		break;
	case 4:
		return new ZShape();
		break;
	case 5:
		return new TShape();
		break;
	case 6:
		return new OShape();
		break;
	default:
		return nullptr;
		break;
	}
}

void Application::setNewShape() 
{
	_currentShape = _nextShape;

	if (_currentShape != nullptr)
	{
		_currentShape->MoveDown(5);
	}
	else
	{
		_currentShape = getRandomShape();
	}

	_nextShape = getRandomShape();

	_nextShape->MoveUp(5);
}

bool Application::CanMoveDown()
{
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 shapeCube = _currentShape->Positions()[i];
		if (_placedCubes[(int)shapeCube.x][(int)shapeCube.y - 1][(int)shapeCube.z])
		{
			return false;
		}
	}

	return true;
}

bool Application::CanMoveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 shapeCube = _currentShape->Positions()[i];
		if (shapeCube.x - 1 < 0)
		{
			return false;
		}
		if (_placedCubes[(int)shapeCube.x - 1][(int)shapeCube.y][(int)shapeCube.z])
		{
			return false;
		}
	}

	return true;
}

bool Application::CanMoveRight()
{
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 shapeCube = _currentShape->Positions()[i];
		if (shapeCube.x + 1 >= BOARD_WIDTH)
		{
			return false;
		}
		if (_placedCubes[(int)shapeCube.x + 1][(int)shapeCube.y][(int)shapeCube.z])
		{
			return false;
		}
	}

	return true;
}

bool Application::CanMoveBack()
{
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 shapeCube = _currentShape->Positions()[i];
		if (shapeCube.z - 1 < 0)
		{
			return false;
		}
		if (_placedCubes[(int)shapeCube.x][(int)shapeCube.y][(int)shapeCube.z - 1])
		{
			return false;
		}
	}

	return true;
}

bool Application::CanMoveForward()
{
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 shapeCube = _currentShape->Positions()[i];
		if (shapeCube.z + 1 >= BOARD_WIDTH)
		{
			return false;
		}
		if (_placedCubes[(int)shapeCube.x][(int)shapeCube.y][(int)shapeCube.z + 1])
		{
			return false;
		}
	}

	return true;
}

bool Application::areInside()
{
	for (int i = 0; i < 4; i++)
	{
		glm::vec3 shapeCube = _currentShape->Positions()[i];
		if (_placedCubes[(int)shapeCube.x][(int)shapeCube.y][(int)shapeCube.z])
		{
			return true;
		}
	}

	return false;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto* app = (Application*)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		app->_currentShape->RotateZ();
		if (app->areInside()) {
			app->_currentShape->RotateZ();
			app->_currentShape->RotateZ();
			app->_currentShape->RotateZ();
		}
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && app->CanMoveLeft())
	{
		app->_currentShape->MoveLeft();
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && app->CanMoveRight())
	{
		app->_currentShape->MoveRight();
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS && app->CanMoveForward())
	{
		app->_currentShape->MoveForward();
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS && app->CanMoveBack())
	{
		app->_currentShape->MoveBack();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static bool firstMouse = true;
	static double lastX;
	static double lastY;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if (state != GLFW_PRESS)
		return;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	auto* app = (Application*)glfwGetWindowUserPointer(window);

	app->_yaw += xoffset;
	app->_pitch += yoffset;

	if (app->_pitch > 89.0f)
		app->_pitch = 89.0f;

	if (app->_pitch < -89.0f)
		app->_pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(app->_yaw)) * cos(glm::radians(app->_pitch));
	direction.y = sin(glm::radians(app->_pitch));
	direction.z = sin(glm::radians(app->_yaw)) * cos(glm::radians(app->_pitch));

	app->_cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto* app = (Application*)glfwGetWindowUserPointer(window);

	app->_fov -= (float)yoffset;

	if (app->_fov < 1.0f)
		app->_fov = 1.0f;

	if (app->_fov > 90.0f)
		app->_fov = 90.0f;
}

void Application::ProcessInput(GLFWwindow* window, float dt, float& moveDownSlowdown, float level)
{
	const float cameraSpeed = 5.0f * dt;
	const float lightSpeed = cameraSpeed;
	float multiplier = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		multiplier = 5.0f;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		_lightPos.x += lightSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		_lightPos.x -= lightSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		_lightPos.y += lightSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		_lightPos.y -= lightSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		_lightPos.z += lightSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		_lightPos.z -= lightSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		_cameraPos += cameraSpeed * multiplier * _cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		_cameraPos -= cameraSpeed * multiplier * _cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed * multiplier;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		moveDownSlowdown = 0.1f;
	}
	else
	{
		if (level >= 13)
		{
			level = 12;
		}
		moveDownSlowdown = 1.3f - (0.1f * level);
	}
}

void Application::Run()
{
	GLFWwindow* window;

	/* Initialize the glfw */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "3D Tetris", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, 1920, 1080);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	Init();

	srand(time(NULL));

	setNewShape();

	int level = 1;
	int result = 0;
	//int level = 5; 
	//int result = 2400;

	std::string resultString = "3D Tetris - Result: ";
	resultString.append(std::to_string(result));
	resultString.append(" Level: ");
	resultString.append(std::to_string(level));
	glfwSetWindowTitle(window, resultString.c_str());

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float moveDownSlowdown = 1.0f;
	float elapsedTime = 0.0f;
	_newPieceTime = glfwGetTime();
	_lastMoveDownTime = _newPieceTime;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		elapsedTime = lastFrame - _newPieceTime;

		ProcessInput(window, deltaTime, moveDownSlowdown, level);
		Update(deltaTime, level, result, elapsedTime, moveDownSlowdown, window);
		Render(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void Application::Init()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	std::unique_ptr<VertexBuffer> vbo(new VertexBuffer(vertices, sizeof(vertices)));

	vbo->Bind();

	vbo->SetLayout(
		{
			{"aPos", Float3},
			{"aNorm", Float3},
			{"aTexCoords", Float2}
		}
	);

	_va = std::make_unique<VertexArray>();
	_va->SetVertexBuffer(std::move(vbo));
	_va->Bind();

	_shader = std::make_unique<Shader>("res\\lighting.vert.glsl", "res\\lighting.frag.glsl");
	_lightCubeShader = std::make_unique<Shader>("res\\light_cube.vert.glsl", "res\\light_cube.frag.glsl");

	_diffuseTexture = std::make_unique<Texture>("res\\container2.png");
	_specularTexture = std::make_unique<Texture>("res\\container2_specular.png");

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			_placedCubes[i][0][j] = true;
			_placedCubes[i][1][j] = true;
			_placedCubes[i][2][j] = true;
			_placedCubes[i][3][j] = true;
			_placedCubes[i][4][j] = true;
		}
	}
	_placedCubes[0][1][0] = false;
	_placedCubes[0][2][0] = false;
	_placedCubes[0][3][0] = false;
	_placedCubes[0][4][0] = false;
	_placedCubes[3][3][3] = true;
	_placedCubes[3][4][3] = true;
}

void Application::Update(float dt, int level, int& result, float elapsedTime, float moveDownSlowdown, GLFWwindow* window)
{
	const auto view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
	const auto projection = glm::perspective(glm::radians(_fov), 1920.0f / 1080.0f, 0.1f, 100.0f);

	_shader->use();
	_shader->setFloatMat4("view", view);
	_shader->setFloatMat4("projection", projection);

	_lightCubeShader->use();
	_lightCubeShader->setFloatMat4("view", view);
	_lightCubeShader->setFloatMat4("projection", projection);

	//Tetris Logic
	if (elapsedTime - _lastMoveDownTime > moveDownSlowdown)
	{
		if (CanMoveDown())
		{
			_currentShape->MoveDown();
			_lastMoveDownTime = glfwGetTime() - _newPieceTime;
		}
		else
		{
			glm::vec3* positions = _currentShape->Positions();
			//_currentShape becomes part of _placedCubes
			for (int i = 0; i < 4; i++)
			{
				glm::vec3 position = positions[i];
				_placedCubes[(int)position.x][(int)position.y][(int)position.z] = true;
			}
			int removedLayers = 0;
			//for each layer
			for (int i = 1; i < BOARD_HEIGHT; i++)
			{
				int filled = 0;
				//find filled blocks count
				for (int j = 0; j < BOARD_WIDTH; j++)
				{
					for (int k = 0; k < BOARD_WIDTH; k++)
					{
						if (_placedCubes[j][i][k])
						{
							filled++;
						}
					}
				}
				//if fully filled
				if (filled == BOARD_WIDTH * BOARD_WIDTH)
				{
					removedLayers++;
					//remove layer
					for (int j = 0; j < BOARD_WIDTH; j++)
					{
						for (int k = 0; k < BOARD_WIDTH; k++)
						{
							_placedCubes[j][i][k] = false;
						}
					}
					//drop all placedCubes by 1 layer
					for (int l = i + 1; l < BOARD_HEIGHT; l++)
					{
						for (int j = 0; j < BOARD_WIDTH; j++)
						{
							for (int k = 0; k < BOARD_WIDTH; k++)
							{
								_placedCubes[j][l - 1][k] = _placedCubes[j][l][k];
								_placedCubes[j][l][k] = false;
							}
						}
					}
					i--;
				}
			}
			result += (pow(2, removedLayers) - 1) * 100;
			level = 1 + (result / 500);

			std::string resultString = "3D Tetris - Result: ";
			resultString.append(std::to_string(result));
			resultString.append(" Level: ");
			resultString.append(std::to_string(level));
			glfwSetWindowTitle(window, resultString.c_str());

			for (int i = 0; i < 4; i++)
			{
				glm::vec3 position = positions[i];
				if (position.y == BOARD_HEIGHT - 1 && _placedCubes[(int)position.x][BOARD_HEIGHT - 1][(int)position.z])
				{
					//YOU LOSE
					glfwSetWindowShouldClose(window, 1);
				}
			}

			setNewShape();
			_newPieceTime = glfwGetTime();
			_lastMoveDownTime = 0.0f;
		}
	}
}

void Application::Render(GLFWwindow* window)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_va->Bind();

	_shader->use();
	_shader->setFloat3("viewPos", _cameraPos);

	_diffuseTexture->Bind(0);
	_specularTexture->Bind(1);

	_shader->setInt("material.diffuse", 0);
	_shader->setInt("material.specular", 1);
	_shader->setFloat("material.shininess", 16.f);

	_shader->setFloat3("light.position", _lightPos);
	_shader->setFloat3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	_shader->setFloat3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader->setFloat3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	//all cubes
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			for (int k = 0; k < BOARD_WIDTH; k++)
			{
				if (_placedCubes[i][j][k])
				{
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3((float)i, (float)j, (float)k));
					_shader->setFloatMat4("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}
	}

	
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			//x wall
			glm::mat4 modelX = glm::mat4(1.0f);
			modelX = glm::translate(modelX, glm::vec3(7.0f, (float)i, (float)j));
			_shader->setFloatMat4("model", modelX);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			//z wall
			glm::mat4 modelZ = glm::mat4(1.0f);
			modelZ = glm::translate(modelZ, glm::vec3((float)j, (float)i, -1.0f));
			_shader->setFloatMat4("model", modelZ);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	glm::vec3 rotationPointCoordinates = _currentShape->Positions()[1];
	for (int i = 0; i < 4; i++)
	{
		//current shape
		glm::mat4 modelC = glm::mat4(1.0f);
		modelC = glm::translate(modelC, _currentShape->Positions()[i]);
		_shader->setFloatMat4("model", modelC);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//next shape
		glm::mat4 modelN = glm::mat4(1.0f);
		modelN = glm::translate(modelN, _nextShape->Positions()[i]);
		_shader->setFloatMat4("model", modelN);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//light
	_lightCubeShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, _lightPos);
	model = glm::scale(model, glm::vec3(1.0f));
	_lightCubeShader->setFloatMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
