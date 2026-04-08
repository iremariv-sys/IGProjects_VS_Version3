#include "BoxCubeOpen.h"

BoxCubeOpen::BoxCubeOpen(GLdouble length)
{
    mMesh = Mesh::generateBoxOutline(length);
    
}