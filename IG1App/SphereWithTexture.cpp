#include "SphereWithTexture.h"
#include "IndexMesh.h"

SphereWithTexture::SphereWithTexture(GLdouble radius, GLuint nParallel, GLuint nMeridians)
    : EntityWithTexture(new Texture(), false)
{
    mTexture->load("../assets/images/container.jpg");
    setMesh(IndexMesh::generateSphere(radius, nParallel, nMeridians));
}

SphereWithTexture::~SphereWithTexture()
{
    delete mTexture;
    mTexture = nullptr;
}