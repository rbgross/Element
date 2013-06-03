/*******************************************************************************
* ElementHeader.h
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#define GLEW_STATIC 
#include <glew.h>
#include <glfw.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm> 
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

/* DEFINES */
#define NO_SHADER 0
#define PICKING_SHADER 1
#define COLOR_SHADER 2
#define ATTRIB_POSITION 0
#define ATTRIB_NORMAL 1
#define ATTRIB_TEXTURE 2

/* CLASS DEFINITIONS */
class System;
class Input;
class Renderer;
class Shader;
class Mesh;
class Transform;
class Scene;
class Camera;
class Light;
class Actor;
class Component;

// Component class definition
class Component {
	private:
	public:
		Component( void );
		virtual ~Component( void );
};

// Light class definition
class Light: public Component {
	private:
		glm::vec4 lightPos;
	public:
		Light( void );
		~Light( void );
};

// Camera class definition
class Camera: public Component {
	private:
		glm::mat4 view;
		glm::vec3 viewDirection;
		glm::vec3 upDirection;
		glm::mat4 proj;
		float fieldOfView;
		float aspectRatio;
		float nearClipPlane;
		float farClipPlane;
	public:
		Camera( void );
		~Camera( void );
};

// Transform class definition
class Transform: public Component {
	private:
	public:
		glm::mat4 model;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		Transform( void );
		~Transform( void );
};

// Mesh class definition
class Mesh: public Component {
	private:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		std::vector< float > meshData;
		std::vector< GLuint > elements;
		void loadModel( std::string );
	public:
		Mesh( std::string );
		~Mesh( void );
		void draw( void );
};

// Actor class definition
class Actor {
	private:
		unsigned int actorID;
		std::vector< Component* > components;
	public:
		Actor( void );
		virtual ~Actor( void );
		void addComponent( Component* );
		virtual void update( void );
		void draw( void );
};

// Scene class definition
class Scene {
	private:
		Actor* camera;
		Actor* light;
		Actor* cube;
	public:
		Scene( void );
		~Scene( void );
		void update( void );
		void draw( void );
};

// Shader class definition
class Shader {
	private:
		GLuint shaderProgram;
		void loadSource( std::string, std::string& );
		void printShaderInfoLog( GLuint );
		void printProgramInfoLog( GLuint );
	public:
		Shader( std::string, std::string );
		~Shader( void );
		GLuint getShaderProgram( void );
		void setUniform( std::string, glm::mat4 );
		void setUniform( std::string, glm::mat3 );
		void setUniform( std::string, glm::vec4 );
		void setUniform( std::string, glm::vec3 );
		void setUniform( std::string, unsigned int );
};

// Renderer class definition
class Renderer {
	private:
		Shader* colorShader;
		Shader* pickingShader;
		GLuint pickingFrameBuffer;
		int windowWidth;
		int windowHeight;
		int activeShader;
		bool initialize( void );

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		glm::vec4 lightPos;
		glm::vec3 diffCol;
		int objectIndex;
	public:
		Renderer( void );
		~Renderer( void );
		void setModel( glm::mat4 );
		void setView( glm::mat4 );
		void setProj( glm::mat4 );
		void setLightPos( glm::vec4 );
		void setDiffCol( glm::vec3 );
		void setObjectIndex( int );
		bool windowOpen( void );
		void draw( void );
		void usePickingShader( void );
		void useColorShader( void );
		void createPickingFrameBuffer( void );
};

// Input class definition
class Input {
	private:
	public:
		Input( void );
		~Input( void );
		void pollInput( void );
};

// System class definition
class System {
	public:
		Renderer* renderer;
		Scene* scene;
		Input* input;
		System( void );
		~System( void );
		void init( void );
		void run( void );
};

// GLOBAL VARIABLES
namespace Global {
	extern System* system;
}