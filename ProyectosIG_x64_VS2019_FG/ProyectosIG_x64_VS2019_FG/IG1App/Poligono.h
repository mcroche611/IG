#pragma once
#include "Entity.h"

using namespace glm;

class Poligono : public Abs_Entity
{
	float num_, r_;
	Mesh* myMesh;

public:
	Poligono(float num, float r);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
};

