
#include "MechanicalArm.h"
#include "IndexedBox.h"
#include "Sphere.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

MechanicalArm::MechanicalArm()
{
	const glm::vec4 metalDark(0.16f, 0.18f, 0.22f, 1.0f);
	const glm::vec4 metalLight(0.55f, 0.58f, 0.64f, 1.0f);
	const glm::vec4 accentRed(0.95f, 0.18f, 0.18f, 1.0f);

	IndexedBox* base = new IndexedBox(40.0);
	base->setColor(metalDark);
	base->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(2.8f, 0.7f, 2.8f)));
	addEntity(base);

	IndexedBox* column = new IndexedBox(24.0);
	column->setColor(metalDark);
	column->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 65.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 2.0f, 0.8f)));
	addEntity(column);

	mTurretNode = new CompoundEntity();
	addEntity(mTurretNode);

	Sphere* shoulder = new Sphere(14.0, 16, 32);
	shoulder->setColor(metalLight);
	shoulder->setModelMat(glm::mat4(1.0f));
	mTurretNode->addEntity(shoulder);

	mShoulderNode = new CompoundEntity();
	mTurretNode->addEntity(mShoulderNode);

	IndexedBox* upperArm = new IndexedBox(12.0);
	upperArm->setColor(metalDark);
	upperArm->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(mUpperLen * 0.5f, 0.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(mUpperLen / 12.0f, 0.45f, 0.45f)));
	mShoulderNode->addEntity(upperArm);

	IndexedBox* piston1 = new IndexedBox(10.0);
	piston1->setColor(accentRed);
	piston1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(mUpperLen * 0.35f, -6.0f, 10.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1.6f, 0.14f, 0.14f)));
	mShoulderNode->addEntity(piston1);

	mElbowNode = new CompoundEntity();
	mShoulderNode->addEntity(mElbowNode);

	Sphere* elbow = new Sphere(10.0, 16, 32);
	elbow->setColor(metalLight);
	elbow->setModelMat(glm::mat4(1.0f));
	mElbowNode->addEntity(elbow);

	IndexedBox* foreArm = new IndexedBox(10.0);
	foreArm->setColor(metalDark);
	foreArm->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(mForeLen * 0.5f, 0.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(mForeLen / 10.0f, 0.42f, 0.42f)));
	mElbowNode->addEntity(foreArm);

	IndexedBox* piston2 = new IndexedBox(10.0);
	piston2->setColor(accentRed);
	piston2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(mForeLen * 0.4f, -5.0f, -10.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 0.14f, 0.14f)));
	mElbowNode->addEntity(piston2);

	mWristNode = new CompoundEntity();
	mElbowNode->addEntity(mWristNode);

	Sphere* wrist = new Sphere(7.0, 14, 28);
	wrist->setColor(metalLight);
	wrist->setModelMat(glm::mat4(1.0f));
	mWristNode->addEntity(wrist);

	IndexedBox* wristSupport = new IndexedBox(12.0);
	wristSupport->setColor(metalDark);
	wristSupport->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.25f, 0.25f)));
	mWristNode->addEntity(wristSupport);

	mClawTop = new IndexedBox(12.0);
	mClawTop->setColor(metalLight);
	mWristNode->addEntity(mClawTop);

	mClawBottom = new IndexedBox(12.0);
	mClawBottom->setColor(metalLight);
	mWristNode->addEntity(mClawBottom);

	mBaseYaw = 0.0f;
	mShoulderAngle = glm::radians(15.0f);
	mElbowAngle = glm::radians(35.0f);
	mClawOpen = 16.0f;

	updateNodes();
}

glm::mat4 MechanicalArm::rootWorldMat() const
{
	return glm::translate(glm::mat4(1.0f), mBasePos) * mBaseMat;
}

glm::mat4 MechanicalArm::baseScaleInverseMat() const
{
	float sx = glm::length(glm::vec3(mBaseMat[0]));
	float sy = glm::length(glm::vec3(mBaseMat[1]));
	float sz = glm::length(glm::vec3(mBaseMat[2]));

	if (sx == 0.0f) sx = 1.0f;
	if (sy == 0.0f) sy = 1.0f;
	if (sz == 0.0f) sz = 1.0f;

	return glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / sx, 1.0f / sy, 1.0f / sz));
}

glm::mat4 MechanicalArm::gripperWorldMat() const
{
	glm::mat4 M = rootWorldMat();
	M = M * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 105.0f, 0.0f));
	M = M * glm::rotate(glm::mat4(1.0f), mBaseYaw, glm::vec3(0.0f, 1.0f, 0.0f));
	M = M * glm::rotate(glm::mat4(1.0f), mShoulderAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = M * glm::translate(glm::mat4(1.0f), glm::vec3(mUpperLen, 0.0f, 0.0f));
	M = M * glm::rotate(glm::mat4(1.0f), mElbowAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	M = M * glm::translate(glm::mat4(1.0f), glm::vec3(mForeLen + mGripLen, 0.0f, 0.0f));
	return M;
}

glm::mat4 MechanicalArm::makeBoxMatFromGrip() const
{
	glm::mat4 M = gripperWorldMat();
	M = M * baseScaleInverseMat();
	M = M * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -mBoxHalfSize.y, 0.0f));
	M = M * glm::scale(glm::mat4(1.0f), mBoxHalfSize * 2.0f);
	return M;
}

