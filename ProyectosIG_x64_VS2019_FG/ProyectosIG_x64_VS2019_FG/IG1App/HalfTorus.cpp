#include "HalfTorus.h"
#include "MbR.h"

#include "IndexMesh.h"
using namespace glm;

XTorus::XTorus(GLdouble n, GLdouble rPerfil, GLuint m, GLdouble rHalfTorus, GLuint angTubo, GLfloat angRev) {
	// r=radio de la HalfTorus
	// m=número de muestras, n=número de puntos del perfil
	dvec3* perfil = new dvec3[n + 1];
	float ang = 0;
	for (int i = 0; i < n + 1; i++) {
		perfil[i] = { rPerfil * cos(radians(ang)) + rHalfTorus, rPerfil * sin(radians(ang)) + rHalfTorus, 0.0 };
		//radio * cos(ang), radio * sen(ang)

		ang += angTubo / n;
	}
	this->mesh = MbR::generaIndexMbRCortado(n + 1, m, perfil, angRev);
}

void XTorus::render(dmat4 const& modelViewMat) const
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

void XTorus::update()
{
}


