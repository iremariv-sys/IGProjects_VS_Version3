#include <vector>
#include <fstream>
#include "Photo.h"

Photo::Photo(GLsizei winW, GLsizei winH, GLdouble w, GLdouble h)
    : EntityWithTexture(new Texture(), false)
    , mWinW(winW)
    , mWinH(winH)
{
    //sobre el suelo
    mMesh = Mesh::generaRectangleTexCor(w, h, 1, 1);
}

Photo::~Photo()
{
    delete mTexture;
    mTexture = nullptr;
}

void Photo::render(glm::mat4 const& modelViewMat) const
{
    
    if (mTexture != nullptr)
        mTexture->loadColorBuffer(mWinW, mWinH, GL_BACK);

    EntityWithTexture::render(modelViewMat);
}
// Capture de la Foto
void Photo::capture()
{
    if (mTexture != nullptr)
        mTexture->loadColorBuffer(mWinW, mWinH, GL_BACK);
}

void Photo::saveToBMP(const char* filename) const
{
    std::vector<unsigned char> pixels(3 * mWinW * mWinH);

    //glPixelStorei(GL_PACK_ALIGNMENT, 1);
    //glReadPixels(0, 0, mWinW, mWinH,
    //    GL_BGR, GL_UNSIGNED_BYTE,
    //    pixels.data());

    glReadBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, mWinW, mWinH,
        GL_BGR, GL_UNSIGNED_BYTE,
        pixels.data());

    std::ofstream file(filename, std::ios::binary);
    if (!file) return;

    unsigned char fileHeader[14] = {
        'B','M',
        0,0,0,0,
        0,0,0,0,
        54,0,0,0
    };
    unsigned char infoHeader[40] = {
        40,0,0,0,
        0,0,0,0,
        0,0,0,0,
        1,0,
        24,0
    };

    int fileSize = 54 + 3 * mWinW * mWinH;

    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);

    infoHeader[4] = (unsigned char)(mWinW);
    infoHeader[5] = (unsigned char)(mWinW >> 8);
    infoHeader[6] = (unsigned char)(mWinW >> 16);
    infoHeader[7] = (unsigned char)(mWinW >> 24);

    infoHeader[8] = (unsigned char)(mWinH);
    infoHeader[9] = (unsigned char)(mWinH >> 8);
    infoHeader[10] = (unsigned char)(mWinH >> 16);
    infoHeader[11] = (unsigned char)(mWinH >> 24);

    file.write((char*)fileHeader, 14);
    file.write((char*)infoHeader, 40);

    //for (int y = 0; y < mWinH; ++y)
    //{
    //    file.write((char*)(pixels.data()
    //        + (mWinW * (mWinH - y - 1) * 3)),
    //        mWinW * 3);
    //}

    //file.close();

    for (int y = 0; y < mWinH; ++y)
    {
        file.write((char*)(pixels.data() + y * mWinW * 3), mWinW * 3);
    }

    file.close();
}