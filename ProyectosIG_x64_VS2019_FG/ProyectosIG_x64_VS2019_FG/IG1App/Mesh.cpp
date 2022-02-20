#define _USE_MATH_DEFINES

#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
#include <cmath>
using namespace std;
using namespace glm;



//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble w2 = w / 2, h2 = h / 2;

    mesh->vVertices.emplace_back(w2, h2, 0.0);
    mesh->vVertices.emplace_back(-w2, h2, 0.0);
    mesh->vVertices.emplace_back(w2, -h2, 0.0);
    mesh->vVertices.emplace_back(-w2, -h2, 0.0);


    return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vColors.reserve(mesh->mNumVertices);
    // Red
    mesh->vColors.emplace_back(255, 0, 0, 1.0);
    // Green  (Alpha = 1 : fully opaque)
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Green
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Blue
    mesh->vColors.emplace_back(0, 0, 255, 1.0);

    return mesh;
}

//static const GLfloat cube_strip[] = { +0.5, +0.5, -0.5, // Back-top-right
//                                    -0.5, +0.5, -0.5, // Back-top-left
//                                    +0.5, -0.5, -0.5, // Back-bottom-right
//                                    -0.5, -0.5, -0.5, // Back-bottom-left
//                                    -0.5, -0.5, +0.5, // Front-bottom-left
//                                    -0.5, +0.5, -0.5, // Back-top-left
//                                    -0.5, +0.5, +0.5, // Front-top-left
//                                    +0.5, +0.5, -0.5, // Back-top-right
//                                    +0.5, +0.5, +0.5, // Front-top-right
//                                    +0.5, -0.5, -0.5, // Back-bottom-right
//                                    +0.5, -0.5, +0.5, // Front-bottom-right
//                                    -0.5, -0.5, +0.5, // Front-bottom-left
//                                    +0.5, +0.5, +0.5, // Front-top-right
//                                    -0.5, +0.5, +0.5, // Front-top-left
//                                    };

static const GLfloat cube_strip[] = { +0.5, +0.5, -0.5, // Back-top-right Red
                                    -0.5, +0.5, -0.5, // Back-top-left Red
                                    +0.5, -0.5, -0.5, // Back-bottom-right Red
                                    -0.5, -0.5, -0.5, // Back-bottom-left Red
                                    -0.5, -0.5, -0.5, // Back-bottom-left Green*
                                    -0.5, -0.5, +0.5, // Front-bottom-left Green
                                    -0.5, +0.5, -0.5, // Back-top-left Green
                                    -0.5, +0.5, +0.5, // Front-top-left Green
                                    -0.5, +0.5, +0.5, // Front-top-left Blue*
                                    +0.5, +0.5, +0.5, // Front-top-right Blue2
                                    -0.5, +0.5, -0.5, // Back-top-left Blue2
                                    +0.5, +0.5, -0.5, // Back-top-right Blue
                                    +0.5, +0.5, -0.5, // Back-top-right Green2
                                    +0.5, +0.5, +0.5, // Front-top-right Green*
                                    +0.5, -0.5, -0.5, // Back-bottom-right Green
                                    +0.5, -0.5, +0.5, // Front-bottom-right Green
                                    +0.5, -0.5, +0.5, // Front-bottom-right Red*
                                    +0.5, +0.5, +0.5, // Front-top-right Red2
                                    -0.5, -0.5, +0.5, // Front-bottom-left Red
                                    -0.5, +0.5, +0.5, // Front-top-left Red
                                    +0.5, -0.5, +0.5, // Front-bottom-right Red2
                                    +0.5, -0.5, +0.5, // Front-bottom-right Blue2
                                    -0.5, -0.5, +0.5, // Front-bottom-left Blue2
                                    +0.5, -0.5, -0.5, // Back-bottom-right Blue2
                                    -0.5, -0.5, -0.5 // Back-bottom-left Blue2  
};

