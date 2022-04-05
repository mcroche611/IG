#include "Cristalera.h"
#include "Mesh.h"

Cristalera::Cristalera(GLdouble longitud)
{
    l_ = longitud;

    myMesh = new Mesh();
    myMesh = Mesh::generaContCajaTexCor(l_);


}

void Cristalera::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mTexture->setWrap(GL_REPEAT);
        mTexture->bind(GL_MODULATE);

        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        //culling a las traseras
        myMesh->render();

        //se renderiza lo de fuera


        glLineWidth(1);
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    glColor3d(255, 255, 255);
}

void Cristalera::update()
{
}
