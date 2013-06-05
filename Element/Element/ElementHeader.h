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
#include <map>
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
class Timer;
class Renderer;
class Shader;
class Scene;
class Actor;
class Component;
class Transform;
class Camera;
class Light;
class Mesh;

// Component class definition
class Component {
	private:
	protected:
	public:
		Actor* owner;
		Component( void );
		virtual ~Component( void );
		virtual void setup( Actor* ) = NULL;
};

// Light class definition
class Light: public Component {
	private:
	public:
		bool local;
		Light( void );
		~Light( void );
		void setup( Actor* );
};

// Camera class definition
class Camera: public Component {
	private:
	public:
		glm::mat4 view;
		glm::vec3 viewDirection;
		glm::vec3 upDirection;
		glm::mat4 proj;
		float fieldOfView;
		float aspectRatio;
		float nearClipPlane;
		float farClipPlane;
		Camera( void );
		~Camera( void );
		void setup( Actor* );
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
		void setup( Actor* );
};

// Mesh class definition
class Mesh: public Component {
	private:
	public:
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		std::vector< float > meshData;
		std::vector< GLuint > elements;
		void loadModel( std::string );
		Mesh( std::string );
		~Mesh( void );
		void setup( Actor* );
		void draw( void );
};

// Actor class definition
class Actor {
	private:
	public:
		unsigned int actorID;
		std::map< std::string, Component* > components;
		Actor( void );
		virtual ~Actor( void );
		virtual void setup( void );
		void addComponent( std::string, Component* );
		Component* getComponent( std::string );
		virtual void update( void );
		void draw( void );
};

// Scene class definition
class Scene {
	private:
	public:
		Actor* camera;
		Actor* light;
		Actor* cube;
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
		int windowWidth;
		int windowHeight;
		bool initialize( void );
	public:
		Renderer( void );
		~Renderer( void );
		void setModel( glm::mat4 );
		void setView( glm::mat4 );
		void setProj( glm::mat4 );
		void setLightPos( glm::vec4 );
		void setDiffCol( glm::vec3 );
		bool windowOpen( void );
		void draw( void );
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