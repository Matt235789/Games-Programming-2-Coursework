#include "TheGame.h"
#include "Camera.h"
#include <iostream>
#include <string>



unsigned int indices[] = { 0, 1, 2 };

Transform transform;
Transform transform1;
Transform transform2;

TheGame::TheGame()
{
	_gameState = GameState::PLAY;
	ScreenDisplay* _gameDisplay = new ScreenDisplay(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
	ModelTexture* texture();
	ModelTexture* texture2();
	Shader* shader();
}

TheGame::~TheGame()
{
}

void TheGame::runGame()
{
	initSystems(); 
	gameLoop();
}

bool TheGame::checkCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distanceSq = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

		if (distanceSq < (m1Rad * m2Rad) * (m1Rad * m2Rad))
		{
			cout << "Collision";
			return true;
		}

	return false;
}

void TheGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	mesh1.loadModel("..\\res\\CandyCane.obj");
	texture.init("..\\res\\redandwhite.jpg");
	shader.init("..\\res\\shader"); //new shader 

	mesh2.loadModel("..\\res\\monkey3.obj");
	texture2.init("..\\res\\TexturedPattern.jpg");
	shader.init("..\\res\\shader"); //new shader

	mesh3.loadModel("..\\res\\peanut.obj");
	texture3.init("..\\res\\peanut.jpg"); //
	shader.init("..\\res\\shader"); //new shader

	//enable fog
	glEnable(GL_FOG);

	myCamera.initCamera(glm::vec3(0, 0, -40), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);
	counter = 0.0f;

	
	
}

void TheGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		updateTransform();
		checkCollision(*mesh2.shperepos(), *mesh2.radius(), *mesh1.shperepos(), *mesh1.radius());
	}
}

void TheGame::processInput()
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:

			//Move object by coords when key is pressed
				if (event.key.keysym.sym == SDLK_d)
				{
					CoordX -= 0.3;
				}
				
				if (event.key.keysym.sym == SDLK_a)
				{
					CoordX += 0.3;
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					CoordY += 0.3;
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					CoordY -= 0.3;
				}
				
				break;


			case SDL_QUIT:
				_gameState = GameState::EXIT;
		}
	}
	
}

void TheGame::updateTransform()
{
	//candy cane
	transform.SetPos(glm::vec3(0, 0, 0)); //position of object
	transform.SetRot(glm::vec3(0.0, 0.0, sin(counter))); //rotation of object
	transform.SetScale(glm::vec3(0.1, 0.1, 0.1)); //scale of object

	//monkey
	transform1.SetPos(glm::vec3(CoordX, CoordY, CoordZ));
	transform1.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform1.SetScale(glm::vec3(1.0, 1.0, 1.0));

	//peanut
	transform2.SetPos(glm::vec3(15, 5, 0));
	transform2.SetRot(glm::vec3(0.0, counter * 1.0006, 0.0));
	transform2.SetScale(glm::vec3(0.7, 0.7, 0.7));

	counter = counter + 0.01f;
}


void TheGame::drawGame()
{
	_gameDisplay.clearDisplay(0.5f, 0.5f, 0.5f, 1.0f);
	
	//candy cane
	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh1.draw();
	mesh1.updateTheSphere(*transform.GetPos(), 2.0f);

	//monkey
	shader.Update(transform1, myCamera);
	texture2.Bind(0);
	mesh2.draw();
	mesh2.updateTheSphere(*transform1.GetPos(), 2.0f);

	//peanut
	shader.Update(transform2, myCamera);
	texture3.Bind(0);
	mesh3.draw();

	// This array stores the colour used for the fog
	GLfloat fogColour[] = { 0.5f, 0.5f, 0.5f, 1 };
	glFogfv(GL_FOG_COLOR, fogColour);

	//fog strength will increase in a linear fashion
	glFogi(GL_FOG_MODE, GL_LINEAR);

	//Where the fog will start drawing from the camera and when it will stop
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 45.0f);

				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();

} 