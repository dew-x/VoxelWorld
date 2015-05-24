#include "Game.h"


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT),
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS),
	_currentCamara(FIST_CAMERA),
	_drawMode(TEXTURE_COLOR),
	_lightMode(0){	
}

/**
* Destructor
*/
Game::~Game()
{
	delete w;
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);		
		//Compile and Link shader
	loadShaders();
		//Prepare VBO and VAO
	_openGLBuffers.initializeBuffers(_colorProgram);
		//Create the scene to render 
	loadSceneToRender();
		//Load the game textures
	loadGameTextures();
		//Initialize the cameras
	initCameras();
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::loadShaders() {
		//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexId");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.addAttribute("vertexNormal");
		//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Load the game information. For example, where are placed enemies, the hero, walls, etc.
*/
void Game::loadSceneToRender() {
	//Load the game
	vbo = std::vector<Vertex>(0);
	w = new World();
	w->generator(vbo);

	glm::vec3 initPlayerPos = { (w->width*CUBESIZE)/2, (w->height*CUBESIZE)/2, ((w->depth*CUBESIZE)/2)+1};
	glm::vec3 initPlayerdir = { -0.1, -0.1, 0 };
	player = new Player(initPlayerPos);
	player->setDirection(initPlayerdir);

	std::cout << vbo.size() << std::endl;
	//_gameElements.loadGameElements("./resources/scene3D.txt");	
	_openGLBuffers.sendDataToGPU(&vbo[0], vbo.size());
}

/**
* Load all the textures that can be used in the game
*/
void Game::loadGameTextures() {					
		
		/*Suggestion: 
			- You can define the texture fileNames in the "scene3D.txt" file. 
			- Next, you can loop through the GameObjects stored in the Geometry class, and assign the textureID in each GameObject
		*/

		//GameObject currentGameObject;
			//Load the game textures			
		/*for (int i = 0; i < _gameElements.getNumGameElements(); i++) {
			currentGameObject = _gameElements.getGameElement(i);
			(_gameElements.getGameElement(i))._textureID = _textureManager.getTextureID(currentGameObject._textureFile);
		}*/
	tex = _textureManager.getTextureID("resources/textures/minecrafttexture.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
}

/*
* Initialize the game cameras
* The constant NUM_CAMERAS defines how many cameras are activated
*/
void Game::initCameras() {
		//Allocate space for the cameras
	_camera.resize(NUM_CAMERAS);

		//Initialize the view transformation matrix of the the cameras based on CameraPosition, CameraFront, Height, Width ..
	

	_camera[FIST_CAMERA].setCameraPosition(glm::vec3(1.0f, 1.0f, 0.1f));
	_camera[FIST_CAMERA].setCameraFront(glm::vec3(1.0f, 0.0f, 0.0f));
	//_camera[FIST_CAMERA].swapProjectionMode();


		//The 2nd camera represents a camera at third person
	_camera[SECOND_CAMERA].setCameraPosition(glm::vec3(4.0f, 4.0f, 4.0f));
	_camera[SECOND_CAMERA].setCameraFront(glm::vec3(2.0f, 2.0f, 2.0f));
	//_camera[SECOND_CAMERA].swapProjectionMode();

		//Set the current camera
	_currentCamara = FIST_CAMERA;
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;	

	while (_gameState != GameState::EXIT) {		
			//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
			//Process the input information (keyboard and mouse)
		processInput();
			//Execute pending actions
		updateGameObjects();
			//Draw the objects on the screen
		drawGame();	
			//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	_inputManager.update();
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.xrel, evnt.motion.yrel);
			player->addMouseDeltas(evnt.motion.xrel, evnt.motion.yrel);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		default:
			break;
		}
	}
}

