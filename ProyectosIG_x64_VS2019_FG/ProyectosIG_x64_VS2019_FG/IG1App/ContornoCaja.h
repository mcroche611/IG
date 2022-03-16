#pragma once
#include "Entity.h"

using namespace glm;

class ContornoCaja : public Abs_Entity
{
	GLdouble l_;
	Mesh* myMesh;

public:
	ContornoCaja(GLdouble longitud);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;

};