static const GLfloat cube_colors[] = { 255, 0, 0, // Back-top-right Red
                                       255, 0, 0, // Back-top-left Red
                                    255, 0, 0, // // Back-bottom-right Red
                                    255, 0, 0, // // Back-bottom-left Red
                                    0, 255, 0, // // Back-bottom-left Green
                                    0, 255, 0, // // Front-bottom-left Green
                                    0, 255, 0, // // Back-top-left Green
                                    0, 255, 0, // // Front-top-left Green
                                    0, 0, 255, // // Front-top-left Blue*
                                    0, 0, 255, // // Front-top-right Blue2
                                    0, 0, 255, // // Back-top-left Blue2
                                    0, 0, 255, // // Back-top-right Blue
                                    0, 255, 0, // // Back-top-right Green2
                                    0, 255, 0, // // Front-top-right Green*
                                    0, 255, 0, // // Back-bottom-right Green
                                    0, 255, 0, // // Front-bottom-right Green
                                    255, 0, 0, // // Front-bottom-right Red*
                                    255, 0, 0, // // Front-top-right Red2
                                    255, 0, 0, // // Front-bottom-left Red
                                    255, 0, 0, // // Front-top-left Red
                                    255, 0, 0, // // Front-bottom-right Red2
                                    0, 0, 255, // // Front-bottom-right Blue2
                                    0, 0, 255, // // Front-bottom-left Blue2
                                    0, 0, 255, // // Back-bottom-right Blue2
                                    0, 0, 255 // // Back-bottom-left Blue2  
};

static const GLfloat cube_vertices[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static const GLfloat color_vertices[] = {
    255,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};


//static const GLfloat cube_colors[] = { 0, 0, 255, // Back-top-right
//                                       0, 0, 255, // Back-top-left
//                                    0, 255, 0, // Back-bottom-right
//                                    255, 0, 0, // Back-bottom-left
//                                    255, 0, 0, // Front-bottom-left
//                                    0, 0, 255, // Back-top-left
//                                    0, 0, 255, // Front-top-left
//                                    0, 255, 0, // Back-top-right
//                                    0, 0, 255, // Front-top-right
//                                    0, 255, 0, // Back-bottom-right
//                                    255, 0, 0, // Front-bottom-right
//                                    255, 0, 0, // Front-bottom-left
//                                    255, 0, 0, // Front-top-right
//                                    255, 0, 0, // Front-top-left
//};

//static const GLfloat cube_colors[] = { 255, 0, 0, // Back-top-right
//                                       255, 0, 0, // Back-top-left
//                                    255, 0, 0, // Back-bottom-right
//                                    255, 0, 0, // Back-bottom-left
//                                    0, 255, 0, // Front-bottom-left
//                                    0, 255, 0, // Back-top-left
//                                    0, 255, 0, // Front-top-left
//                                    0, 0, 0, // Back-top-right
//                                    0, 0, 0, // Front-top-right
//                                    0, 0, 0, // Back-bottom-right
//                                    0, 0, 0, // Front-bottom-right
//                                    0, 0, 0, // Front-bottom-left
//                                    0, 0, 0, // Front-top-right
//                                    0, 0, 0, // Front-top-left
//};

Mesh* Mesh::generaCubo(GLdouble l)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = sizeof(cube_strip) / sizeof(GLfloat);
    mesh->vVertices.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i += 3)
    {
        mesh->vVertices.emplace_back(l* cube_strip[i], l * cube_strip[i + 1], l * cube_strip[i + 2]);
    }

    //mesh->vVertices.insert(mesh->vVertices.end(), cube_strip, cube_strip + sizeof(GLfloat) * 14);

    return mesh;
}

//Mesh* Mesh::generaCuboRGB(GLdouble l)
//{
//    Mesh* mesh = generaCubo(l);
//
//    mesh->vColors.reserve(mesh->mNumVertices);
//
//    for (int i = 0; i < mesh->mNumVertices; i += 3)
//    {
//        mesh->vColors.emplace_back(l * cube_colors[i], l * cube_colors[i + 1], l * cube_colors[i + 2], 1.0);
//    }
//
//    return mesh;
//}

Mesh* Mesh::generaCuboRGB(GLdouble l)
{
    Mesh* mesh = generaCubo(l);

    mesh->vColors.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i += 3)
    {
        mesh->vColors.emplace_back(cube_colors[i], cube_colors[i + 1], cube_colors[i + 2], 1.0);
    }

    return mesh;
}

