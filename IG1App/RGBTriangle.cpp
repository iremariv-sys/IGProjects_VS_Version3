#include "RGBTriangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

RGBTriangle::RGBTriangle(GLdouble r) : EntityWithColors()
{
    mMesh = Mesh::generateRGBTriangle(r);
}

void RGBTriangle::update() {
    static float angleOrbit = 0.0f;   // ángulo para orbitar (antihorario)
    static float angleSpin = 0.0f;   // ángulo para girar sobre sí mismo (horario)

    // Incrementos
    angleOrbit += glm::radians(2.0f);   // antihorario
    angleSpin -= glm::radians(5.0f);   // horario (negativo)

    float R = 200.0f; // radio de la circunferencia

    // Posición orbital
    float x = R * cos(angleOrbit);
    float y = R * sin(angleOrbit);

    // 1. Trasladar al punto de la órbita
    glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));

    // 2. Rotar sobre sí mismo
    M = glm::rotate(M, angleSpin, glm::vec3(0, 0, 1));

    // Guardar la nueva matriz
    mModelMat = M;
}