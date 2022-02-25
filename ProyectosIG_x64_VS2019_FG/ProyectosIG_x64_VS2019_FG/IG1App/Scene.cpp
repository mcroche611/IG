#include "Scene.h"
#include "CheckML.h"
#include "Poligono.h"
#include "TrianguloRGB.h"
#include "RectanguloRGB.h"
#include "Cubo.h"
#include "CuboRGB.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	Texture* t = new Texture();
	t->load("..\\Bmps\\baldosaC.bmp");
	gTextures.push_back(t);

	// allocate memory and load resources
    // Lights
    // Textures

	if (mId == 0)
	{
		gObjects.push_back(new Ejes2D(400.0));

		Poligono* circle = new Poligono(360, 200);
		circle->setColor({ 255, 0, 255, 1.0 });
		gObjects.push_back(circle);

		TrianguloRGB* triangleRGB = new TrianguloRGB(100);
		gObjects.push_back(triangleRGB);

		triangleRGB->setModelMat(translate(triangleRGB->modelMat(), dvec3(circle->getR(), 0, 0)));

		RectanguloRGB* rectRGB = new RectanguloRGB(300, 200);
		gObjects.push_back(rectRGB);
	}
	else if (mId == 1)
	{
		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(400.0));

		CuboRGB* cubo = new CuboRGB(200);
		gObjects.push_back(cubo);
	}

}

//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}

	for (Texture* e : gTextures)
	{
		delete e;  e = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
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

void Scene::update()
{
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}

void Scene::setState(int id)
{
	if (mId != id)
	{
		free();

		//vaciar gObjects
		gObjects.clear();

		mId = id;

		init();
	}
}
//-------------------------------------------------------------------------


