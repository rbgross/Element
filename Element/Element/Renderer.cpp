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
Renderer::Renderer( void ) {	
	this->windowWidth = 1024;
	this->windowHeight = 768;

	// Initalize the OpenGL context and Renderer
	if ( !this->initialize() ) {
		exit( EXIT_FAILURE );
	}

	// Load the shaders
	this->colorShader = new Shader( "ADS.vert", "ADS.frag" );
}

/***************************************************************************************************
* ~Renderer function
*
* Placeholder.
***************************************************************************************************/
Renderer::~Renderer( void ) {	
	// Close GLFW
	delete this->colorShader;
    glfwTerminate();
}

/***************************************************************************************************
* setModel function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setModel( glm::mat4 model ) {
	this->colorShader->setUniform( "model", model );
}

/***************************************************************************************************
* setView function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setView( glm::mat4 view ) {
	this->colorShader->setUniform( "view", view );
}

/***************************************************************************************************
* setProj function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setProj( glm::mat4 proj ) {
	this->colorShader->setUniform( "proj", proj );
}

/***************************************************************************************************
* setLightPos function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setLightPos( glm::vec4 lightPos ) {
	this->colorShader->setUniform( "lightPosition", lightPos );
}

/***************************************************************************************************
* setDiffCol function
*
* Placeholder.
***************************************************************************************************/
void Renderer::setDiffCol( glm::vec3 diffCol ) {
	this->colorShader->setUniform( "diffuseColor", diffCol );
}

/***************************************************************************************************
* windowOpen function
*
* Placeholder.
***************************************************************************************************/
bool Renderer::windowOpen( void ) {	
	if ( glfwGetWindowParam( GLFW_OPENED ) ) {
		return true;
	} else {
		return false;
	}
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Renderer::draw( void ) {
	// Bind the default screen buffer and clear the previous data
	glUseProgram( this->colorShader->getShaderProgram() );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if ( glfwGetKey( 'W' ) == GLFW_PRESS ) {
		( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model = glm::translate( ( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model, glm::vec3( 0.0f, 0.0f, -0.1f ) ); 
	}

	if ( glfwGetKey( 'S' ) == GLFW_PRESS ) {
		( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model = glm::translate( ( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model, glm::vec3( 0.0f, 0.0f, 0.1f ) ); 
	}

	if ( glfwGetKey( 'A' ) == GLFW_PRESS ) {
		( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model = glm::translate( ( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model, glm::vec3( -0.1f, 0.0f, 0.0f ) ); 
	}

	if ( glfwGetKey( 'D' ) == GLFW_PRESS ) {
		( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model = glm::translate( ( ( Transform* ) Global::system->scene->cube->getComponent( "transform" ) )->model, glm::vec3( 0.1f, 0.0f, 0.0f ) ); 
	}

	// Draw the scene
	Global::system->scene->draw();
		
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