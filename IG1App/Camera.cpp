#include "Shader.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/matrix_access.hpp>
using namespace glm;

Camera::Camera(Viewport* vp)
    : mViewMat(1.0)
    , mProjMat(1.0)
    , xRight(vp->width() / 2.0)
    , xLeft(-xRight)
    , yTop(vp->height() / 2.0)
    , yBot(-yTop)
    , mViewPort(vp)
{
    setPM();
}

void Camera::setAxes()
{
    mRight = row(mViewMat,0);
    mUpward = row(mViewMat, 1);
    mFront = -row(mViewMat, 2);
}

void Camera::setVM()
{
    mViewMat = lookAt(mEye, mLook, mUp);
    setAxes();
}


void Camera::set2D()
{
    // Posición original del proyecto IG1
    mEye = glm::vec3(0.0f, 0.0f, 500.0f);
    mLook = glm::vec3(0.0f, 0.0f, 0.0f);
    //mUpward = glm::vec3(0.0f, 1.0f, 0.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    // Cálculo coherente de radio y ángulo
    glm::vec3 v = mEye - mLook;
    mRadio = glm::length(v);
    mAng = atan2(v.z, v.x);

    setVM();
    setPM();
}


void Camera::set3D()
{
    //// Posición original del proyecto IG1
    //mEye = glm::vec3(500.0f, 500.0f, 500.0f);
    //mLook = glm::vec3(0.0f, 0.0f, 0.0f);
    ////mUpward = glm::vec3(0.0f, 1.0f, 0.0f);
    //mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    //// Cálculo coherente de radio y ángulo
    //glm::vec3 v = mEye - mLook;
    //mRadio = glm::length(v);
    //mAng = atan2(v.z, v.x);

    //setVM();
    //setPM();
    
    //mEye = glm::vec3(1300.0f, 800.0f, 1300.0f);
    //mLook = glm::vec3(0.0f, 100.0f, 0.0f);
    //mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bOrto = false;

    // Esquina del laboratorio, ligeramente elevada
    mEye = glm::vec3(-1300.0f, 480.0f, 1300.0f);
    mLook = glm::vec3(0.0f, 150.0f, 0.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 v = mEye - mLook;
    mRadio = glm::length(v);
    mAng = atan2(v.z, v.x);

    setVM();
    setPM();
    
}


void Camera::pitch(GLfloat a)
{
    mViewMat = rotate(mViewMat, radians(a), vec3(1.0, 0, 0));
    setAxes();//Lo pide el Apartado 39
}

void Camera::yaw(GLfloat a)
{
    mViewMat = rotate(mViewMat, radians(a), vec3(0, 1.0, 0));
    setAxes();//Lo pide el Apartado 39
}

void Camera::roll(GLfloat a)
{
    mViewMat = rotate(mViewMat, radians(a), vec3(0, 0, 1.0));
    setAxes();// Apartado 39
}
void Camera::moveLR(GLfloat cs)//Apartado 40
{
    mEye += cs * mRight;
    mLook += cs * mRight;
    setVM();
}
void Camera::moveFB(GLfloat cs)//Apartado 40
{
    mEye += cs * mFront;
    mLook += cs * mFront;
    setVM();
}
void Camera::moveUD(GLfloat cs)//Apartado 40
{
    mEye += cs * mUpward;
    mLook += cs * mUpward;
    setVM();
}

void Camera::setSize(GLdouble xw, GLdouble yh)
{
    xRight = xw / 2.0;
    xLeft = -xRight;
    yTop = yh / 2.0;
    yBot = -yTop;
    setPM();
}



void Camera::setScale(GLdouble s)
{
    mScaleFact -= s;
    if (mScaleFact < 0)
        mScaleFact = 0.01;

    setPM();   // recalcula la proyección con el nuevo zoom Apartado 42
}


//
//void Camera::setPM()
//{
//    if (bOrto) {
//        // Proyección ortogonal — usa mScaleFact para el zoom
//        mProjMat = ortho(xLeft * mScaleFact,
//            xRight * mScaleFact,
//            yBot * mScaleFact,
//            yTop * mScaleFact,
//            mNearVal, mFarVal);
//    }
//    else {
//        float aspect = mViewPort->width() / float(mViewPort->height());
//
//        //FOV escalado con mScaleFact: más pequeño = zoom in, más grande = zoom out
//        float fov = glm::clamp(
//            glm::radians(50.0f) * static_cast<float>(mScaleFact),
//            glm::radians(5.0f),    // límite mínimo (zoom in)
//            glm::radians(170.0f)   // límite máximo (zoom out)
//        );
//
//        mProjMat = glm::perspective(fov, aspect, mNearVal, mFarVal);
//    }
//}

void Camera::setPM()
{
    float aspect = mViewPort->width() / float(mViewPort->height());

    if (bOrto)
    {
        mProjMat = glm::ortho(
            xLeft * mScaleFact,
            xRight * mScaleFact,
            yBot * mScaleFact,
            yTop * mScaleFact,
            mNearVal,
            mFarVal
        );
    }
    else
    {
        float fov = glm::radians(45.0f);

        mProjMat = glm::perspective(
            fov,
            aspect,
            //0.1f,
            //100.0f
            1.0f,
            5000.0f
        );
    }
}

void Camera::changePrj()//Apartadp 41
{
    bOrto = !bOrto;   // alterna entre ortogonal y perspectiva
    setPM();          // recalcula la matriz de proyección
}



// Apartado 45
void Camera::pitchReal(GLfloat cs)
{
    float dist = glm::length(mLook - mEye);  // preservar distancia ojo-objetivo
    glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mRight);
    mFront = glm::normalize(glm::vec3(R * glm::vec4(mFront, 0.0f)));
    mUpward = glm::normalize(glm::vec3(R * glm::vec4(mUpward, 0.0f)));
    mUp = mUpward;
    mLook = mEye + mFront * dist;  //  mantener distancia original
    setVM();
}

