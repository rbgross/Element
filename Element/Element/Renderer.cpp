/***************************************************************************************************
* Renderer.cpp
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Renderer function
*
* Placeholder.
***************************************************************************************************/
Renderer::Renderer( System* system ) {
	this->system = system;
	
	this->windowWidth = 1024;
	this->windowHeight = 768;

	// Initalize the OpenGL context and Renderer
	if ( !this->initialize() ) {
		std::cerr << "Failed to create an OpenGL 4.0 context and Renderer.\n";
		exit( EXIT_FAILURE );
	}

	// Load the shaders
	this->colorShader = new Shader( "ADS.vert", "ADS.frag" );
	this->pickingShader = new Shader( "Picking.vert", "Picking.frag" );
	this->activeShader = NO_SHADER;

	// Assign the value for the projection matrix
	glm::mat4 proj = glm::perspective( 45.0f, ( float ) this->windowWidth / ( float ) this->windowHeight, 0.1f, 1000.0f );
	this->setProj( proj );

	this->createPickingFrameBuffer();
}

/***************************************************************************************************
* ~Renderer function
*
* Placeholder.
***************************************************************************************************/
Renderer::~Renderer( void ) {	
	// Close GLFW
	delete this->colorShader;
	delete this->pickingShader;
	glDeleteFramebuffers( 1, &this->pickingFrameBuffer );
    glfwTerminate();
}

/***************************************************************************************************
* setModel function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setModel( glm::mat4 model ) {
	this->model = model;
	if ( this->activeShader == COLOR_SHADER ) {
		this->colorShader->setUniform( "model", model );
	}
	if ( this->activeShader == PICKING_SHADER ) {
		this->pickingShader->setUniform( "model", model );
	}
}

/***************************************************************************************************
* setView function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setView( glm::mat4 view ) {
	this->view = view;
	if ( this->activeShader == COLOR_SHADER ) {
		this->colorShader->setUniform( "view", view );
	}
	if ( this->activeShader == PICKING_SHADER ) {
		this->pickingShader->setUniform( "view", view );
	}
}

/***************************************************************************************************
* setProj function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setProj( glm::mat4 proj ) {
	this->proj =  proj;
	if ( this->activeShader == COLOR_SHADER ) {
		this->colorShader->setUniform( "proj", proj );
	}
	if ( this->activeShader == PICKING_SHADER ) {
		this->pickingShader->setUniform( "proj", proj );
	}
}

/***************************************************************************************************
* setLightPos function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setLightPos( glm::vec4 lightPos ) {
	this->lightPos = lightPos;
	if ( this->activeShader == COLOR_SHADER ) {
		this->colorShader->setUniform( "lightPosition", lightPos );
	}
}

/***************************************************************************************************
* setDiffCol function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setDiffCol( glm::vec3 diffCol ) {
	this->diffCol = diffCol;
	if ( this->activeShader == COLOR_SHADER ) {
		this->colorShader->setUniform( "diffuseColor", diffCol );
	}
}

/***************************************************************************************************
* setObjectIndex function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setObjectIndex( int objectIndex ) {
	this->objectIndex = objectIndex;
	if ( this->activeShader == PICKING_SHADER ) {
		this->pickingShader->setUniform( "objectID", objectIndex );
	}
}

/***************************************************************************************************
* windowOpen function
*
* Placeholder.
***************************************************************************************************/
bool Renderer::windowOpen( void ) {	
	return glfwGetWindowParam( GLFW_OPENED );
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Renderer::draw( void ) {
	// Bind the default screen buffer and clear the previous data
	this->usePickingShader();
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw the scene
	this->system->scene->draw();

	// Get the viewpoint coordinates of the mouse cursor (0:width, height:0)
	int mouseX;
	int mouseY;
	glfwGetMousePos( &mouseX, &mouseY );
	// Read the object ID of the cube under the mouse cursor
	glReadBuffer( GL_COLOR_ATTACHMENT0 );
	unsigned int pixelInfo[ 3 ] = { 0, 0, 0 };
	glReadPixels( mouseX, 768 - mouseY, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, pixelInfo );
	glReadBuffer( GL_NONE );
	std::cout << pixelInfo[ 0 ] << std::endl;
	// Determine which cube is selected
	if ( pixelInfo[ 0 ] > 0 && glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT ) ) {
		std::cout << "HERE" << std::endl;
	}

	// Bind the default screen buffer and clear the previous data
	this->useColorShader();
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw the scene
	this->system->scene->draw();
		
	// Swap the buffers
	glfwSwapBuffers();
}

/***************************************************************************************************
* initialize function
*
* Placeholder.
***************************************************************************************************/
bool Renderer::initialize( void ) {
	// Initalize GLFW
	if ( !glfwInit() ) {
		std::cerr << "Failed to initialize GLFW.\n";
		return false;
	}

	// Provide Renderer hints to GLFW
	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 16 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
	glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );

	// Open a GLFW Renderer
	if ( !glfwOpenWindow( this->windowWidth, this->windowHeight, 0, 0, 0, 0, 24, 8, GLFW_WINDOW ) ) {
		std::cerr << "Failed to open GLFW window.\n";
		return false;
	}
	glfwSetWindowTitle( "Game Test" );

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if ( glewInit() != GLEW_OK ) {
		std::cerr << "Failed to initialize GLEW.\n";
		return false;
	}

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );

	return true;
}

/***************************************************************************************************
* usePickingShader function
*
* Placeholder.
***************************************************************************************************/
void Renderer::usePickingShader( void ) {
	this->activeShader = PICKING_SHADER;
	glUseProgram( this->pickingShader->getShaderProgram() );
	glBindFramebuffer( GL_FRAMEBUFFER, this->pickingFrameBuffer );
	this->setModel( this->model );
	this->setView( this->view );
	this->setProj( this->proj );
	this->setObjectIndex( this->objectIndex );
}

/***************************************************************************************************
* useColorShader function
*
* Placeholder.
***************************************************************************************************/
void Renderer::useColorShader( void ) {
	this->activeShader = COLOR_SHADER;
	glUseProgram( this->colorShader->getShaderProgram() );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	this->setModel( this->model );
	this->setView( this->view );
	this->setProj( this->proj );
	this->setLightPos( this->lightPos );
	this->setDiffCol( this->diffCol );
}

/***************************************************************************************************
* createFrameBuffer function
*
* Placeholder.
***************************************************************************************************/
void Renderer::createPickingFrameBuffer( void ) {
	// Create frame buffer
	glGenFramebuffers( 1, &this->pickingFrameBuffer );
	glBindFramebuffer( GL_FRAMEBUFFER, this->pickingFrameBuffer );
	
	// Create texture to hold object data
	GLuint pickingTexture;
	glActiveTexture( GL_TEXTURE0 );
	glGenTextures( 1, &pickingTexture );
	glBindTexture( GL_TEXTURE_2D, pickingTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32UI, windowWidth, windowHeight, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0 );
	
	// Create depth render buffer
	GLuint depthTexture;
	glGenRenderbuffers( 1, &depthTexture );
	glBindRenderbuffer( GL_RENDERBUFFER, depthTexture );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTexture );

	GLenum drawBuffers[] = { GL_NONE, GL_COLOR_ATTACHMENT0 };
	glDrawBuffers( 2, drawBuffers );
}