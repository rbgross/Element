/*******************************************************************************
* System.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* System function
*
* Placeholder.
***************************************************************************************************/
System::System( void ) {
	this->renderer = NULL;
	this->input = NULL;
	this->scene = NULL;
}

/***************************************************************************************************
* ~System function
*
* Placeholder.
***************************************************************************************************/
System::~System( void ) {
	delete this->scene;
	delete this->input;
	delete this->renderer;
}

/***************************************************************************************************
* init function
*
* Placeholder.
***************************************************************************************************/
void System::init( void ) {
	this->renderer = new Renderer();
	this->input = new Input();
	this->scene = new Scene();
}

/***************************************************************************************************
* run function
*
* Placeholder.
***************************************************************************************************/
void System::run( void ) {
	while ( this->renderer->windowOpen() ) {
		this->input->pollInput();
		this->scene->update();
		this->renderer->draw();
	}
}