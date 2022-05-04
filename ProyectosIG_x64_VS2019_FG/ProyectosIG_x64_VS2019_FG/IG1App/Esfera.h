#pragma once
#include "Entity.h"
using namespace glm;

class Esfera : public Abs_Entity
{
protected:
	Mesh* mesh;
public:
	Esfera(GLdouble h, GLdouble r, GLuint n);
	void render(dmat4 const& modelViewMat)const override;
	void update() override;

};