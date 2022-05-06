#pragma once
#include "EntityWithMaterial.h"
using namespace glm;

class Torus : public EntityWithMaterial
{
protected:
	Mesh* mesh;
public:
	Torus(GLdouble h, GLdouble r, GLuint n, GLdouble rTorus);
	void render(dmat4 const& modelViewMat)const override;
	void update() override;

};