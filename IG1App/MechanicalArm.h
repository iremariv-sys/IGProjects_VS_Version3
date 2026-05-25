
#ifndef _H_MechanicalArm_H_
#define _H_MechanicalArm_H_

#include "CompoundEntity.h"
#include <glm/glm.hpp>

class IndexedBox;

class MechanicalArm : public CompoundEntity
{
public:
	explicit MechanicalArm();

	void update() override;

	void setBaseMat(const glm::mat4& mat) { mBaseMat = mat; updateNodes(); }
	void setHomePos(const glm::vec3& pos) { mBasePos = pos; updateNodes(); }
	void setPickPos(const glm::vec3& pos) { mPickPos = pos; }
	void setDropPos(const glm::vec3& pos) { mDropPos = pos; }
	void setCarriedBox(IndexedBox* box) { mCarriedBox = box; }
	

	void resetAnimation(int step = 0, int counter = 0)
	{
		mStep = step;
		mStepCounter = counter;
		mBoxAttached = false;
	}


private:
	void solveToTarget(const glm::vec3& worldTarget, float clawOpen);
	void updateNodes();
	glm::mat4 rootWorldMat() const;
	glm::mat4 gripperWorldMat() const;
	glm::mat4 baseScaleInverseMat() const;
	glm::mat4 makeBoxMatFromGrip() const;

	glm::mat4 mBaseMat = glm::mat4(1.0f);
	glm::vec3 mBasePos = glm::vec3(0.0f);
	glm::vec3 mPickPos = glm::vec3(0.0f);
	glm::vec3 mDropPos = glm::vec3(0.0f);

	CompoundEntity* mTurretNode = nullptr;
	CompoundEntity* mShoulderNode = nullptr;
	CompoundEntity* mElbowNode = nullptr;
	CompoundEntity* mWristNode = nullptr;

	IndexedBox* mClawTop = nullptr;
	IndexedBox* mClawBottom = nullptr;
	IndexedBox* mCarriedBox = nullptr;

	float mBaseYaw = 0.0f;
	float mShoulderAngle = 0.0f;
	float mElbowAngle = 0.0f;
	float mClawOpen = 16.0f;

	float mUpperLen = 62.0f;
	float mForeLen = 52.0f;
	float mGripLen = 24.0f;

	glm::vec3 mBoxHalfSize = glm::vec3(90.0f, 90.0f, 90.0f);

	int mStep = 0;
	int mStepCounter = 0;
	bool mBoxAttached = false;

};

#endif //_H_MechanicalArm_H_