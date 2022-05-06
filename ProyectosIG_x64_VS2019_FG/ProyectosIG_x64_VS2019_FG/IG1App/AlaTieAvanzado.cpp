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

	glColor3d(mColor.r, mColor.g, mColor.b);

	if (alas != nullptr)
	{

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_MODULATE);
		alas->render();
		mTexture->unbind();

	}

	glColor3d(255, 255, 255);
}
