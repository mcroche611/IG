#include "ContornoCaja.h"
#include "Mesh.h"

ContornoCaja::ContornoCaja(GLdouble longitud)
{
    l_ = longitud;

    myMesh = new Mesh();
    myMesh = Mesh::generaContCajaTexCor(l_);

   
}

void ContornoCaja::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glPolygonMode(GL_BACK, GL_LINE);

        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        mTexture->setWrap(GL_REPEAT);
        mTexture->bind(GL_MODULATE);

        myMesh->render();
        glLineWidth(1);

        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    glColor3d(255, 255, 255);
}

void ContornoCaja::update()
{
}
