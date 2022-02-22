#include "Poligono.h"
#include "Mesh.h"

Poligono::Poligono(float num, float r)
{
    num_ = num;
    r_ = r;
    myMesh = new Mesh();
    myMesh = Mesh::generaPoligonoRegular(num, r);

    glm::dvec4 color = { 255, 255, 0, 1.0 };
    setColor(color);
}

void Poligono::render(dmat4 const& modelViewMat)const
{
	glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        myMesh->render();
        glLineWidth(1);
    }

    glColor3d(255, 255, 255);
}

void Poligono::update()
{
}
