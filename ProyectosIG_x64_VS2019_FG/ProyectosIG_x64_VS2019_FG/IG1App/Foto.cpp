#include "Foto.h"
#include "Mesh.h"

Foto::Foto(GLdouble w, GLdouble h)
{
    w_ = w;
    h_ = h;

    myMesh = new Mesh();
    //myMesh = Mesh::generaFoto(w_, h_);

    glm::dvec4 color = { 255, 255, 0, 1.0 };
    setColor(color);
}

void Foto::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        myMesh->render();
        glLineWidth(1);

        glPolygonMode(GL_FRONT, GL_FILL);
    }

    glColor3d(255, 255, 255);
}

void Foto::update()
{
}
