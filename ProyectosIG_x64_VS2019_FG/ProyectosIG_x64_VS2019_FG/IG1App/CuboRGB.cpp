#include "CuboRGB.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp> 

CuboRGB::CuboRGB(GLdouble longitud)
{
    l_ = longitud;
    
    myMesh = Mesh::generaCuboRGB(l_);

    dvec4 color = { 0, 0, 0, 1.0 };
    setColor(color);
}

void CuboRGB::update()
{
    setModelMat(rotate(modelMat(), radians(1.0), dvec3(1, 0, 0)));
}

void CuboRGB::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        //glPolygonMode(GL_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT, GL_FILL);
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        myMesh->render();
        glLineWidth(1);

        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    glColor3d(255, 255, 255);
}