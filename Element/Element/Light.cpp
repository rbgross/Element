/***************************************************************************************************
* Light.cpp
*
* Placeholder.
***************************************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Light function
*
* Placeholder.
***************************************************************************************************/
Light::Light( void ) {
	
}

/***************************************************************************************************
* ~Light function
*
* Placeholder.
***************************************************************************************************/
Light::~Light( void ) {

}

/***************************************************************************************************
* setup function
*
* Placeholder.
***************************************************************************************************/
void Light::setup( Actor* owner ) {
	this->owner = owner;
	this->local = true;

	( ( Transform* ) this->owner->getComponent( "transform" ) )->position = glm::vec3( 0.0f, 10.0f, 10.0f );

	glm::vec4 lightPos = glm::vec4( ( ( Transform* ) this->owner->getComponent( "transform" ) )->position, 0.0f );
	if ( this->local ) {
		lightPos.w = 1.0f;
	}

	// Assign the value for the light position in world space
	Global::system->renderer->setLightPos( lightPos );
}