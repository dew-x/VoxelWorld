#include "Window.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "ErrorManagement.h"


/**
* Initialize the game engine
*/
Window::Window() 	{
	//Initialize all the SDL elements, even they are not used for this example
	SDL_Init(SDL_INIT_EVERYTHING);

	//All the SDL_GL_Set attributes must be done before creating the window
	//Tell SDL that we want a double buffered window so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

/**
* Destructor
*/
Window::~Window() 	{
}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	//Check the flags that passes the user. If we want to add more parameters, we need to extend the enum in the Window.h
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & (unsigned int)WindowFlags::INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & (unsigned int)WindowFlags::FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & (unsigned int)WindowFlags::BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	//Create a SDL window centered into the middle of the screen
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);
	//Check for errors
	if (_sdlWindow == nullptr) {
		ErrorManagement::errorRunTime("SDL Window could not be created!");
	}

	//Set up our OpenGL context. It will store the OpenGL things like vertex, buffers,...
	//The context is going to be stored in the window so the local variable won't be used longer
	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr) {
		ErrorManagement::errorRunTime("SDL_GL context could not be created!");
	}

	//Set up glew (optional but recommended)
	//Initialize all the extensions setup. It will help to manage things that may be are not supported by our hardware
	//GLEW obtains information on the supported extensions from the graphics driver. Experimental or pre-release drivers, however, might not report every available extension through the standard mechanism, in which case GLEW will report it unsupported. To circumvent this situation, the glewExperimental global switch can be turned on by setting it to  GL_TRUE before calling glewInit(), which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		ErrorManagement::errorRunTime("Could not initialize glew!!");
	}

	//Check the opengl version
	printf("****** OpenGL Version %s ********\n", glGetString(GL_VERSION));

	//Set the color that will be set every time the color buffer is initialized
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Set the base depth that will be set every time the depth buffer is initialized
	glClearDepth(1.0);

	//Set VSYNC. 0 means disable, 1 means enable
	//If it's enable, it automatically syncs the fps with the monitor, so, we don't need to use SDL_Delay
	SDL_GL_SetSwapInterval(0);
	
	//Activate the Z-buffer
	glEnable(GL_DEPTH_TEST);
		
	//Set the accuracy of OpenGL
	setglHint();

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);
	return 0;
}


void Window::swapBuffer() {
	SDL_GL_SwapWindow(_sdlWindow);
}


/**
* Certain aspects of GL behavior, when there is room for interpretation, can be controlled with hints
* See more at: https://www.opengl.org/sdk/docs/man2/xhtml/glHint.xml 
*/
void Window::setglHint() {	
	//Indicates the accuracy of fog calculation.If per - pixel fog calculation is not efficiently supported by the GL implementation, hinting GL_DONT_CARE or GL_FASTEST can result in per - vertex calculation of fog effects.	
	glHint(GL_FOG_HINT, GL_NICEST);

	//Indicates the accuracy of the derivative calculation for the GL shading language fragment processing built - in functions : dFdx, dFdy, and fwidth.
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);

	//Indicates the quality of filtering when generating mipmap images.
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

	//Indicates the sampling quality of antialiased lines.If a larger filter function is applied, hinting GL_NICEST can result in more pixel fragments being generated during rasterization.
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	//Indicates the quality of color, texture coordinate, and fog coordinate interpolation.If perspective - corrected parameter interpolation is not efficiently supported by the GL implementation, hinting GL_DONT_CARE or GL_FASTEST can result in simple linear interpolation of colors and / or texture coordinates.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Indicates the sampling quality of antialiased points.If a larger filter function is applied, hinting GL_NICEST can result in more pixel fragments being generated during rasterization.
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	//Indicates the sampling quality of antialiased polygons.Hinting GL_NICEST can result in more pixel fragments being generated during rasterization, if a larger filter function is applied.
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//Indicates the quality and performance of the compressing texture images. Hinting GL_FASTEST indicates that texture images should be compressed as quickly as possible, while GL_NICEST indicates that texture images should be compressed with as little image quality loss as possible. GL_NICEST should be selected if the texture is to be retrieved by glGetCompressedTexImage for reuse.
	glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);
}