void Camera::yawReal(GLfloat cs)
{
    float dist = glm::length(mLook - mEye);  // preservar distancia ojo-objetivo
    glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mUpward);
    mFront = glm::normalize(glm::vec3(R * glm::vec4(mFront, 0.0f)));
    mRight = glm::normalize(glm::vec3(R * glm::vec4(mRight, 0.0f)));
    mUp = mUpward;
    mLook = mEye + mFront * dist;  //  mantener distancia original
    setVM();
}

void Camera::rollReal(GLfloat cs)
{
    // mFront no cambia  mLook no cambia  distancia se preserva sola
    glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(cs), mFront);
    mRight = glm::normalize(glm::vec3(R * glm::vec4(mRight, 0.0f)));
    mUpward = glm::normalize(glm::vec3(R * glm::vec4(mUpward, 0.0f)));
    mUp = mUpward;
    setVM();
}
//Apartado 46
void Camera::orbit(GLfloat incAng, GLfloat incY)
{
    glm::vec3 v = mEye - mLook;
    GLfloat dist = glm::length(v);

    // Ángulo horizontal
    GLfloat ang = atan2(v.z, v.x);
    ang += glm::radians(incAng);

    // Nueva altura, limitada para no colapsar la cámara
    GLfloat y = v.y + incY;
    GLfloat maxY = dist * 0.99f;
    y = glm::clamp(y, -maxY, maxY);

    // Radio horizontal compatible con la distancia total
    GLfloat r = sqrt(glm::max(dist * dist - y * y, 0.0f));

    v.x = r * cos(ang);
    v.z = r * sin(ang);
    v.y = y;

    mEye = mLook + v;

    mFront = glm::normalize(mLook - mEye);
    mRight = glm::normalize(glm::cross(mFront, glm::vec3(0, 1, 0)));
    mUpward = glm::normalize(glm::cross(mRight, mFront));
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);

    setVM();
}
//void Camera::setCenital()//Apartado 48
//{
//    // Colocar la cámara justo encima del punto de interés
//    mEye = mLook + glm::vec3(0.0f, 500.0f, 0.0f);  // altura cenital
//
//    // Mirar hacia abajo
//    mUpward = glm::vec3(0.0f, 0.0f, -1.0f);        // Up coherente para vista cenital
//
//    // Calcular radio y ángulo
//    glm::vec3 v = mEye - mLook;
//    mRadio = glm::length(v);
//    mAng = atan2(v.z, v.x);
//
//    setVM();
//    setPM();
//}

void Camera::setCenital()// Apartado 49
{
    mEye = mLook + glm::vec3(0.0f, 500.0f, 0.0f);
    mUp = glm::vec3(0.0f, 0.0f, -1.0f);  //  mUp
    glm::vec3 v = mEye - mLook;
    mRadio = glm::length(v);
    mAng = atan2(v.z, v.x);
    setVM();
    setPM();
}

void Camera::uploadPM() const
{
    Shader::setGlobals(mProjMat);
}


void Camera::upload() const
{
    mViewPort->upload();
    uploadPM();

    //Shader* lightShader = Shader::get("simple_light");
    //lightShader->use();

    //glm::vec4 lightDirView = mViewMat * glm::vec4(-1.0f, -1.5f, -1.25f, 0.0f);
    //lightDirView = glm::vec4(glm::normalize(glm::vec3(lightDirView)), 0.0f);

    //lightShader->setUniform("lightDir", lightDirView);
}