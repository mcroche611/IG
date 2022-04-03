#pragma once
#include "Entity.h"

using namespace glm;

class Estrella3D : public Abs_Entity
{
	GLdouble re_, np_, h_;
	Mesh* myMesh;

	float anguloActual = 0.0;
	float trasIncrease = 0.1;
	double estrellaRot = 1.0;
	double rotIncrease = 0.1;

	double angulo = 0.0;

public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;
};





