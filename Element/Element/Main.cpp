/***************************************************************************************************
* Main.cpp
*
* Placeholder.
***************************************************************************************************/

#include "ElementHeader.h"

/***************************************************************************************************
* main function
*
* Placeholder.
***************************************************************************************************/
int main( int argc, char* argv[] ) {	
	Global::system = new System();
	Global::system->init();
	Global::system->run();
	delete Global::system;
}