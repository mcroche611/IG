#include "Esfera.h"
#include "MbR.h"

#include "IndexMesh.h"
using namespace glm;

Esfera::Esfera(GLdouble h, GLdouble r, GLuint n) {
	// h=altura del cono, r=radio de la base
	// n=número de muestras, m=número de puntos del perfil
	dvec3* perfil = new dvec3[n];
	float ang = 0;
	for (int i = 0; i < n; i++) {
		perfil[i] = { r * cos(radians(ang)), r * (radians(ang)), 0.0 };
		//radio * cos(ang), radio * sen(ang)

		ang += 180 / n;
	}
	this->mesh = MbR::generaIndexMbR(32, n, perfil);
}

void Esfera::render(dmat4 const& modelViewMat) const
{

	if (this->mesh != nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		this->mesh->render();
	}
}

void Esfera::update()
{
}


