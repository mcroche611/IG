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

void CompoundEntity::addTranslucidEntity(Abs_Entity* ae)
{
	tObjects.push_back(ae);
}

void CompoundEntity::render(dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	for (auto g : gObjects) {
		g->render(aMat);
	}
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (Abs_Entity* el : tObjects)
	{
		el->render(aMat);
	}
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
