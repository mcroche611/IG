#include "Esfera.h"
#include "MbR.h"

#include "IndexMesh.h"
using namespace glm;

Esfera::Esfera(GLdouble n, GLdouble r, GLuint m) {
	// r=radio de la esfera
	// m=n�mero de muestras, n=n�mero de puntos del perfil
	dvec3* perfil = new dvec3[n + 1];
	float ang = 270;
	for (int i = 0; i < n + 1 && ang >= 0; i++) {
		perfil[i] = { r * cos(radians(ang)), r * sin(radians(ang)), 0.0 };
		//radio * cos(ang), radio * sen(ang)

		ang -= 180/ n;
	}
	this->mesh = MbR::generaIndexMbR(n + 1, m, perfil);
}

void Esfera::render(dmat4 const& modelViewMat) const
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

void Esfera::update()
{
}


