#pragma once
#include "Entity.h"

class QuadricEntity : public Abs_Entity 
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

class Sphere : public QuadricEntity 
{
public:
	Sphere(GLdouble rr); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	GLdouble r;
};

class Cylinder : public QuadricEntity
{
public:
	Cylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble h);
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	GLdouble baseRadius;
	GLdouble topRadius;
	GLdouble h;
};

class Disk : public QuadricEntity
{
public:
	Disk(GLdouble innerRadius, GLdouble outerRadius);
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	GLdouble innerRadius;
	GLdouble outerRadius;
};

class PartialDisk : public QuadricEntity
{
public:
	PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle);
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLdouble startAngle;
	GLdouble sweepAngle;
};

//class PartialDisk : public QuadricEntity
//{
//public:
//	PartialDisk(GLdouble r); // r es el radio de la esfera
//	void render(glm::dmat4 const& modelViewMat) const;
//protected:
//	GLdouble r;
//};
//
