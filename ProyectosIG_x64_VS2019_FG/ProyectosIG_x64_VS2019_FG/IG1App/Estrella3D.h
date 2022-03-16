#pragma once
#include "Entity.h"

using namespace glm;

class Estrella3D : public Abs_Entity
{
	GLdouble re_, np_, h_;
	Mesh* myMesh;

public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;
};





