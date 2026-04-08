#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Viewport.h"

class Camera
{
public:
    explicit Camera(Viewport* vp);
    ~Camera() = default;


    // getter de la view matrix
    const glm::mat4& viewMat() const { return mViewMat; }

    // viewport
    Viewport const& viewPort() const { return *mViewPort; }

    // proyección
    glm::mat4 const& projMat() const { return mProjMat; }

    // Apartado 41 cambia de proyección ortogonal a perspectiva y viceversa.
    void changePrj();
    // Apartado 46
    void orbit(GLfloat incAng, GLfloat incY);
    
    //Apartado 47
   // GLfloat mRadio;   // distancia de la cámara al punto mLook
   // GLfloat mAng;     // ángulo horizontal en el plano XZ
    GLfloat mRadio = 500.0f;  //valor coherente con mEye inicial (0,0,500)
    GLfloat mAng = 0.0f;
    void setCenital();   // Apartado 48


    // modos de cámara
    void set2D();
    void set3D();

    // rotaciones
    void pitch(GLfloat a);
    void yaw(GLfloat a);
    void roll(GLfloat a);

    // tamaño y escala
    void setSize(GLdouble xw, GLdouble yh);
    void setScale(GLdouble s);

    // subir matrices a GPU
    void upload() const;

    //Apartado 40
    void moveLR(GLfloat cs); // izquierda / derecha
    void moveFB(GLfloat cs); // adelante / atrás
    void moveUD(GLfloat cs); // arriba / abajo
    
    //Apartado 41
    void pitchReal(GLfloat cs);
    void yawReal(GLfloat cs);
    void rollReal(GLfloat cs);



protected:
    glm::vec3 mEye = { 0.0, 0.0, 500.0 };
    glm::vec3 mLook = { 0.0, 0.0, 0.0 };
    glm::vec3 mUp = { 0.0, 1.0, 0.0 };

    // ejes de la cámara
    glm::vec3 mRight, mUpward, mFront;

    glm::mat4 mViewMat;   // view matrix
    glm::mat4 mProjMat;   // projection matrix

    void uploadPM() const;

    GLfloat xRight, xLeft, yTop, yBot;
    GLfloat mNearVal = 1, mFarVal = 10000;
    GLfloat mScaleFact = 1;
    bool bOrto = true;

    Viewport* mViewPort;

    void setVM();
    void setPM();
    void setAxes();//Apartado 38
};

#endif //_H_Camera_H_

