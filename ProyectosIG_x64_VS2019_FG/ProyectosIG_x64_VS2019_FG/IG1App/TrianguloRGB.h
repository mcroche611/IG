#pragma once
#include "Entity.h"

using namespace glm;

class TrianguloRGB : public Abs_Entity
{
	float r_;
	float radio = 200;
	int angulo = 0;
	Mesh* myMesh;

public:
	TrianguloRGB(float r);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;
};



