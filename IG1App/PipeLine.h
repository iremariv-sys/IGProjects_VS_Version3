#ifndef _H_Pipeline_H_
#define _H_Pipeline_H_

#include "CompoundEntity.h"

class IndexedBox;

class Pipeline : public CompoundEntity
{
public:
	Pipeline();
	void update() override;

private:
	glm::vec4 colorForPhase(int phase) const;

	IndexedBox* mGlowNorth = nullptr;
	IndexedBox* mGlowSouth = nullptr;
	IndexedBox* mGlowWest = nullptr;
	IndexedBox* mGlowEast = nullptr;

	int mBlinkCounter = 0;
};

#endif //_H_Pipeline_H_