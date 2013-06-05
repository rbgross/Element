/***************************************************************************************************
* Camera.cpp
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Camera function
*
* Placeholder.
***************************************************************************************************/
Camera::Camera( void ) {
	this->upDirection = glm::vec3( 0.0f, 1.0f, 0.0f );
	this->viewDirection = glm::vec3( 0.0f, 0.0f, 0.0f );
	
	// Assign the value for the view matrix
	this->view = glm::lookAt( glm::vec3( 10.0f, 10.0f, 10.0f ), this->viewDirection, this->upDirection );
	Global::system->renderer->setView( this->view );

	this->fieldOfView = 45.0f;
	this->aspectRatio = ( float ) 1024 / ( float ) 768;
	this->nearClipPlane = 0.1f;
	this->farClipPlane = 1000.0f;

	// Assign the value for the projection matrix
	this->proj = glm::perspective( this->fieldOfView, this->aspectRatio, this->nearClipPlane, this->farClipPlane );
	Global::system->renderer->setProj( this->proj );
}

/***************************************************************************************************
* ~Camera function
*
* Placeholder.
***************************************************************************************************/
Camera::~Camera( void ) {

}