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
        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT); //culling a las frontales
        mTexture->setWrap(GL_REPEAT);
        mTexture->bind(GL_REPLACE);
        
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        //culling a las traseras
        myMesh->render();

        glCullFace(GL_BACK); 
        nTexture->setWrap(GL_REPEAT);
        nTexture->bind(GL_REPLACE);
        //se renderiza lo de fuera
        myMesh->render();

        glLineWidth(1);
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    glColor3d(255, 255, 255);
}

void ContornoCaja::update()
{
}
