/***************************************************************************************************
* Shader.cpp
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Shader function
*
* Placeholder.
***************************************************************************************************/
Shader::Shader( std::string vertexFileName, std::string fragmentFileName ) {
	std::string vertexSource;
	this->loadSource( vertexFileName, vertexSource );
	const char* vertexCode = vertexSource.c_str();
	
	std::string fragmentSource;
	this->loadSource( fragmentFileName, fragmentSource );
	const char* fragmentCode = fragmentSource.c_str();

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexCode, NULL );
	glCompileShader( vertexShader );

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentCode, NULL );
	glCompileShader( fragmentShader );

	// Link the vertex, geometry, and fragment shader into a shader program
	this->shaderProgram = glCreateProgram();
	glAttachShader( this->shaderProgram, vertexShader );
	glAttachShader( this->shaderProgram, fragmentShader );
	glBindAttribLocation( this->shaderProgram, ATTRIB_POSITION, "position" );
	glBindAttribLocation( this->shaderProgram, ATTRIB_NORMAL, "normal" ); 
	glBindFragDataLocation( this->shaderProgram, 0, "outColor" );
	glLinkProgram( this->shaderProgram );
	glUseProgram( this->shaderProgram );

	// Print the shader logs
	printShaderInfoLog( vertexShader );
	printShaderInfoLog( fragmentShader );
	printProgramInfoLog( this->shaderProgram );

	// Flag the vertex and fragment shaders for deletion when not in use
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
}

/***************************************************************************************************
* ~ColorShader function
*
* Placeholder.
***************************************************************************************************/
Shader::~Shader( void ) {
	// Clean up the program before exiting
	glDeleteProgram( this->shaderProgram );
}

/***************************************************************************************************
* getShaderProgram function
*
* Placeholder.
***************************************************************************************************/
GLuint Shader::getShaderProgram( void ) {
	return this->shaderProgram;
}

/***************************************************************************************************
* setUniform function
*
* Placeholder.
***************************************************************************************************/
void Shader::setUniform( std::string name, glm::mat4 value ) {
	glUniformMatrix4fv( glGetUniformLocation( this->shaderProgram, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
}

/***************************************************************************************************
* setUniform function
*
* Placeholder.
***************************************************************************************************/
void Shader::setUniform( std::string name, glm::mat3 value ) {
	glUniformMatrix3fv( glGetUniformLocation( this->shaderProgram, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
}

/***************************************************************************************************
* setUniform function
*
* Placeholder.
***************************************************************************************************/
void Shader::setUniform( std::string name, glm::vec4 value ) {
	glUniform4fv( glGetUniformLocation( this->shaderProgram, name.c_str() ), 1, glm::value_ptr( value ) );
}

/***************************************************************************************************
* setUniform function
*
* Placeholder.
***************************************************************************************************/
void Shader::setUniform( std::string name, glm::vec3 value ) {
	glUniform3fv( glGetUniformLocation( this->shaderProgram, name.c_str() ), 1, glm::value_ptr( value ) );
}

/***************************************************************************************************
* setUniform function
*
* Placeholder.
***************************************************************************************************/
void Shader::setUniform( std::string name, unsigned int value ) {
	glUniform1ui( glGetUniformLocation( this->shaderProgram, name.c_str() ), value );
}

/***************************************************************************************************
* loadSource function
*
* Placeholder.
***************************************************************************************************/
void Shader::loadSource( std::string fileName, std::string& source ) {
	std::ifstream in( fileName.c_str() );
	if ( !in ) {
		std::cerr << "Unable to open " << fileName << ".";
		return;
	}

	std::stringstream buffer;
	buffer << in.rdbuf();
	source = buffer.str();

	in.close();
}

/***************************************************************************************************
* printShaderInfoLog function
*
* Placeholder.
***************************************************************************************************/
void Shader::printShaderInfoLog( GLuint obj ) {
    int infoLogLength = 0; 
    glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &infoLogLength );
 
	if ( infoLogLength > 1 ) {
		int charsWritten = 0;
		char *infoLog = new char[ infoLogLength ];
        glGetShaderInfoLog( obj, infoLogLength, &charsWritten, infoLog );
		std::cerr << infoLog << std::endl;
		delete infoLog;
	}
}
 
/***************************************************************************************************
* printProgramInfoLog function
*
* Placeholder.
***************************************************************************************************/
void Shader::printProgramInfoLog( GLuint obj ) {
    int infoLogLength = 0; 
    glGetProgramiv( obj, GL_INFO_LOG_LENGTH, &infoLogLength );
 
    if ( infoLogLength > 1 ) {
        int charsWritten = 0;
		char* infoLog = new char[ infoLogLength ];
        glGetProgramInfoLog( obj, infoLogLength, &charsWritten, infoLog );
		std::cerr << infoLog << std::endl;
		delete infoLog;
    }
}