#include "TechStation.h"
#include <glm/gtc/matrix_transform.hpp>

class ScreenPanel : public EntityWithTexture
{
public:
    ScreenPanel(Texture* tex, GLdouble w, GLdouble h)
        : EntityWithTexture(tex)
    {
        mMesh = Mesh::generaRectangleTexCor(w, h, 1, 1);
    }
};

TechStation::TechStation(Texture* screenTex)
    : mScreenTex(screenTex)
{
    const glm::vec4 deskColor(0.18f, 0.20f, 0.24f, 1.0f);
    const glm::vec4 metalColor(0.28f, 0.30f, 0.34f, 1.0f);

    // Tablero
    IndexedBox* top = new IndexedBox(1.0);
    top->setColor(deskColor);
    top->setModelMat(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 120.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(420.0f, 20.0f, 220.0f)));
    addEntity(top);

    // Patas
    auto addLeg = [&](float x, float z)
        {
            IndexedBox* leg = new IndexedBox(1.0);
            leg->setColor(metalColor);
            leg->setModelMat(
                glm::translate(glm::mat4(1.0f), glm::vec3(x, 60.0f, z)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 120.0f, 20.0f)));
            addEntity(leg);
        };

    addLeg(-180.0f, -90.0f);
    addLeg(180.0f, -90.0f);
    addLeg(-180.0f, 90.0f);
    addLeg(180.0f, 90.0f);

    // Torre/soporte del monitor
    IndexedBox* stand = new IndexedBox(1.0);
    stand->setColor(metalColor);
    stand->setModelMat(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 155.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(30.0f, 80.0f, 30.0f)));
    addEntity(stand);

    // Cuerpo del monitor
    IndexedBox* monitor = new IndexedBox(1.0);
    monitor->setColor(glm::vec4(0.08f, 0.08f, 0.10f, 1.0f));
    monitor->setModelMat(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 270.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(260.0f, 160.0f, 10.0f)));
    addEntity(monitor);

    // Pantalla texturizada
    ScreenPanel* screen = new ScreenPanel(screenTex,230.0, 120.0);
    screen->setModelMat(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 270.0f, 9.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f))
    );
    addEntity(screen);

    // Teclado opcional
    IndexedBox* keyboard = new IndexedBox(1.0);
    keyboard->setColor(glm::vec4(0.12f, 0.13f, 0.15f, 1.0f));
    keyboard->setModelMat(
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 145.0f, 100.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(160.0f, 8.0f, 60.0f)));
    addEntity(keyboard);
}