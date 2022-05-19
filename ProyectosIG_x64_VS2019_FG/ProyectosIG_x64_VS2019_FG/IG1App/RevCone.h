#pragma once
#include "Entity.h"

class RevCone : public Abs_Entity
{
protected:
	Mesh* mesh;
public:
	RevCone(GLdouble h, GLdouble r, GLuint n);
};

