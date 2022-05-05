#pragma once
#include "EntityWithMaterial.h"
using namespace glm;

class Esfera : public EntityWithMaterial
{
protected:
	Mesh* mesh;
public:
	Esfera(GLdouble h, GLdouble r, GLuint n);
	void render(dmat4 const& modelViewMat)const override;
	void update() override;

};