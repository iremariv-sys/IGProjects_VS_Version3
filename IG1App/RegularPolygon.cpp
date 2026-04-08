#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(GLuint num, GLdouble r , const glm :: vec4& color):SingleColorEntity(color) 
{
	mMesh = Mesh::generateRegularPolygon(num, r);
	
}
