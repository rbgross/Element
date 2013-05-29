/*******************************************************************************
* Object.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Object function
*
* Placeholder.
***************************************************************************************************/
Object::Object( System* system ) {
	this->system = system;
	this->objectID = 1;
	this->transform = new Transform();
	this->mesh = new Mesh( "C:\\Users\\Ryan\\Game Tests\\CubeTest2.obj" );
}

/***************************************************************************************************
* ~Object function
*
* Placeholder.
***************************************************************************************************/
Object::~Object( void ) {
	delete this->transform;
	delete this->mesh;
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void Object::update( void ) {
	
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Object::draw( void ) {
	// Calculate and apply the Object model transformation
	this->system->renderer->setModel( this->transform->model );
	this->system->renderer->setObjectIndex( this->objectID );
	this->system->renderer->setDiffCol( glm::vec3( 0.0f, 0.5f, 1.0f ) );
	this->mesh->draw();
}