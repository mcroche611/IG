#include "TieAvanzado.h"
#include "QuadricEntity.h"
#include <gtc/matrix_transform.hpp>  

#define WIDTH_AXIS 300

TieAvanzado::TieAvanzado()
{
	addEntity(new EjesRGB(400.0));

	Sphere* esfera = new Sphere(WIDTH_AXIS / 3);
	esfera->setColor(mColor);
	addEntity(esfera);

	Cylinder* eje = new Cylinder(20.0, 20.0, WIDTH_AXIS);
	glm::dmat4 mAux = eje->modelMat();
	eje->setColor(mColor);
	mAux = translate(mAux, dvec3(WIDTH_AXIS / 2, 0, 0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1.0, 0));
	eje->setModelMat(mAux);
	addEntity(eje);
}
