#pragma once
#include "Entity.h"

class QuadricEntity : public Abs_Entity
{
	QuadricEntity();
};

class Sphere : public QuadricEntity
{
	Sphere();
};

class Cylinder : public QuadricEntity
{
	Cylinder();
};

class Disk : public QuadricEntity
{
	Disk();
};

class PartialDisk : public QuadricEntity
{
	PartialDisk();
};