Mesh* Mesh::generaPoligonoRegular(GLuint num, GLdouble r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = num;
    mesh->vVertices.reserve(mesh->mNumVertices);

    float aumento = 0.0;
    for (int i = 0; i < num; i++) {
        mesh->vVertices.emplace_back(r * cos(radians(90.0 + aumento)), r * sin(radians(90.0 + aumento)), 0.0);
        aumento += (360.0 / num);
    }

    //mesh->vColors.reserve(mesh->mNumVertices);
    //for (int j = 0; j < num; j++) 
    //{
    //    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    //}

    return mesh;
}

//Mesh* Mesh::createTriangle(float r)
//{
//    Mesh* mesh = new Mesh();
//
//    mesh->mPrimitive = GL_TRIANGLES;
//
//    mesh->mNumVertices = 3;
//    mesh->vVertices.reserve(3);
//
//    // X axis vertice
//    mesh->vVertices.emplace_back(r, 0.0, 0.0);
//    // Y axis vertice
//    mesh->vVertices.emplace_back(0.0, r, 0.0);
//    // Z axis vertice
//    mesh->vVertices.emplace_back(0.0, 0.0, r);
//
//    mesh->vColors.reserve(3);
//    // X axis color: cyan  (Alpha = 1 : fully opaque)
//    mesh->vColors.emplace_back(0, 255, 255, 1.0);
//    // Y axis color: cyan
//    mesh->vColors.emplace_back(0, 255, 255, 1.0);
//    // Z axis color: cyan
//    mesh->vColors.emplace_back(0, 255, 255, 1.0);
//
//    return mesh;
//}
//
//Mesh* Mesh::createCircle(float r)
//{
//    Mesh* mesh = new Mesh();
//
//    mesh->mPrimitive = GL_LINE_LOOP;
//
//    mesh->vVertices.reserve(360);
//
//    for (float i = 0.0; i < 360.0; i++) 
//    {
//        mesh->vVertices.emplace_back(r * cos(radians(i)), r * sin(radians(i)), 0.0);
//    }
//
//    mesh->vColors.reserve(360);
//    for (int i = 0; i < 360; i++)
//    {
//        mesh->vColors.emplace_back(255, 0, 255, 1.0); //magenta
//    }
//
//    return mesh;
//}

Mesh* Mesh::createTriangleRGB(float r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 3;
    mesh->vVertices.reserve(mesh->mNumVertices);

    float aumento = 0.0;
    for (int i = 0; i < 3; i++) {
        mesh->vVertices.emplace_back(r * cos(radians(90.0 + aumento)), r * sin(radians(90.0 + aumento)), 0.0);
        aumento += (360.0 / 3);
    }

    //// X axis vertice
    //mesh->vVertices.emplace_back(r/2, -r/2, 0);
    //// Y axis vertice
    //mesh->vVertices.emplace_back(-r/2, -r/2, 0.0);
    //// Z axis vertice
    //mesh->vVertices.emplace_back(0, r/2, 0);

    mesh->vColors.reserve(mesh->mNumVertices);
    // X axis color: cyan  (Alpha = 1 : fully opaque)
    mesh->vColors.emplace_back(255, 0, 0, 1.0);
    // Y axis color: cyan
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Z axis color: cyan
    mesh->vColors.emplace_back(0, 0, 255, 1.0);

    return mesh;
}

//
//Mesh* Mesh::generaTriangleRegular(GLuint num, GLdouble r)
//{
//    Mesh* mesh = new Mesh();
//
//    mesh->mPrimitive = GL_LINE_LOOP;
//
//    mesh->mNumVertices = num;
//    mesh->vVertices.reserve(mesh->mNumVertices);
//
//    for (float i = 0; i < 360; i += 360 / num)
//    {
//        //mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
//        //glVertex2f(r * cos(radians(i)), r * sin(radians(i)));
//
//        mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
//        mesh->vVertices.emplace_back(r * cos(radians(i)), r * sin(radians(i)), 0.0);
//    }
//
//    return mesh;
//
//    //glBegin(GL_LINE_LOOP);
//    //for (float i = 0; i < 360; i += 360/num)
//    //{
//    //    glVertex2f(r * cos(radians(i)), r * sin(radians(i)));
//    //}
//    //glVertex2f(r, 0);
//    //glEnd();
//}