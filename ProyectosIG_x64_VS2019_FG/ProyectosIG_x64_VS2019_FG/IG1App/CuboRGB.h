#pragma once
#include "Entity.h"
#include <vector>

using namespace std;
using namespace glm;

class CuboRGB : public Abs_Entity
{
	GLdouble l_;
    Mesh* myMesh;

public:
	CuboRGB(GLdouble longitud);
	void render(dmat4 const& modelViewMat)const override; //No necesita 'override' pq el render de Abs_Entity es virtual
	void update() override;
};





