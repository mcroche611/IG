//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(1.0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	virtual void update() = 0;

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//atributo color
	glm::dvec4 const& color() { return mColor; };
	void setColor(glm::dvec4 const& aColor) { mColor = aColor; };
	
	void setTexture(Texture* tex) { mTexture = tex; };
protected:

	Mesh* mMesh = nullptr;   // the mesh
	Texture* mTexture = nullptr; //the texture
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;       // color de la entidad
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
};

//-------------------------------------------------------------------------

class Ejes2D : public Abs_Entity
{
public:
	explicit Ejes2D(GLdouble l);
	~Ejes2D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
};

#endif //_H_Entities_H_