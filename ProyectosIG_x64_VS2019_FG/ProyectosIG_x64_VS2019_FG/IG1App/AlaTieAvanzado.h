#pragma once
#include "Entity.h"
using namespace glm;
class AlaTieAvanzado : public Abs_Entity
{
public: 
	AlaTieAvanzado(GLdouble w, GLdouble h);
	~AlaTieAvanzado();
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	Mesh* alas;
};

