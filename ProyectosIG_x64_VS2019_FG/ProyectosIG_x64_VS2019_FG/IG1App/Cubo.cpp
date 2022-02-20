#include "Cubo.h"
#include "Mesh.h"

Cubo::Cubo(GLdouble longitud)
{
    l_ = longitud;

    myMesh = new Mesh();
    myMesh = Mesh::generaCubo(l_);

    glm::dvec4 color = { 0, 0, 0, 1.0 };
    setColor(color);
}

void Cubo::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glPolygonMode(GL_BACK, GL_LINE);
        glPolygonMode(GL_FRONT, GL_POINT);
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