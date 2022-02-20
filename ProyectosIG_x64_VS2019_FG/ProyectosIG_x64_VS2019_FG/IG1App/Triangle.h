#pragma once
#include "Entity.h"

using namespace glm;

class Triangle : public Abs_Entity
{
	float r_;
	Mesh* myMesh;

public:
	Triangle(float r);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
};



