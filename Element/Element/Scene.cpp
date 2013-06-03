/*******************************************************************************
* Scene.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "ElementHeader.h"

/***************************************************************************************************
* Scene function
*
* Placeholder.
***************************************************************************************************/
Scene::Scene( void ) {
	this->camera = new Actor();
	this->camera->addComponent( new Camera() );
	this->light = new Actor();
	this->light->addComponent( new Light() );
	this->cube = new Actor();
	this->cube->addComponent( new Transform() );
	this->cube->addComponent( new Mesh( "C:\\Users\\Ryan\\Game Tests\\CubeTest2.obj" ) );
}

/***************************************************************************************************
* ~Puzzle function
*
* Placeholder.
***************************************************************************************************/
Scene::~Scene( void ) {
	delete this->cube;
	delete this->light;
	delete this->camera;
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void Scene::update( void ) {
	this->cube->update();
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Scene::draw( void ) {
	this->cube->draw();
}