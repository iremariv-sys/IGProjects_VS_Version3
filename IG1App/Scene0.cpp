#include "Scene0.h"
#include "LaboratoryRoom.h"
#include "Texture.h"
#include <glm/ext/matrix_transform.hpp>
#include "HexagonalBase.h"
#include "ADNStructure.h"
#include "GlassPanel.h"
#include "GlassCap.h"
#include "Cone.h"
#include "Disk.h"
#include "LightColumn.h"
#include "Light.h"
#include "TechStation.h"
#include "Chair.h"
#include "IndexedBox.h"
#include "EntityWithTexture.h"
#include "Pipeline.h"
#include "Shelf.h"
#include "Door.h"
#include "MechanicalArm.h"
#include <cmath>


Texture* Scene0::createTexture(const char* path, int repeat)
{
	Texture* tex = new Texture();
	tex->load(path, repeat);
	mTextures.push_back(tex);
	return tex;
}
//los shelf de las equinas
void Scene0::addShelf(const glm::vec3& pos, float angleDeg, int lightId, SpotLight*& outLight)
{
	Shelf* shelf = new Shelf(lightId);
	shelf->setModelMat(
		glm::translate(glm::mat4(1.0f), pos) *
		glm::rotate(glm::mat4(1.0f), glm::radians(angleDeg), glm::vec3(0.0f, 1.0f, 0.0f)));
	gObjects.push_back(shelf);

	outLight = shelf->light();
	if (outLight != nullptr) {
		outLight->setPosition(glm::vec3(shelf->modelMat() * glm::vec4(0.0f, 510.0f, 35.0f, 1.0f)));
		gLights.push_back(outLight);
	}
}

Scene0::~Scene0()
{
	for (Texture* tex : mTextures)
		delete tex;
	mTextures.clear();
}


//color de escena 
glm::vec4 Scene0::clearColor() const
{
	return glm::vec4(0.05f, 0.06f, 0.08f, 1.0f);

}

//repetion de codigo para crear objetos
glm::mat4 makeTR(const glm::vec3& pos, float angleDeg, const glm::vec3& axis = glm::vec3(0.0f, 1.0f, 0.0f))
{
	return glm::translate(glm::mat4(1.0f), pos) *
		glm::rotate(glm::mat4(1.0f), glm::radians(angleDeg), axis);
}

glm::mat4 makeTS(const glm::vec3& pos, const glm::vec3& scale)
{
	return glm::translate(glm::mat4(1.0f), pos) *
		glm::scale(glm::mat4(1.0f), scale);
}

void setEnabled(PosLight* light, bool enabled)
{
	if (light != nullptr)
		light->setEnabled(enabled);
}

//para creear las cajas de los brazos mecanicos
	IndexedBox* Scene0::createBox(const glm::vec3& pos)
	{
		IndexedBox* box = new IndexedBox(1.0);
		box->setColor(glm::vec4(0.55f, 0.35f, 0.20f, 1.0f));
		box->setModelMat(makeTS(pos, glm::vec3(180.0f, 180.0f, 180.0f)));
		return box;
	}
	//para crear los paneles de las estaciones de trabajo
	EntityWithTexture* Scene0::createPanel(Texture* tex, const glm::vec3& pos, float angleDeg)
	{
		EntityWithTexture* panel = new EntityWithTexture(tex);
		panel->setMesh(Mesh::generaRectangleTexCor(1000.0, 660.0, 1, 1));
		panel->setModelMat(makeTR(pos, angleDeg, glm::vec3(1.0f, 0.0f, 0.0f)));
		return panel;
	}

	MechanicalArm* createMechanicalArm_local(const glm::vec3& home,
		const glm::vec3& pick,
		const glm::vec3& drop,
		const glm::mat4& baseMat)
	{
		MechanicalArm* arm = new MechanicalArm();
		arm->setHomePos(home);
		arm->setPickPos(pick);
		arm->setDropPos(drop);
		arm->setBaseMat(baseMat);
		return arm;
	}

