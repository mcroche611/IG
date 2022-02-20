#pragma once
#include "Entity.h"

using namespace glm;

class TrianguloRGB : public Abs_Entity
{
	float r_;
	Mesh* myMesh;

public:
	TrianguloRGB(float r);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
};



