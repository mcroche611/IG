#include "Esfera.h"
#include "MbR.h"
#include "IndexMesh.h"
#include <gtc/type_ptr.hpp>
using namespace glm;

Esfera::Esfera(GLdouble n, GLdouble r, GLuint m) {
	// r=radio de la esfera
	// m=n?mero de muestras, n=n?mero de puntos del perfil
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

		if (this->material != nullptr)
		{
			material->upload();
		}
		else
		{
			glEnable(GL_COLOR_MATERIAL);
			//glm::dvec3 color = glm::dvec3(0,1,0);
			glColor4dv(value_ptr(this->mColor));
		}
		upload(aMat);

		this->mesh->render();
		glDisable(GL_COLOR_MATERIAL);
	}
}

void Esfera::update()
{
}


