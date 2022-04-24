#pragma once
#include "Entity.h"

using namespace glm;

class CompoundEntity : public Abs_Entity
{
public:
	CompoundEntity();
	~CompoundEntity();
	void addEntity(Abs_Entity* ae);
	void addTranslucidEntity(Abs_Entity* ae);

	void update() {};

	virtual void render(dmat4 const& modelViewMat) const override;

protected:
	std::vector<Abs_Entity*> gObjects;
	std::vector<Abs_Entity*> tObjects;

};

