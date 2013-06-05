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
	
}

/***************************************************************************************************
* ~Actor function
*
* Placeholder.
***************************************************************************************************/
Actor::~Actor( void ) {
	this->components.clear();
}

/***************************************************************************************************
* setup function
*
* Placeholder.
***************************************************************************************************/
void Actor::setup( void ) {
	std::map< std::string, Component* >::iterator i;
	for ( i = this->components.begin(); i != this->components.end(); i++ ) {
		i->second->setup( this );
	}
}

/***************************************************************************************************
* addComponent function
*
* Placeholder.
***************************************************************************************************/
void Actor::addComponent( std::string type, Component* component ) {
	this->components.insert( std::pair< std::string, Component* >( type, component ) );
}

/***************************************************************************************************
* getComponent function
*
* Placeholder.
***************************************************************************************************/
Component* Actor::getComponent( std::string type ) {
	return this->components.find( type )->second;
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
	Global::system->renderer->setModel( ( ( Transform* ) this->getComponent( "transform" ) )->model );
	Global::system->renderer->setDiffCol( glm::vec3( 0.25f, 0.5f, 1.0f ) );
	( ( Mesh* ) this->getComponent( "mesh" ) )->draw();
}