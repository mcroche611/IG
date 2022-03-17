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
}

void Estrella3D::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glColor4dv(value_ptr(mColor));
        mTexture->bind(GL_MODULATE);
        myMesh->render();
        mTexture->unbind();
        aMat = aMat * rotate(modelMat(), radians(180.0), dvec3(0, 1, 0));
        upload(aMat);
        glColor4dv(value_ptr(mColor));
        mTexture->bind(GL_MODULATE);
        myMesh->render();
        mTexture->unbind();
        glColor4d(1, 1, 1, 1);
    }

    glColor3d(255, 255, 255);
}

void Estrella3D::update()
{
}
