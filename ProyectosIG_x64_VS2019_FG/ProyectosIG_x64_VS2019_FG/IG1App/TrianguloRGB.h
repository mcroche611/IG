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
	double triangleRot = 1.0;
	double rotIncrease = 0.3;
	Mesh* myMesh;

protected:
	

public:
	TrianguloRGB(float r);
	void render(dmat4 const& modelViewMat)const override; 
	void update() override;
};



