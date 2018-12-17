#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "ScreenDisplay.h" 
#include "Shader.h"
#include "Mesh.h"
#include "ModelTexture.h"
#include "transform.h"

enum class GameState{PLAY, EXIT};

class TheGame
{
public:
	TheGame();
	~TheGame();

	void runGame();

	bool checkCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void updateTransform();

	ScreenDisplay _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Camera myCamera;
	ModelTexture texture; 
	Shader shader;
	ModelTexture texture2;
	ModelTexture texture3;

	float CoordX = 0.0f;
	float CoordY = -10.0f;
	float CoordZ = 0.0f;


	float counter;


};

