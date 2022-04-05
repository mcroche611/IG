#pragma once
#include "Entity.h"

using namespace glm;

class ContornoCaja : public Abs_Entity
{
	GLdouble l_;
	Mesh* myMesh;
	Texture* nTexture = nullptr; //the second
public:
	ContornoCaja(GLdouble longitud);
	void render(dmat4 const& modelViewMat)const override; 
	void update() override;
	void setTexture2(Texture* tex) { nTexture = tex; };



};






