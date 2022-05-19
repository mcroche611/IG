#include "Bolido.h"
#include "QuadricEntity.h"
#include <gtc/matrix_transform.hpp>  
#include "Light.h"

#define WIDTH_AXIS 300

Bolido::Bolido()
{
	Texture* night = new Texture();
	night->load("..\\Bmps\\noche.bmp", 160);

	Sphere* esfera = new Sphere(200);
	esfera->setColor({ 255, 0, 0, 1 });
	addEntity(esfera);

	MyCone* cono = new MyCone(100.0f, 150.0f);
	glm::dmat4 mAux = cono->modelMat();
	mAux = translate(mAux, dvec3(0, 0, -175));
	mAux = rotate(mAux, radians(-180.0), dvec3(0, 1, 0));
	cono->setColor({ 0, 0, 255, 1 });
	cono->setModelMat(mAux);
	addEntity(cono);

	Disk* alas = new Disk(200, 250);
	alas->setModelMat(rotate(alas->modelMat(), radians(90.0), dvec3(1, 0, 0)));
	alas->setColor({ 0, 255, 0, 1});
	addEntity(alas);


	spotLight = new SpotLight();
	//glEnable(GL_LIGHT3);
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	spotLight->setAmb(ambient);
	spotLight->setDiff(diffuse);
	spotLight->setSpec(specular);
	spotLight->setSpot(glm::fvec3(0,-1,0),90,0); 
	spotLight->setPosDir(glm::fvec3(0,490,0));
}
