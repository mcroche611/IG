#include "Suelo.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <gtc/type_ptr.hpp>


Suelo::Suelo(GLdouble w, GLdouble h)
{
	myMesh = Mesh::generaRectanguloTexCor(w, h, 2, 2);

	setModelMat(rotate(mModelMat, radians(90.0), dvec3(1, 0, 0)));
}

void Suelo::render(dmat4 const& modelViewMat)const
{
	glColor3d(mColor.r, mColor.g, mColor.b);

	if (myMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		mTexture->bind(GL_MODULATE);
		myMesh->render();
		mTexture->unbind();
		glColor4d(1, 1, 1, 1);
	}

    glColor3d(255, 255, 255);
}

void Suelo::update()
{
}
