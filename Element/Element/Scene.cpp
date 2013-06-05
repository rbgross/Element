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
	this->camera->addComponent( "transform", new Transform() );
	this->camera->addComponent( "camera", new Camera() );
	this->light = new Actor();
	this->light->addComponent( "transform", new Transform() );
	this->light->addComponent( "light", new Light() );
	this->cube = new Actor();
	this->cube->addComponent( "transform", new Transform() );
	this->cube->addComponent( "mesh", new Mesh( "C:\\Users\\Ryan\\Game Tests\\CubeTest2.obj" ) );

	this->camera->setup();
	this->light->setup();
	this->cube->setup();
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