#pragma once
#include "Entity.h"

class Cone : public Abs_Entity
{
protected:
	Mesh* mesh;
public:
	Cone(GLdouble h, GLdouble r, GLuint n);
};

