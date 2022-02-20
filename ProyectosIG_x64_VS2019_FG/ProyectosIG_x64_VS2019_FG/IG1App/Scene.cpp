#include "Scene.h"
#include "CheckML.h"
#include "Poligono.h"
#include "Triangle.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(new Poligono(5, 200));
	Poligono* triangle= new Poligono(3, 200);
	triangle->setColor({ 0, 255, 255, 1.0 });
	gObjects.push_back(triangle);
	Poligono* circle = new Poligono(360, 200);
	circle->setColor({ 255, 0, 255, 1.0 });
	gObjects.push_back(circle);
	Triangle* triangleRGB = new Triangle(100);
	gObjects.push_back(triangleRGB);
}

//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------


