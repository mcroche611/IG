#include "Torus.h"
#include "MbR.h"

#include "IndexMesh.h"
using namespace glm;

Torus::Torus(GLdouble n, GLdouble r, GLuint m, GLdouble rTorus) {
	// r=radio de la Torus
	// m=número de muestras, n=número de puntos del perfil
	dvec3* perfil = new dvec3[n + 1];
	float ang = 0;
	for (int i = 0; i < n + 1; i++) {
		perfil[i] = { r * cos(radians(ang)) + rTorus, r * sin(radians(ang)) + rTorus, 0.0 };
		//radio * cos(ang), radio * sen(ang)

		ang += 360/ n;
	}
	this->mesh = MbR::generaIndexMbR(n + 1, m, perfil);
}

void Torus::render(dmat4 const& modelViewMat) const
{
	if (this->mesh != nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);

		if (this->material != nullptr)
		{
			material->upload();
			this->mesh->render();
		}
		else
		{
			glEnable(GL_COLOR_MATERIAL);
			glColor3f(mColor.r, mColor.g, mColor.b);
			this->mesh->render();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_COLOR_MATERIAL);
		}
	}
}

void Torus::update()
{
}