void MechanicalArm::solveToTarget(const glm::vec3& worldTarget, float clawOpen)
{
	glm::mat4 invRoot = glm::inverse(rootWorldMat());
	glm::vec4 targetLocal4 = invRoot * glm::vec4(worldTarget, 1.0f);
	glm::vec3 targetLocal = glm::vec3(targetLocal4);

	glm::vec3 shoulderPivot(0.0f, 105.0f, 0.0f);
	glm::vec3 v = targetLocal - shoulderPivot;

	float planar = std::sqrt(v.x * v.x + v.z * v.z);
	float vertical = v.y;

	mBaseYaw = std::atan2(v.z, v.x);

	float l1 = mUpperLen;
	float l2 = mForeLen + mGripLen;
	float d = std::sqrt(planar * planar + vertical * vertical);

	if (d > l1 + l2 - 0.001f) d = l1 + l2 - 0.001f;
	if (d < 1.0f) d = 1.0f;

	float cosElbow = (d * d - l1 * l1 - l2 * l2) / (2.0f * l1 * l2);
	if (cosElbow > 1.0f) cosElbow = 1.0f;
	if (cosElbow < -1.0f) cosElbow = -1.0f;

	float elbow = std::acos(cosElbow);

	float shoulder =
		std::atan2(vertical, planar) -
		std::atan2(l2 * std::sin(elbow), l1 + l2 * std::cos(elbow));

	mShoulderAngle = shoulder;
	mElbowAngle = elbow;
	mClawOpen = clawOpen;
}

void MechanicalArm::updateNodes()
{
	mModelMat = rootWorldMat();

	if (mTurretNode != nullptr) {
		mTurretNode->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 105.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), mBaseYaw, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	if (mShoulderNode != nullptr) {
		mShoulderNode->setModelMat(
			glm::rotate(glm::mat4(1.0f), mShoulderAngle, glm::vec3(0.0f, 0.0f, 1.0f)));
	}

	if (mElbowNode != nullptr) {
		mElbowNode->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(mUpperLen, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), mElbowAngle, glm::vec3(0.0f, 0.0f, 1.0f)));
	}

	if (mWristNode != nullptr) {
		mWristNode->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(mForeLen, 0.0f, 0.0f)));
	}

	if (mClawTop != nullptr) {
		mClawTop->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(mGripLen, mClawOpen, 5.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.16f, 0.16f)));
	}

	if (mClawBottom != nullptr) {
		mClawBottom->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(mGripLen, -mClawOpen, -5.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.16f, 0.16f)));
	}
}

void MechanicalArm::update()
{
	const int moveFrames = 70;
	const int holdFrames = 20;
	const float zOffset = 170.0f; 
	
	glm::vec3 restTarget = glm::vec3(rootWorldMat() * glm::vec4(90.0f, 150.0f, 0.0f, 1.0f));
	glm::vec3 pickGrip = mPickPos + glm::vec3(zOffset, 120.0f, 0.0f);
	glm::vec3 pickHover = pickGrip + glm::vec3(0.0f, 180.0f, 0.0f);
	glm::vec3 carryHover = mDropPos + glm::vec3(0.0f, 300.0f, 0.0f);

	int duration = moveFrames;
	if (mStep == 2 || mStep == 7) {
		duration = holdFrames;
	}

	float t = 1.0f;
	if (duration > 1) {
		t = float(mStepCounter) / float(duration - 1);
	}
	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	glm::vec3 target = restTarget;
	float claw = 16.0f;

	switch (mStep) {
	case 0: // reposo -> encima de la caja
		target = glm::mix(restTarget, pickHover, t);
		claw = 16.0f;
		mBoxAttached = false;
		break;

	case 1: // bajar a coger
		target = glm::mix(pickHover, pickGrip, t);
		claw = 16.0f;
		mBoxAttached = false;
		break;

	case 2: // cerrar pinza
		target = pickGrip;
		claw = 16.0f - 12.0f * t;
		mBoxAttached = true;
		break;

	case 3: // subir con la caja
		target = glm::mix(pickGrip, pickHover, t);
		claw = 4.0f;
		mBoxAttached = true;
		break;

	case 4: // mover la caja lejos
		target = glm::mix(pickHover, carryHover, t);
		claw = 4.0f;
		mBoxAttached = true;
		break;

	case 5: // volver encima de la caja
		target = glm::mix(carryHover, pickHover, t);
		claw = 4.0f;
		mBoxAttached = true;
		break;

	case 6: // bajar de nuevo a la caja original
		target = glm::mix(pickHover, pickGrip, t);
		claw = 4.0f;
		mBoxAttached = true;
		break;

	case 7: // abrir y soltar donde estaba
		target = pickGrip;
		claw = 4.0f + 12.0f * t;
		mBoxAttached = (t < 0.7f);
		break;

	case 8: // volver a reposo
		target = glm::mix(pickGrip, restTarget, t);
		claw = 16.0f;
		mBoxAttached = false;
		break;

	default:
		mStep = 0;
		mStepCounter = 0;
		mBoxAttached = false;
		target = restTarget;
		claw = 16.0f;
		break;
	}

	solveToTarget(target, claw);
	updateNodes();

	if (mCarriedBox != nullptr) {
		if (mBoxAttached) {
			mCarriedBox->setModelMat(makeBoxMatFromGrip());
		}
		else {
			// ajustar elevación de la caja cuando no está sujeta
			const float lift = 82.0f; 
			glm::vec3 center = mPickPos + glm::vec3(0.0f, lift - mBoxHalfSize.y, zOffset);
			glm::mat4 boxMat =
				glm::translate(glm::mat4(1.0f), center) *
				glm::scale(glm::mat4(1.0f), mBoxHalfSize * 2.0f);
			mCarriedBox->setModelMat(boxMat);
		}
	}
	




	mStepCounter++;
	if (mStepCounter >= duration) {
		mStepCounter = 0;
		mStep++;
		if (mStep > 8) {
			mStep = 0;
		}
	}
}