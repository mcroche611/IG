#pragma once
#include "Entity.h"
#include "Material.h"

class EntityWithMaterial : public Abs_Entity
{
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};

