#include "Suelo.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <gtc/type_ptr.hpp>


Suelo::Suelo(GLdouble w, GLdouble h)
{
	myMesh = Mesh::generaRectanguloTexCor(w, h, 4, 4);

	setModelMat(rotate(mModelMat, radians(90.0), dvec3(1, 0, 0)));
}

void Suelo::render(dmat4 const& modelViewMat)const
{

	if (myMesh != nullptr) {  

		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		mTexture->bind(GL_MODULATE);
		myMesh->render();
		mTexture->unbind();
	}

}

void Suelo::update()
{
}
