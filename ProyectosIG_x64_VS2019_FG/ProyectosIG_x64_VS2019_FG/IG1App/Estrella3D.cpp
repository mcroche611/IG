#include "Estrella3D.h"
#include "Mesh.h"
#include <ext/matrix_transform.hpp>
#include <iostream>
#include <gtc/type_ptr.hpp>

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
    re_ = re;
    np_ = np;
    h_ = h;

    myMesh = new Mesh();
    myMesh = Mesh::generaEstrella3DTexCor(re_, np_, h_);
    setModelMat(translate(dmat4(1.0), dvec3(195, 150, 195)));
}

void Estrella3D::render(dmat4 const& modelViewMat)const
{
    if (myMesh != nullptr)
    {
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        mTexture->bind(GL_MODULATE);
        myMesh->render();
        mTexture->unbind();
        aMat = aMat * rotate(modelMat(), radians(180.0), dvec3(0, 1, 0));
        upload(aMat);
        mTexture->bind(GL_MODULATE);
        myMesh->render();
        mTexture->unbind();
    }

}

void Estrella3D::update()
{
    //setModelMat(rotate(mModelMat, radians(0.5), dvec3(0, 1, 0)));
    //setModelMat(rotate(mModelMat, radians(0.5), dvec3(0, 0, 1)));

    //mModelMat = rotate(mModelMat, radians(0.5), dvec3(0, 1, 0));

    //mModelMat = rotate(mModelMat, radians(0.5), dvec3(0, 0, 1));
}