void Scene0::init()
{
	
	Scene::init();
	

	//carga de las texturas 
	Texture* floorTex = createTexture("../assets/images/floor.jpg", 255);
	Texture* wallTex = createTexture("../assets/images/la2.jpg", 255);
	Texture* wallTex2 = createTexture("../assets/images/la2.jpg", 255);
	Texture* screenTex = createTexture("../assets/images/noche.jpg", 255);
	Texture* controlTex = createTexture("../assets/images/lab-computer.png", 255);
	Texture* doorTex = createTexture("../assets/images/security.jpg", 255);


	//Laboratory Room - Tamaño
	LaboratoryRoom* room = new LaboratoryRoom(4000.0, 4000.0, 1500.0, floorTex, wallTex, wallTex2);
	gObjects.push_back(room);

	const float structureScale = 1.35f;

	HexagonalBase* base = new HexagonalBase();
	base->setModelMat(glm::scale(glm::mat4(1.0f), glm::vec3(structureScale)));
	gObjects.push_back(base);

	//estructura ADN
	ADNStructure* adn = new ADNStructure();
	adn->setBaseMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(structureScale)));
	adn->update();
	gObjects.push_back(adn);

	//pipelines
	mPipeline = new Pipeline();
	gObjects.push_back(mPipeline);

	
// brazo robot
		
	mArm = createMechanicalArm_local(
		glm::vec3(-900.0f, 0.0f, -1000.0f),
		glm::vec3(-650.0f, 90.0f, -1000.0f),
		glm::vec3(-350.0f, 90.0f, -1000.0f),
		glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(2.8f))
	);
	gObjects.push_back(mArm);

	// caja que coge el brazo
	mBox = createBox(glm::vec3(-630.0f, 82.0f, -1000.0f));
	gObjects.push_back(mBox);
	mArm->setCarriedBox(mBox);
	mArm->resetAnimation(0, 0);


	// brazo robot 2 en diagonal

	mArm2 = createMechanicalArm_local(
		glm::vec3(1200.0f, 0.0f, 1200.0f),
		glm::vec3(630.0f, 90.0f, 1200.0f),
		glm::vec3(650.0f, 90.0f, 1200.0f),
		glm::rotate(glm::mat4(1.0f), glm::radians(190.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(2.8f))
	);
	gObjects.push_back(mArm2);

	// caja que coge el brazo 2
	mBox2 = createBox(glm::vec3(630.0f, 82.0f, 1050.0f));
	gObjects.push_back(mBox2);
	mArm2->setCarriedBox(mBox2);
	mArm2->resetAnimation(4, 35);

	//paneles 
	EntityWithTexture* panel1 = createPanel(controlTex, glm::vec3(0.0f, 700.0f, -1990.0f), 90.0f);
	gObjects.push_back(panel1);

	EntityWithTexture* panel2 = createPanel(controlTex, glm::vec3(0.0f, 700.0f, 1990.0f), -90.0f);
	gObjects.push_back(panel2);

	
	//tapa del cristal
	const float glassRadius = 120.0f * structureScale;
	const float glassHeight = 490.0f * structureScale;
	const float glassCenterY = 80.0f * structureScale;
	const float glassTopY = glassCenterY + glassHeight * 0.5f;

	GlassCap* cap = new GlassCap(
		120.0,
		glassRadius * 1.3f,
		glassRadius * 0.80f, 0);

	cap->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, glassTopY + 350.0f, 0.0f)));

	mSpotLight = cap->light();
	if (mSpotLight != nullptr) {
		mSpotLight->setPosition(glm::vec3(0.0f, glassTopY + 350.0f + 120.0f * 0.20f, 0.0f));
		mSpotLight->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
		mSpotLight->setCutoff(28.0f, 35.0f);
		mSpotLight->setEnabled(true);
	}

	gObjects.push_back(cap);
	gLights.push_back(mSpotLight);

	
		
	//columns de luz
	LightColumn* c1 = new LightColumn(950.0, 55.0, glm::vec4(0.20f, 0.55f, 1.0f, 1.0f), glm::vec3(-1600.0f, 0.0f, -1600.0f), 0);
	LightColumn* c2 = new LightColumn(950.0, 55.0, glm::vec4(0.25f, 0.95f, 0.70f, 1.0f), glm::vec3(1600.0f, 0.0f, -1600.0f), 1);
	LightColumn* c3 = new LightColumn(950.0, 55.0, glm::vec4(0.20f, 0.55f, 1.0f, 1.0f), glm::vec3(-1600.0f, 0.0f, 1600.0f), 2);
	LightColumn* c4 = new LightColumn(950.0, 55.0, glm::vec4(0.25f, 0.95f, 0.70f, 1.0f), glm::vec3(1600.0f, 0.0f, 1600.0f), 3);

	gObjects.push_back(c1);
	gObjects.push_back(c2);
	gObjects.push_back(c3);
	gObjects.push_back(c4);

	mColumnLight1 = c1->light();
	mColumnLight2 = c2->light();
	mColumnLight3 = c3->light();
	mColumnLight4 = c4->light();

	gLights.push_back(mColumnLight1);
	gLights.push_back(mColumnLight2);
	gLights.push_back(mColumnLight3);
	gLights.push_back(mColumnLight4);

	
