#include "TrianguloRGB.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp> 
#include <iostream>

TrianguloRGB::TrianguloRGB(float r)
{
    r_ = r;
    myMesh = new Mesh();
    myMesh = Mesh::createTriangleRGB(r);

    initMat = modelMat();
    camMat = modelMat();

    glm::dvec4 color = { 255, 255, 0, 1.0 };
    setColor(color);

    count = MAX_COUNT;
}

void TrianguloRGB::render(dmat4 const& modelViewMat)const
{
    glColor3d(mColor.r, mColor.g, mColor.b);

    if (myMesh != nullptr)
    {
        glPolygonMode(GL_BACK, GL_LINE);
        dmat4 aMat = modelViewMat * mModelMat /** rot * tr*/;
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
    //rot = rotate(modelMat(), radians(5.0), dvec3(0, 0, 1));

    //tr = translate(modelMat(), dvec3(cos(radians((float)angulo)), sin(radians((float)angulo)), 0.0));

    //setModelMat(mModelMat * rot * tr);


    ////setModelMat(translate(modelMat(), dvec3(-radio, 0, 0.0)));

    //setModelMat(rotate(modelMat(), radians(5.0), dvec3(0, 0, 1)));

    anguloActual += trasIncrease;
    mModelMat = translate(dmat4(1.0), dvec3(cos(radians(anguloActual)) * radio, sin(radians(anguloActual)) * radio, 0));

    triangleRot -= rotIncrease;
    mModelMat = rotate(mModelMat, radians(triangleRot + 0.1), dvec3(0, 0, 1));

    //setModelMat(translate(modelMat(), dvec3(radio, 0, 0.0)));

    //if (count == 0)
    //{
    //    setModelMat(rotate(modelMat(), radians(10.0), dvec3(0, 0, 1)));

    //    count = MAX_COUNT;
    //}
    //else
    //{
    //    setModelMat(translate(modelMat(), dvec3(-radio * cos(radians(5.0)), -1 * sin(radians(5.0)), 0.0)));

    //    setModelMat(rotate(modelMat(), radians(1.0), dvec3(0, 0, 1)));

    //    setModelMat(translate(modelMat(), dvec3(radio * cos(radians(5.0)), 1 * sin(radians(5.0)), 0.0)));

    //angulo++;

    //    count--;
    //}
        
    

    /*setModelMat(translate(modelMat(), dvec3(30 * cos(radians((float)angulo)) - radio, sin(radians((float)angulo)), 0.0)));*/

    //setModelMat(translate(modelMat(), dvec3(radio, 0, 0.0)));

    
}
