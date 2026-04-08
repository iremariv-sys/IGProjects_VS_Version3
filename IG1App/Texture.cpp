#include "Texture.h"

#include "Image.h"

Texture::~Texture()
{
	if (mId != 0)
		glDeleteTextures(1, &mId);
}

void
Texture::init()
{
	/*glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);*/
	// genera un identificador para una nueva textura
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId); 
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void
Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, mId);
}

void
Texture::load(const std::string& name, GLubyte alpha)
{
	if (mId == 0)
		init();

	Image image;
	image.load(name);

	if (alpha != 255)
		image.setAlpha(alpha);

	mWidth = image.width();
	mHeight = image.height();

	GLint level = 0;  // Base image level
	GLint border = 0; // No border

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D,
	             level,
	             GL_RGBA,
	             mWidth,
	             mHeight,
	             border,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             image.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void
Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP_TO_EDGE, ...
{
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//apartado 35
void
Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer )
{
	if (mId == 0)
		init();

	mWidth = GLuint(width);
	mHeight = GLuint(height);

	glBindTexture(GL_TEXTURE_2D, mId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		mWidth, mHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glReadBuffer(buffer);

	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, mWidth, mHeight);

	glBindTexture(GL_TEXTURE_2D, 0);
}