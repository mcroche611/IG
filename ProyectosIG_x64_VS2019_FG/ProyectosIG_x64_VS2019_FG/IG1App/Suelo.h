#pragma once
#include "Entity.h"

using namespace glm;

class Suelo : public Abs_Entity
{
	GLdouble w_, h_;
	Mesh* myMesh;

public:
	Suelo(GLdouble w, GLdouble h);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;
};

