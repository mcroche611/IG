#include "TieAvanzado.h"
#include "QuadricEntity.h"
#include <gtc/matrix_transform.hpp>  
#include "AlaTieAvanzado.h"

#define WIDTH_AXIS 300

TieAvanzado::TieAvanzado()
{
	addEntity(new EjesRGB(400.0));

	Sphere* esfera = new Sphere(WIDTH_AXIS / 4);
	esfera->setColor(mColor);
	addEntity(esfera);

	Cylinder* eje = new Cylinder(20.0, 20.0, WIDTH_AXIS);
	glm::dmat4 mAux = eje->modelMat();
	eje->setColor(mColor);
	mAux = translate(mAux, dvec3(WIDTH_AXIS / 2, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1.0, 0));
	eje->setModelMat(mAux);
	addEntity(eje);

	AlaTieAvanzado* ala1 = new AlaTieAvanzado(125, 300);
	mAux = ala1->modelMat();
	//ala1->setTexture(mTexture);
	mAux = translate(mAux, dvec3(WIDTH_AXIS / 3 - 10, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0, 0));
	ala1->setModelMat(mAux);
	addEntity(ala1);

	AlaTieAvanzado* ala2 = new AlaTieAvanzado(125, 300);
	mAux = ala2->modelMat();
	//ala2->setTexture(mTexture);
	mAux = translate(mAux, dvec3(-(WIDTH_AXIS / 3) + 10, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(1.0, 0.0, 0.0));
	mAux = rotate(mAux, radians(180.0), dvec3(0.0, 1.0, 0.0));
	ala2->setModelMat(mAux);
	addEntity(ala2);
}
