#include "AlaTieAvanzado.h"

AlaTieAvanzado::AlaTieAvanzado(GLdouble w, GLdouble h)
{
	alas = new Mesh();
	alas = Mesh::generaAla(w, h);
}

AlaTieAvanzado::~AlaTieAvanzado()
{
	delete alas;
}

void AlaTieAvanzado::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	alas->render();
}
