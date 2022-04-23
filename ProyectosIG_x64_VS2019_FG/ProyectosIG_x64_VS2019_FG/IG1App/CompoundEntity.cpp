#include "CompoundEntity.h"
#include "Camera.h"
using namespace glm;

CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

void CompoundEntity::render(dmat4 const& modelViewMat) const
{
	for (Abs_Entity* el : gObjects)
	{
		el->render(modelViewMat);
	}
}