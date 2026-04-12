#include "IndexedBox.h"
#include "IndexMesh.h"

IndexedBox::IndexedBox(GLdouble length)
	: ColorMaterialEntity(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))
{
	//mMesh = IndexMesh::generateIndexedBox8(length);
 mMesh = IndexMesh::generateIndexedBox(length);
}
