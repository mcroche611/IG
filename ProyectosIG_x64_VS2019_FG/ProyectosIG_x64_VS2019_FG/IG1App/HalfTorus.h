#pragma once
#include "EntityWithMaterial.h"
using namespace glm;

class XTorus : public EntityWithMaterial
{
protected:
	Mesh* mesh;
public:
	XTorus(GLdouble h, GLdouble r, GLuint n, GLdouble rHalfTorus, GLuint angTubo, GLfloat angRev);
	void render(dmat4 const& modelViewMat)const override;
	void update() override;

};