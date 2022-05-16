#pragma once
#include "Entity.h"

using namespace glm;

class Hierba : public Abs_Entity
{
	GLdouble w_, h_;
	Mesh* myMesh;

public:
	Hierba(GLdouble w, GLdouble h);
	void render(dmat4 const& modelViewMat)const override; 
	void update() override;
};

