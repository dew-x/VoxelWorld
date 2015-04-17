#pragma once


//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Window.h"
#include "GLSLProgram.h"
#include "FPSLimiter.h"
#include "OpenGLBuffers.h"
#include "Vertex.h"
#include "Geometry.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include "TextureManager.h"

#define ORIGINAL_COLOR 0
#define TEXTURE_COLOR 1
#define COMBINED_COLOR 2
#define DRAW_MODE 3

#define FIST_CAMERA 0
#define SECOND_CAMERA 1
#define NUM_CAMERAS 2

#define GAME_SPEED 0.2f

//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState{INIT, PLAY, EXIT, MENU};

//This class manages the game execution
class Game {
	public:						
		Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS);	//Constructor
		~Game();					//Destructor
		void run();					//Game execution

	private:
			//Attributes	
		std::string _windowTitle;		//Window Title
		int _drawMode;					//Define how the color is computed
		int _screenWidth;				//Screen width in pixels				
		int _screenHeight;				//Screen height in pixels				
		GameState _gameState;			//It describes the game state				
		Window _window;					//Manage the OpenGL context
		GLSLProgram _colorProgram;		//Manage the shader programs
		FPSLimiter _fpsLimiter;			//Manage the synchronization between frame rate and refresh rate
		OpenGLBuffers _openGLBuffers;	//Manage the openGL buffers		
		InputManager _inputManager;		//Manage the input devices
		TextureManager _textureManager;	//Manage all the data related to the different textures used in the game
		

		Geometry _gameElements;			//Manage the game elements
		vector <Camera> _camera;		//Manage the cameras
		int _currentCamara;

			//Internal methods
		void initSystems();
		void loadShaders();		
		void loadSceneToRender();
		void loadGameTextures();
		void initCameras();
		void updateCameraPositions();
		void gameLoop();
		void processInput();
		void updateGameObjects();
		void ExecutePlayerCommands();
		void ExecuteGameLogic();
		void drawGame();	
		
};

