#include "TrianguloRGB.h"
#include "Mesh.h"

TrianguloRGB::TrianguloRGB(float r)
{
    r_ = r;
    myMesh = new Mesh();
    myMesh = Mesh::createTriangleRGB(r);

    glm::dvec4 color = { 255, 255, 0, 1.0 };
    setColor(color);
}

void TrianguloRGB::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glPolygonMode(GL_BACK, GL_LINE);
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        myMesh->render();
        glLineWidth(1);

        glPolygonMode(GL_BACK, GL_FILL);
    }

    glColor3d(255, 255, 255);
}