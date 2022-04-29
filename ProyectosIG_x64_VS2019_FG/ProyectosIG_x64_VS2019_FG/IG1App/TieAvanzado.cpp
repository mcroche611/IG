#include "TieAvanzado.h"
#include "QuadricEntity.h"
#include <gtc/matrix_transform.hpp>  
#include "AlaTieAvanzado.h"

#define WIDTH_AXIS 300

TieAvanzado::TieAvanzado()
{
	Texture* night = new Texture();
	night->load("..\\Bmps\\noche.bmp", 160);


	Sphere* esfera = new Sphere(WIDTH_AXIS / 4);
	esfera->setColor(miColor);
	addEntity(esfera);

	Cylinder* eje = new Cylinder(20.0, 20.0, WIDTH_AXIS);
	glm::dmat4 mAux = eje->modelMat();
	eje->setColor(miColor);
	mAux = translate(mAux, dvec3(WIDTH_AXIS / 2, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1.0, 0));
	eje->setModelMat(mAux);
	addEntity(eje);


	Cylinder* cabina = new Cylinder(50.0, 50.0, 20);
	mAux = cabina->modelMat();
	cabina->setColor(miColor);
	mAux = translate(mAux, dvec3(0, 0, WIDTH_AXIS / 5));
	cabina->setModelMat(mAux);
	addEntity(cabina);
	
	AlaTieAvanzado* ala1 = new AlaTieAvanzado(125, 300);
	mAux = ala1->modelMat();
	//ala1->setColor({ 255, 255, 255, 0.5 });
	ala1->setTexture(night);
	mAux = translate(mAux, dvec3(WIDTH_AXIS / 3 - 10, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
	ala1->setModelMat(mAux);
	addTranslucidEntity(ala1);

	AlaTieAvanzado* ala2 = new AlaTieAvanzado(125, 300);
	mAux = ala2->modelMat();
	//ala2->setColor({ 255.0, 255.0, 255.0, 0.8 });
	ala2->setTexture(night);
	mAux = translate(mAux, dvec3(-(WIDTH_AXIS / 3) + 10, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0.0, 0.0));
	mAux = rotate(mAux, radians(180.0), dvec3(0.0, 1.0, 0.0));
	ala2->setModelMat(mAux);
	addTranslucidEntity(ala2);

	
}
