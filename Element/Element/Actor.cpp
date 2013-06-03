/*******************************************************************************
* Actor.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Actor function
*
* Placeholder.
***************************************************************************************************/
Actor::Actor( void ) {
	this->actorID = 1;
}

/***************************************************************************************************
* ~Actor function
*
* Placeholder.
***************************************************************************************************/
Actor::~Actor( void ) {
	for ( unsigned int i = 0; i < this->components.size(); i++ ) {
		delete this->components[ i ];
	}
}

/***************************************************************************************************
* addComponent function
*
* Placeholder.
***************************************************************************************************/
void Actor::addComponent( Component* component ) {
	this->components.push_back( component );
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void Actor::update( void ) {
	
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Actor::draw( void ) {
	// Calculate and apply the Actor model transformation
	Global::system->renderer->setModel( ( ( Transform* ) this->components[ 0 ] )->model );
	Global::system->renderer->setObjectIndex( this->actorID );
	Global::system->renderer->setDiffCol( glm::vec3( 0.0f, 0.5f, 1.0f ) );
	( ( Mesh* ) this->components[ 1 ] )->draw();
}