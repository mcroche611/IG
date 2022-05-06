#include "Scene.h"
#include "CheckML.h"
#include "Poligono.h"
#include "TrianguloRGB.h"
#include "RectanguloRGB.h"
#include "Cubo.h"
#include "CuboRGB.h"
#include "Suelo.h"
#include "ContornoCaja.h"
#include "Cristalera.h"
#include "Foto.h"
#include "Estrella3D.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"
#include "CompoundEntity.h"
#include "TieAvanzado.h"
#include "CuboIndexado.h"
#include "MbR.h"
#include "Esfera.h"
#include "Material.h"
#include "Light.h"
using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
	Texture* baldosaC = new Texture();
	baldosaC->load("..\\Bmps\\baldosaC.bmp");
	gTextures.push_back(baldosaC);

	Texture* baldosaP = new Texture();
	baldosaP->load("..\\Bmps\\baldosaP.bmp");
	gTextures.push_back(baldosaP);

	Texture* container = new Texture();
	container->load("..\\Bmps\\container.bmp");
	gTextures.push_back(container);

	Texture* papelE = new Texture();
	papelE->load("..\\Bmps\\papelE.bmp");
	gTextures.push_back(papelE);

	Texture* windowV = new Texture();
	windowV->load("..\\Bmps\\windowV.bmp", 100);
	gTextures.push_back(windowV);

	Texture* fotoTex = new Texture();
	fotoTex->loadColorBuffer(800, 600);
	gTextures.push_back(fotoTex);

    // Lights
	glEnable(GL_COLOR_MATERIAL);

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
	else if (mId == 2)
	{
		gObjects.push_back(new EjesRGB(400.0));

		Suelo* suelo = new Suelo(500, 500);
		suelo->setTexture(baldosaC);
		suelo->setModelMat(translate(suelo->modelMat(), dvec3(0, 0, 20)));
		gObjects.push_back(suelo);
		
		ContornoCaja* caja = new ContornoCaja(100);
		caja->setTexture(container);
		caja->setTexture2(papelE);
		caja->setModelMat(translate(caja->modelMat(), dvec3(195, 30, 195)));
		gObjects.push_back(caja);


		Estrella3D* estrella = new Estrella3D(50, 8, 40);
		estrella->setTexture(baldosaP);
		gObjects.push_back(estrella);

		Foto* foto = new Foto(200, 100);
		foto->setTexture(fotoTex);
		gObjects.push_back(foto);

		Cristalera* cristalera = new Cristalera(500);
		cristalera->setTexture(windowV);
		cristalera->setModelMat(translate(cristalera->modelMat(), dvec3(0, 230, 0)));
		tObjects.push_back(cristalera);
		
	}
	else if (mId == 3)
	{
		nodoFicticio = new CompoundEntity();
		tr = new TrianguloRGB(100);
		nodoFicticio->addEntity(tr);

		
		gObjects.push_back(nodoFicticio);
		tr->setModelMat(translate(nodoFicticio->modelMat(),
			dvec3(200, 0, 0)));
	}
	else if (mId == 4)
	{
		nodoFicticio = new CompoundEntity();
		TieAvanzado* tie = new TieAvanzado();
		nodoFicticio->addEntity(tie);
		gObjects.push_back(nodoFicticio);
	}
	else if (mId == 5)
	{
		nodoFicticio = new CompoundEntity();
		TieAvanzado* tie = new TieAvanzado();
		nodoFicticio->addEntity(tie);
		tie->setModelMat(translate(tie->modelMat(), dvec3(0, 500, 0)));
		gObjects.push_back(nodoFicticio);

		dvec4 c = { 250.0, 200.0, 0.0, 1.0 };
		Sphere* esfera = new Sphere(400.0);
		esfera->setColor(c);
		gObjects.push_back(esfera);

	}
	else if (mId == 6)
	{
		CuboIndexado* cuboIndex = new CuboIndexado(100);
		gObjects.push_back(cuboIndex);
	}
	else if (mId == 7)
	{
		Esfera* esfera = new Esfera(500, 100, 100);
		Material* m = new Material();
		//m->setCopper();
		//esfera->setMaterial(m);
		gObjects.push_back(esfera);

		//Sphere* esfera = new Sphere(400.0);
		//Material* m = new Material();
		//m->setCopper();
		//esfera->setMaterial(m);
		//gObjects.push_back(esfera);
	}
}

//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();

	//if (mId == 2)
	{
		for (Abs_Entity* elem : tObjects)
		{


			delete elem;  elem = nullptr;

		}
		tObjects.clear();

		for (Texture* e : gTextures)
		{


			delete e;  e = nullptr;

		}
		gTextures.clear();


	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	if (mId!= 5)
		glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	else
		glClearColor(0.0, 0.0, 0.0, 1.0); //fondo negro

	// Se activa el test de profundidad
	glEnable(GL_DEPTH_TEST);
	// Se activan las texturas, por si las hay
	glEnable(GL_TEXTURE_2D);
	// Se activa la iluminación
	glEnable(GL_LIGHTING);
	// Se activa la normalización de los vectores normales
	glEnable(GL_NORMALIZE);
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
	//glColorMaterial(GL_FRONT, GL_AMBIENT);
	//glEnable(GL_COLOR_MATERIAL);
	sceneDirLight(cam);
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//if (mId == 2)
	{
		for (Abs_Entity* el : tObjects)
		{
			el->render(cam.viewMat());
		}
	}
	glDepthMask(GLU_TRUE);
	glDisable(GL_BLEND);

	
}

void Scene::update()
{
	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}

	if (mId == 2)
	{
		for (Abs_Entity* el : tObjects)
		{
			el->update();
		}
	}
	if (mId == 4)
	{
		if (nodoFicticio)
		{
			glm::dmat4 mAux = nodoFicticio->modelMat();
			mAux = rotate(mAux, radians(3.0), dvec3(0.0, 0.0, 1.0));
			nodoFicticio->setModelMat(mAux);
		}

	}
	else if (mId==3)
	{
		nodoFicticio->setModelMat(rotate(nodoFicticio->modelMat(), radians(3.0), dvec3(0, 0, 1)));
	}

}

void Scene::orbit()
{
	if (nodoFicticio)
	{
		glm::dmat4 mAux = nodoFicticio->modelMat();
		mAux = rotate(mAux, radians(3.0), dvec3(1.0, 0.0, 0.0));
		nodoFicticio->setModelMat(mAux);
	}

}
void Scene::rotation()
{
	if (nodoFicticio)
	{
		glm::dmat4 mAux = nodoFicticio->modelMat();
		mAux = rotate(mAux, radians(3.0), dvec3(0.0, 1.0, 0.0));
		nodoFicticio->setModelMat(mAux);
	}

}
void Scene::setState(int id)
{
	if (mId != id)
	{
		free();

		//vaciar gObjects
		gObjects.clear();
		tObjects.clear();

		mId = id;

		init();
	}
}

int Scene::getState()
{
	return mId;
}

void Scene::sceneDirLight(Camera const& cam) const 
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}

//-------------------------------------------------------------------------


