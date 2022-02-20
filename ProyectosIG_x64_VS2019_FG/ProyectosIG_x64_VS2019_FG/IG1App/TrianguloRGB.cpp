#include "TrianguloRGB.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp> 
#include <iostream>

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

void TrianguloRGB::update()
{
    setModelMat(rotate(modelMat(), radians(1.0), dvec3(0,0,1)));

    //float x = cos(radians((float)angulo)) - 1;
    //float y = sin(radians((float)angulo));
    //std::cout << "x=" << x << " y= " << y << std::endl;
    //setModelMat(translate(modelMat(), dvec3(x, y, 0.0)));

    //angulo = (angulo + 1) % 360;
}
