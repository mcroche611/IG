#include "Estrella3D.h"
#include "Mesh.h"

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
    re_ = re;
    np_ = np;
    h_ = h;

    myMesh = new Mesh();
    myMesh = Mesh::generaEstrella3D(re_, np_, h_);
}

void Estrella3D::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        myMesh->render();
        glLineWidth(1);

        glPolygonMode(GL_FRONT, GL_FILL);
    }

    glColor3d(255, 255, 255);
}

void Estrella3D::update()
{
}
