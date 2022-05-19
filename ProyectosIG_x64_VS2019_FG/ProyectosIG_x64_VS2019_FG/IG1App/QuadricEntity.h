#pragma once
#include "EntityWithMaterial.h"
using namespace glm;

class QuadricEntity : public EntityWithMaterial
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
	void renderColor() const;
protected:
	GLUquadricObj* q;
};

class Sphere : public QuadricEntity		
{
public:
	Sphere(GLdouble rr);
	// r es el radio de la esfera
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

class MyCone : public QuadricEntity
{
public:
	MyCone(GLdouble baseRadius, GLdouble h);
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	GLdouble baseRadius;
	GLdouble h;
};

class RevCone : public QuadricEntity
{
public:
	RevCone(GLdouble baseRadius, GLdouble h);
	void render(glm::dmat4 const& modelViewMat) const;
	void update() {};
protected:
	GLdouble baseRadius;
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
