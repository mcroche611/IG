#include "Hierba.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <gtc/type_ptr.hpp>


Hierba::Hierba(GLdouble w, GLdouble h)
{
	myMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);

	setModelMat(rotate(mModelMat, radians(90.0), dvec3(1, 0, 0)));
}

void Hierba::render(dmat4 const& modelViewMat)const
{

	if (myMesh != nullptr) {  

		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		mTexture->bind(GL_MODULATE);
		myMesh->render();
		aMat = aMat * rotate(dmat4(1.0), radians(120.0), dvec3(0, 1, 0));
		upload(aMat);
		myMesh->render();
		aMat = aMat * rotate(dmat4(1.0), radians(120.0), dvec3(0, 1, 0));
		upload(aMat);
		myMesh->render();
		mTexture->unbind();
	}

}

void Hierba::update()
{
}