/**
* Draw the sprites on the screen
*/
void Game::drawGame() {
	GameObject currentRenderedGameElement;

		//Uniform variables send to the shader
	GLuint modelMatrixUniform = _colorProgram.getUniformLocation("modelMatrix");
	GLuint viewMatrixUniform = _colorProgram.getUniformLocation("viewMatrix");
	GLuint projectionMatrixUniform = _colorProgram.getUniformLocation("projectionMatrix");
	GLuint drawModeUniform = _colorProgram.getUniformLocation("drawMode");
	GLuint newColorUniform = _colorProgram.getUniformLocation("objectColor");
	GLint textureDataLocation = _colorProgram.getUniformLocation("textureData");
	GLint textureScaleFactorLocation = _colorProgram.getUniformLocation("textureScaleFactor");	
	GLint modelNormalMatrix = _colorProgram.getUniformLocation("modelNormalMatrix");
	// light
	GLint lightingEnabled = _colorProgram.getUniformLocation("lightingEnabled");
	GLint isALightSource = _colorProgram.getUniformLocation("isALightSource");
	GLint lightPosition = _colorProgram.getUniformLocation("lightPosition");
	GLint viewerPosition = _colorProgram.getUniformLocation("viewerPosition");
	GLint materialAmbient = _colorProgram.getUniformLocation("material.ambient");
	GLint materialDifusse = _colorProgram.getUniformLocation("material.diffuse");
	GLint materialSpecular = _colorProgram.getUniformLocation("material.specular");
	GLint materialShininess = _colorProgram.getUniformLocation("material.shininess");
	GLint lightAmbient = _colorProgram.getUniformLocation("lightColor.ambient");
	GLint lightDifusse = _colorProgram.getUniformLocation("lightColor.diffuse");
	GLint lightSpecular = _colorProgram.getUniformLocation("lightColor.specular");
	GLint lightShininess = _colorProgram.getUniformLocation("lightColor.shininess");


		//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
		//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();	
		//Activate and Bind Texture
	glActiveTexture(tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glm::mat4 modelMatrix = glm::mat4(1.0);
	/*currentRenderedGameElement = _gameElements.getGameElement(i);
	modelMatrix = glm::translate(modelMatrix, currentRenderedGameElement._translate);
	if (currentRenderedGameElement._angle != 0) {
		modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRenderedGameElement._angle), currentRenderedGameElement._rotation);
	}
	modelMatrix = glm::scale(modelMatrix, currentRenderedGameElement._scale);

	//Texture
	glBindTexture(GL_TEXTURE_2D, currentRenderedGameElement._textureID);*/

	//Bind the uniform data to the shader
	/*Pass the matrix information to the shader
	//Get the uniform variable location
	//Pass the matrix
	//1st parameter: the location
	//2nd parameter: the number of matrices
	//3rd parameter: if we want to transpose the matrix
	//4th parameter: the matrix data
	*/
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera[_currentCamara].getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera[_currentCamara].getProjectionMatrix()));
	glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	glUniformMatrix3fv(modelNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glm::vec4 colortmp = { 1.0f, 1.0f, 1.0f, -1.0f };
	glUniform2f(textureScaleFactorLocation, 1.0f, 1.0f);
	glUniform4fv(newColorUniform, 1, glm::value_ptr(colortmp));
	//glUniform1i(textureDataLocation,0);		//This line is not needed if we use only 1 texture, it is sending the GL_TEXTURE0
	glUniform1i(drawModeUniform, _drawMode);
	// light
	glUniform1i(lightingEnabled, _lightMode);
	glUniform1i(isALightSource, 0);
	glm::vec3 lightPositionV = { (w->width*CUBESIZE) / 2, (w->height*CUBESIZE) / 2, (w->depth*CUBESIZE)*1.2 };
	glUniform3f(lightPosition, lightPositionV.x, lightPositionV.y, lightPositionV.z);
	glm::vec3 playerPos = player->getPosition();
	glUniform3f(viewerPosition, playerPos.x, playerPos.y, playerPos.z);
	// 0.05	0.05	0.05	0.5	0.5	0.5	0.7	0.7	0.7	.078125
	glm::vec3 materialAmbientV = { 0.2,0.2,0.2 };
	glm::vec3 materialDifusseV = { 0.5,	0.5,	0.5 };
	glm::vec3 materialSpecularV = { 0.7,	0.7,	0.7 };
	float materialShine = 0.078125f;
	glUniform3f(materialAmbient, materialAmbientV.x, materialAmbientV.y, materialAmbientV.z);
	glUniform3f(materialDifusse, materialDifusseV.x, materialDifusseV.y, materialDifusseV.z);
	glUniform3f(materialSpecular, materialSpecularV.x, materialSpecularV.y, materialSpecularV.z);
	glUniform1f(materialShininess, materialShine);
	glm::vec3 lightAmbientV = { 1, 1, 1 };
	glm::vec3 lightDifusseV = { 1, 1, 1 };
	glm::vec3 lightSpecularV = { 0, 0, 0 };
	float lightShine = 1;
	glUniform3f(lightAmbient, lightAmbientV.x, lightAmbientV.y, lightAmbientV.z);
	glUniform3f(lightDifusse, lightDifusseV.x, lightDifusseV.y, lightDifusseV.z);
	glUniform3f(lightSpecular, lightSpecularV.x, lightSpecularV.y, lightSpecularV.z);
	glUniform1f(lightShininess, lightShine);
	_openGLBuffers.drawData(0, vbo.size());
		//Each object MUST BE RENDERED based on the position, rotation and scale
	/*for (int i = 0; i < _gameElements.getNumGameElements(); i++) {		
			//Model transformation matrix will scale, rotate and translate the current object. This matrix is built in the inverse order of the operations
		glm::mat4 modelMatrix;		
		currentRenderedGameElement = _gameElements.getGameElement(i);
		modelMatrix = glm::translate(modelMatrix, currentRenderedGameElement._translate);
		if (currentRenderedGameElement._angle != 0) {
			modelMatrix = glm::rotate(modelMatrix, glm::radians(currentRenderedGameElement._angle), currentRenderedGameElement._rotation);
		}
		modelMatrix = glm::scale(modelMatrix, currentRenderedGameElement._scale);

			//Texture
		glBindTexture(GL_TEXTURE_2D, currentRenderedGameElement._textureID);

			//Bind the uniform data to the shader
			/*Pass the matrix information to the shader
			//Get the uniform variable location
			//Pass the matrix
			//1st parameter: the location
			//2nd parameter: the number of matrices
			//3rd parameter: if we want to transpose the matrix
			//4th parameter: the matrix data
				
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera[_currentCamara].getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera[_currentCamara].getProjectionMatrix()));
		glUniform4fv(newColorUniform, 1, glm::value_ptr(currentRenderedGameElement._color));
		glUniform1i(textureDataLocation, 0);		//This line is not needed if we use only 1 texture, it is sending the GL_TEXTURE0
		glUniform1i(drawModeUniform, _drawMode);
		if (currentRenderedGameElement._textureRepetion) {
			glUniform2f(textureScaleFactorLocation, currentRenderedGameElement._scale.x, currentRenderedGameElement._scale.y);
		}
		else {
			glUniform2f(textureScaleFactorLocation, 1.0f,1.0f);
		}
			//Send data to GPU
		_openGLBuffers.sendDataToGPU(_gameElements.getData(currentRenderedGameElement._objectType), _gameElements.getNumVertices(currentRenderedGameElement._objectType));
		
			//Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}*/
	glBindTexture(GL_TEXTURE_2D, 0);
		//Unbind the program
	_colorProgram.unuse();

		//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}


/*
* Execute the actions that must update the game objects
*/
void Game::updateGameObjects() {
		//Execute the player actions (keyboard and mouse)
	ExecutePlayerCommands();
		//Execute the game logic
	ExecuteGameLogic();
	_camera[_currentCamara].setCameraPosition(player->getPosition());
	_camera[_currentCamara].setCameraFront(player->getCameraFront());
}

/**
* Executes the actions sent by the user by means of the keyboard and mouse
* Reserved keys: 
	- t changes the draw mode: 0 (Line polygons) 1 (Fill polygons), 2(fill and line polygons), 3(texture) and 4(combination of texture and color)
	- c changes the camera
*/
void Game::ExecutePlayerCommands() {
		//Changes the draw mode
	glm::vec2 deltaPos = { 0, 0 };
	glm::vec3 lookAt = w->transformLookAt(player->getCameraFront());
	float deltaT = 1.0 / 60.0;

	if (_inputManager.isKeyPressed(SDLK_t)){
		_drawMode = (_drawMode + 1) % DRAW_MODE;
		std::cout << "DRAWMODE" << _drawMode << std::endl;
	}
	
		//Changes the current camera 
	if (_inputManager.isKeyPressed(SDLK_c)){
		_currentCamara = (_currentCamara + 1) % NUM_CAMERAS;
	}
	
	if (_inputManager.isKeyPressed(SDLK_l)){
		_lightMode = (_lightMode + 1) % 2;
	}
		//Add the additional keys pressed by the player for moving/changing the state of the player object

	if (_inputManager.isKeyDown(SDLK_w)){
		//_camera[_currentCamara].move(0);
		deltaPos.x -= 1;
	}
	if (_inputManager.isKeyDown(SDLK_s)){
		deltaPos.x += 1;
	}
	if (_inputManager.isKeyDown(SDLK_d)){
		deltaPos.y += 1;
	}
	if (_inputManager.isKeyDown(SDLK_a)){
		deltaPos.y -= 1;
	}
	if (_inputManager.isKeyPressed(SDLK_f)){
		if (w->cubeTipe(lookAt) == 1){
			w->eliminateCube(lookAt);
			player->addCub();
		}
	}
	if (_inputManager.isKeyPressed(SDLK_g)){
		if (w->cubeTipe(lookAt) == 0){
			w->putCube(lookAt);
			player->elimCub();
		}
	}
	if (deltaPos.x != 0 || deltaPos.y != 0){
		//deltaPos = glm::normalize(deltaPos)*deltaT;
		player->moveDeltas(deltaPos.x, deltaPos.y, w);
	}
	player->addGravity(w);
}

/*
* Execute the game logic
*/
void Game::ExecuteGameLogic() {
	//Execute the game logic (move bullets, enemies, etc.)

}
