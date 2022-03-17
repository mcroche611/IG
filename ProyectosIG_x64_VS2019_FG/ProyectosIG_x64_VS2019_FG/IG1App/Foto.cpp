#include "Foto.h"
#include "Mesh.h"
#include <ext/matrix_transform.hpp>


Foto::Foto(GLdouble w, GLdouble h)
{
    w_ = w;
    h_ = h;

    myMesh = new Mesh();
    myMesh = Mesh::generaRectanguloTexCorSinBaldosas(w_, h_);
    setModelMat(rotate(mModelMat, radians(90.0), dvec3(1, 0, 0)));
}

void Foto::render(dmat4 const& modelViewMat)const
{

	if (myMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		mTexture->bind(GL_MODULATE);
		myMesh->render();
		mTexture->unbind();
	}

}

void Foto::update()
{
    mTexture->loadColorBuffer(w_, h_);
}
