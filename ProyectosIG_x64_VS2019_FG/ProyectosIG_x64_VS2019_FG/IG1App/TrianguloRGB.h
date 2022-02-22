#pragma once
#include "Entity.h"

using namespace glm;

class TrianguloRGB : public Abs_Entity
{
	float r_;
	float radio = 200;
	int angulo = 0;
	float anguloActual = 0.0;
	float trasIncrease = 0.1;
	float triangleRot = 0.0;
	float rotIncrease = 0.1;
	Mesh* myMesh;

	dmat4 initMat;
	dmat4 camMat;
	dmat4 rot, tr;

	const int MAX_COUNT = 20;
	int count;

protected:
	

public:
	TrianguloRGB(float r);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;
};