//Estacion de Trabajo
	// computadores encima de la mesa
	TechStation* station1 = new TechStation(screenTex);
	station1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, -1700.0f)));
	gObjects.push_back(station1);

	TechStation* station2 = new TechStation(screenTex);
	station2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, -1700.0f)));
	gObjects.push_back(station2);

//Chairs de las mesas 
	Chair* chair1 = new Chair();
	chair1->setModelMat(makeTR(glm::vec3(-550.0f, 0.0f, -1320.0f), -190.0f));
	gObjects.push_back(chair1);

	Chair* chair2 = new Chair();
	chair2->setModelMat(makeTR(glm::vec3(550.0f, 0.0f, -1420.0f), 160.0f));
	gObjects.push_back(chair2);

	//Shef
	addShelf(glm::vec3(-1950.0f, 0.0f, -400.0f), 90.0f, 1, mShelfLight1);
	addShelf(glm::vec3(-1950.0f, 0.0f, 500.0f), 90.0f, 2, mShelfLight2);
	addShelf(glm::vec3(1950.0f, 0.0f, -400.0f), -90.0f, 3, mShelfLight3);


	//door
	Door* door = new Door(doorTex);
	door->setModelMat(makeTR(glm::vec3(1990.0f, 0.0f, 1000.0f), 180.0f));
	gObjects.push_back(door);
	
	//cilindro de luz transparente
	CircularGlass* glass = new CircularGlass(glassRadius, glassHeight, glm::vec4(0.55f, 0.85f, 1.0f, 0.18f));
	glass->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, glassCenterY, 0.0f)));
	gObjects.push_back(glass);


}



void Scene0::togglePosLight()
{
	mColumnsEnabled = !mColumnsEnabled;

	setEnabled(mColumnLight1, mColumnsEnabled);
	setEnabled(mColumnLight2, mColumnsEnabled);
	setEnabled(mColumnLight3, mColumnsEnabled);
	setEnabled(mColumnLight4, mColumnsEnabled);
}

void Scene0::toggleSpotLight()
{
	if (mSpotLight != nullptr)
		mSpotLight->setEnabled(!mSpotLight->enabled());

	const bool shelfEnabled = !(mShelfLight1 != nullptr && mShelfLight1->enabled());

	setEnabled(mShelfLight1, shelfEnabled);
	setEnabled(mShelfLight2, shelfEnabled);
	setEnabled(mShelfLight3, shelfEnabled);
}


void Scene0::update()
{
	Scene::update();

	mAnimTime += 0.03f;

	if (mSpotLight != nullptr) {
		float pulse = 2.2f + 0.8f * sin(mAnimTime * 2.0f);
		mSpotLight->setDiff(glm::vec3(pulse, 0.05f, 0.05f));
		mSpotLight->setSpec(glm::vec3(pulse * 1.2f, 0.10f, 0.10f));
	}
}


