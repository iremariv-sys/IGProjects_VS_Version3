#include "RGBCube.h"
RGBCube::RGBCube(GLdouble size) : EntityWithColors()
{
    mMesh = Mesh::generateRGBCubeTriangles(size);
}