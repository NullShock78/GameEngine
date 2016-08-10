#include "ShapeGenerator.h"


#pragma warning(push)  //Save state
#pragma warning(disable:4201) //disable warnings
#include "gtc/random.hpp"
#include "vec3.hpp"
#pragma warning(pop) //return to previous warning state
#include "ColorVertex.h"
#include "GraphicalObject.h"
#include "GameLogger.h"
#include "Mesh.h"
#include "GraphicalObject.h"
#include "RenderInfo.h"
#include "RenderEngine.h"
#include "ConfigReader.h"
#include "ModelSize.h"
#include "ShaderManager.h"
#include "TextureManager.h"
//Statics
Mesh ShapeGenerator::m_cubeMesh;
Mesh ShapeGenerator::m_pyramidMesh;
Mesh ShapeGenerator::m_debugSphereMesh;
const int ShapeGenerator::m_filesReadSize;
int ShapeGenerator::m_gridSizeVert;
int ShapeGenerator::m_gridSizeIndex;
Mesh ShapeGenerator::m_gridMesh;
Mesh ShapeGenerator::m_debugCubeMesh;
Mesh ShapeGenerator::m_planeMesh;
Mesh ShapeGenerator::m_specialCubeMesh;
char * ShapeGenerator::m_filesRead[100];


//
ColorVertex ShapeGenerator::sphereVerts[NUMSPHEREVERTS];
Facet3      ShapeGenerator::sphereFacets[NUMSPHEREFACETS];
GLuint    ShapeGenerator::sphereIndices[NUMSPHEREINDICES];






bool ShapeGenerator::Shutdown()
{
	for (int j = 0; j < m_filesReadSize; j++)
	{
		if (m_filesRead != nullptr)
		{
			delete[] m_filesRead[j];
		}
	}
	//delete[] m_filesRead[];
	GameLogger::Log(LogMsgType::cProcess ,"ShapeGenerator::Shutdown() successful");
	return true;
}


//Credit: Robert Lamb?



void ShapeGenerator::MakeSphere(GraphicalObject * gob, glm::vec3 color)
{
	
	//Very important
	gob->SetMesh(&m_debugSphereMesh);
	gob->SetDrawType(GL_LINES);
	gob->SetTint(color);
	//m_debugSphere.m_indices = sphereIndices; // no indices used at this time
	//m_debugSphere.m_numVertices = ;
	//m_debugSphere.m_numIndices = NUMSPHEREINDICES;
	//m_debugSphere.m_vertsPerPrimitive = 2;  // Make sure you use GL_LINES
	//return result;
}

void ShapeGenerator::BuildSphere(glm::vec3 color)
{

	int spFacets = GenerateSphere(sphereFacets, NUMSPHEREITERATIONS);
	for (GLint j = 0; j < spFacets; ++j)
	{
		sphereVerts[3 * j + 0].m_position = sphereFacets[j].p1;
		sphereVerts[3 * j + 0].m_color = color;

		sphereVerts[3 * j + 1].m_position = sphereFacets[j].p2;
		sphereVerts[3 * j + 1].m_color = color;

		sphereVerts[3 * j + 2].m_position = sphereFacets[j].p3;
		sphereVerts[3 * j + 2].m_color = color;

		sphereIndices[6 * j + 0] = 3 * j + 0;
		sphereIndices[6 * j + 1] = 3 * j + 1;
		sphereIndices[6 * j + 2] = 3 * j + 1;
		sphereIndices[6 * j + 3] = 3 * j + 2;
		sphereIndices[6 * j + 4] = 3 * j + 2;
		sphereIndices[6 * j + 5] = 3 * j + 0;
	}
}

void NormalizeXYZ(glm::vec3* p)
{
	float length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
	p->x /= length;
	p->y /= length;
	p->z /= length;
}

// Create a triangular facet approximation to a sphere
/*Return the number of facets created.
The number of facets will be (4^iterations) * 8
*/
int ShapeGenerator::GenerateSphere(Facet3* facets, int iterations)
{
	glm::vec3 p[6] =
	{
		glm::vec3(+0, +0, +1),
		glm::vec3(+0, +0, -1),
		glm::vec3(-1, -1, +0),
		glm::vec3(+1, -1, +0),
		glm::vec3(+1, +1, +0),
		glm::vec3(-1, +1, +0)
	};
	glm::vec3 pa, pb, pc;
	int numFacets = 0;
	int ntold;

	/* Create the level 0 object */
	float a = (float)(1 / sqrt(2.0));
	for (int i = 0; i < 6; i++)
	{
		p[i].x *= a;
		p[i].y *= a;
	}

	facets[0].p1 = p[0];
	facets[0].p2 = p[3];
	facets[0].p3 = p[4];
	facets[1].p1 = p[0];
	facets[1].p2 = p[4];
	facets[1].p3 = p[5];
	facets[2].p1 = p[0];
	facets[2].p2 = p[5];
	facets[2].p3 = p[2];
	facets[3].p1 = p[0];
	facets[3].p2 = p[2];
	facets[3].p3 = p[3];
	facets[4].p1 = p[1];
	facets[4].p2 = p[4];
	facets[4].p3 = p[3];
	facets[5].p1 = p[1];
	facets[5].p2 = p[5];
	facets[5].p3 = p[4];
	facets[6].p1 = p[1];
	facets[6].p2 = p[2];
	facets[6].p3 = p[5];
	facets[7].p1 = p[1];
	facets[7].p2 = p[3];
	facets[7].p3 = p[2];
	numFacets = 8;
	if (iterations < 1) return numFacets;

	/* Bisect each edge and move to the surface of a unit sphere */
	for (int it = 0; it < iterations; it++)
	{
		ntold = numFacets;
		for (int i = 0; i < ntold; i++)
		{
			pa.x = (facets[i].p1.x + facets[i].p2.x) / 2;
			pa.y = (facets[i].p1.y + facets[i].p2.y) / 2;
			pa.z = (facets[i].p1.z + facets[i].p2.z) / 2;
			pb.x = (facets[i].p2.x + facets[i].p3.x) / 2;
			pb.y = (facets[i].p2.y + facets[i].p3.y) / 2;
			pb.z = (facets[i].p2.z + facets[i].p3.z) / 2;
			pc.x = (facets[i].p3.x + facets[i].p1.x) / 2;
			pc.y = (facets[i].p3.y + facets[i].p1.y) / 2;
			pc.z = (facets[i].p3.z + facets[i].p1.z) / 2;

			NormalizeXYZ(&pa);
			NormalizeXYZ(&pb);
			NormalizeXYZ(&pc);

			facets[numFacets].p1 = facets[i].p1;
			facets[numFacets].p2 = pa;
			facets[numFacets].p3 = pc;

			numFacets++;
			facets[numFacets].p1 = pa;
			facets[numFacets].p2 = facets[i].p2;
			facets[numFacets].p3 = pb;

			numFacets++;
			facets[numFacets].p1 = pb;
			facets[numFacets].p2 = facets[i].p3;
			facets[numFacets].p3 = pc;

			numFacets++;
			facets[i].p1 = pa;
			facets[i].p2 = pb;
			facets[i].p3 = pc;
		}
	}

	return numFacets;
}


float ShapeGenerator::m_debug_cube_verts[24] =
{
	1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	-1.0f,1.0f,-1.0f,
	1.0f,1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
};
GLushort ShapeGenerator::m_debug_cube_indices[24] =
{
	0,1,0,3,0,5,
	1,2,1,4,
	2,3,2,7,
	3,6,
	4,5,4,7,
	5,6,
	6,7
};



 ColorVertex ShapeGenerator::cube_colorVerts[24] =
 {

	 //Front
	 { glm::vec3(1.0f,1.0f,1.0f)     ,glm::vec3(0.0f,0.0f,0.0f) }, 
	 { glm::vec3(-1.0f,1.0f,1.0f)    ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) }, 

	 { glm::vec3(1.0f,-1.0f,1.0f)    ,glm::vec3(0.0f,0.0f,0.0f) }, 
	//Back
	 { glm::vec3(-1.0f,1.0f,-1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,1.0f,-1.0f)    ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,-1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 //R
	 { glm::vec3(1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	//L
	 { glm::vec3(-1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(-1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 //T
	 { glm::vec3(1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(-1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 //Bottom
	 { glm::vec3(1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },


 };


 ColorVertex ShapeGenerator::special_cube_colorVerts[36] =
 {

	 //Front
	 { glm::vec3(1.0f,1.0f,1.0f)     ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,1.0f)    ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,1.0f,1.0f)     ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,1.0f)    ,glm::vec3(0.0f,0.0f,0.0f) },//3
	 //Back
	 { glm::vec3(-1.0f,1.0f,-1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },//4,5,6,4,6,7,
	 { glm::vec3(1.0f,1.0f,-1.0f)    ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,-1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,-1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,-1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },//7
	 //R
	 { glm::vec3(1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },//11
	 //L
	 { glm::vec3(-1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(-1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 //T
	 { glm::vec3(1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 //Bottom
	 { glm::vec3(1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(-1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
	 { glm::vec3(1.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },
 };

 GLuint ShapeGenerator::cube_indices[36]=
 {
	0,1,2,0,2,3,
	4,5,6,4,6,7,
	8,9,10,8,10,11,
	12,13,14,12,14,15,
	16,17,18,16,18,19,
	20,21,22,20,22,23
 };




 ColorVertex ShapeGenerator::pyramid_colorVerts[4] =
 {

	 { glm::vec3(-1.0f,-1.0f,1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(1.0f,-1.0f,1.0f)   ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(0.0f,-1.0f,-1.0f)  ,glm::vec3(0.0f,0.0f,0.0f) },

	 { glm::vec3(0.0f,1.0f,0.0f)    ,glm::vec3(0.0f,0.0f,0.0f) }
 };

 GLuint ShapeGenerator::pyramid_indices[12] =
 {
	0,1,3,
	1,2,3,
	2,0,3,
	2,1,0
 };

 ColorVertex ShapeGenerator::m_grid_color_verts[400] =
 {
	 {glm::vec3(0,0,0),glm::vec3(0,0,0)}
 };

 GLuint ShapeGenerator::m_grid_indices[404] =
 {
	 0
 };

 float ShapeGenerator::plane_texVerts[20] = {
	 -1.0f, -1.0f,0.0f ,0.001992f, 0.001992f,
	 1.0f, -1.0f, 0.0f , 0.998008f, 0.001992f,
	 1.0f,  1.0f, 0.0f ,0.998008f, 0.998008f,
	 -1.0f, 1.0f, 0.0f ,0.001992f, 0.998008f
 };

 GLuint ShapeGenerator::plane_indices[6] = {
	 0,1,2,
	 0,2,3
 };

 bool ShapeGenerator::Initialize(ConfigReader * config)
 {
	 const int numCubeVerts = 24;
	 const int numCubeIndices = 36;

	 const int numPyramidVerts = 4;
	 const int numPyramidIndices = 12;
	 bool loadCubeFirst = false;

	 config->GetBoolForKey("BodaciousQuest.LoadCubeFirst", loadCubeFirst, false);

	 m_planeMesh.SetData(plane_texVerts, 4, plane_indices, 6, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), VertexFormats::PositionTexture);
	 if (!RenderEngine::AddMesh(&m_planeMesh, 3, GL_TRIANGLES, VertexFormats::PositionTexture)) {
		 GameLogger::Log(LogMsgType::cFatalError, "Plane mesh failed to add.");
		 return false;
	 }

	 

	 m_debugCubeMesh.SetData(&m_debug_cube_verts, 8, m_debug_cube_indices, 24, IndexSizeInBytesEnum::Ushort,/*remove:*/ glm::vec3(0, 0, 0), VertexFormats::PositionOnly);
	 
	 
	 // m_debugCubeMesh.GetRenderInfo()->m_draw_mode = GL_LINES;
	 	 if (!RenderEngine::AddMesh(&m_debugCubeMesh, 0, GL_LINES, VertexFormats::PositionOnly))return false;
	 printf("AddMesh  m_debugCubeMesh successful\n");
	 //GameLogger::Log(LogMsgType::cDebug, "\n\n5/2=[%d]\n\n", 5 / 2);


	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	 //------------------------------------------------------SPECIAL CUBE LAB 10------------------------------------------------
	
	 m_specialCubeMesh.SetData(&special_cube_colorVerts, 36, nullptr, 0, IndexSizeInBytesEnum::Ushort,/*remove:*/ glm::vec3(0, 0, 0), VertexFormats::PositionColor);
	 SetAllColorsTo(&special_cube_colorVerts[0].m_color.r, 36, 6, glm::vec3(1.0f, 0.0f, 1.0f));
	 m_specialCubeMesh.GetRenderInfo()->m_indexed = false; //TODO: move
	 if (!RenderEngine::AddMesh(&m_specialCubeMesh, 1, GL_TRIANGLES, VertexFormats::PositionColor))return false;

	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------
	 //-------------------------------------------------------------------------------------------------------------------------


	 for (int j = 0; j < m_filesReadSize; j++)
	 {
		 m_filesRead[j] = nullptr;
	 }

	 m_cubeMesh.SetData((void*)cube_colorVerts, 24, cube_indices, 36,IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), VertexFormats::PositionColor);
	 SetColors(&cube_colorVerts[0].m_color.r, numCubeVerts, 6);
	 if (!RenderEngine::AddMesh(&m_cubeMesh,1,GL_TRIANGLES, VertexFormats::PositionColor)) return false;
	 printf("AddMesh  m_cubeMesh successful\n");


	// m_pyramidMesh.SetData(pyramid_colorVerts, numPyramidVerts, pyramid_indices, numPyramidIndices, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), VertexFormats::PositionColor);
	// SetColors(&pyramid_colorVerts[0].m_color.r, numPyramidVerts, 6);

	// if (!RenderEngine::AddMesh(&m_pyramidMesh)) return false;
	// printf("AddMesh  m_pyramidMesh successful\n");
	
	/* for (int j = 0; j < 40; ++j)
	 {
		 m_grid_indices[j] = j;
	 }*/




	BuildSphere(glm::vec3(1.0f, 0, 1.0f));
	printf("Build successful\n");
	m_debugSphereMesh.SetData(&sphereFacets, NUMSPHEREVERTS, sphereIndices, NUMSPHEREINDICES, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), VertexFormats::PositionOnly);


	 printf("SetData successful\n");
	 printf("NUMSPHEREVERTS: %d\n", NUMSPHEREVERTS);
	 printf("NUMSPHEREINDICES: %d\n", NUMSPHEREINDICES);

	 if (!RenderEngine::AddMesh(&m_debugSphereMesh,0,GL_LINES,VertexFormats::PositionOnly))return false;
	 printf("AddMesh  m_debugSphereMesh successful\n");



	 int gridSize = 0;

	 if(!config->GetIntForKey("BodaciousQuest.GridSize", gridSize))return false;
	 int max = 50;
	 if (gridSize > max)
	 {
		 GameLogger::Log(LogMsgType::cWarning, "gridSize exceeds max[%d], setting to max", max);
		 gridSize = max;
	 }

	 FillGrid(gridSize);

	// for (int j = 0; j < 200; ++j)
	 //{
	//	 m_grid_indices[j] = j;
	// }


	 //Grid has no indices as you can see
	 m_gridMesh.SetData(m_grid_color_verts,m_gridSizeVert, nullptr, 0,IndexSizeInBytesEnum::Uint,glm::vec3(),VertexFormats::PositionColor);
	 m_gridMesh.GetRenderInfo()->m_indexed = false;
     //m_gridMesh.GetRenderInfo()->m_draw_mode = GL_LINES;

	 if (!RenderEngine::AddMesh(&m_gridMesh,0,GL_LINES,VertexFormats::PositionColor)) return false;
	 //printf("AddMesh  m_gridMesh successful\n");
	
	

	
	 GameLogger::Log(LogMsgType::cProcess, "ShapeGenerator initialized successfully.");
	 return true;
 }


 void ShapeGenerator::MakeCube(GraphicalObject * gob)
 {
	 gob->SetMesh(&m_cubeMesh);
	
 }

 void ShapeGenerator::MakeSpecialCube(GraphicalObject * gob)
 {
	 gob->SetMesh(&m_specialCubeMesh);
 }

 void ShapeGenerator::MakeDebugCube(GraphicalObject * gob, glm::vec3 color)
 {
	 gob->SetMesh(&m_debugCubeMesh);
	 gob->SetDrawType(GL_LINES);
	 gob->SetTint(color);
 }

 void ShapeGenerator::MakePyramid(GraphicalObject * gob)
 {
	 gob->SetMesh(&m_pyramidMesh);
 }

 void ShapeGenerator::MakeTexturedPlane(GraphicalObject * gob)
 {
	 gob->SetMesh(&m_planeMesh);
	 gob->SetTexture(TextureManager::GetFrameBufferTexID());
 }

 void ShapeGenerator::MakeGrid(GraphicalObject * gob, glm::vec3 color)
 {
	// SetAllColorsTo(&grid_color_verts[3][size].m_color.r, (size * size), ColorVertex::GetStride(), color);
	 gob->SetMesh(&m_gridMesh);
	 gob->SetTint(color);
	 gob->SetDrawType(GL_LINES);
 }

 //MaxSize of 3
 void ShapeGenerator::FillGrid(int size)
 {
	float halfGrid = (float)size / 2.0f; //(sizeX % 2 == 0) ? ((float)sizeX / 2.0f) - 0.5f : (float)sizeX / 2.0f;
	 
	 int vertSize = 0;
	 for (int x = 0; x < size+1; ++x)
	 {
		 m_grid_color_verts[vertSize] = { glm::vec3((float)x - halfGrid,0.0f,-halfGrid),glm::vec3(0.0f,0.0f,0.0f) };
		 vertSize++;
		 m_grid_color_verts[vertSize] = { glm::vec3((float)x - halfGrid,0.0f,halfGrid),glm::vec3(0.0f,0.0f,0.0f) };
		 vertSize++;
	 }

	 for (int z = 0; z < size+1; ++z)
	 {
		 m_grid_color_verts[vertSize] = { glm::vec3(-halfGrid,0.0f,(float)z -halfGrid),glm::vec3(0.0f,0.0f,0.0f) };
		 vertSize++;
		 m_grid_color_verts[vertSize] = { glm::vec3( halfGrid,0.0f,(float)z -halfGrid),glm::vec3(0.0f,0.0f,0.0f) };
		 vertSize++;
	 }

	 m_gridSizeVert = vertSize;
	 int indices = 0;

	 for (GLint j = 0; j <((size *2) + (size *2)) + 4; ++j)
	 {
		 m_grid_indices[j] = j;
		 indices++;
	 }

	 m_gridSizeIndex = indices;

	 //for (int j = 0; j < size; ++j)
	 //{
		// for (int k =0; k < size; ++k)
		// {
		//	 m_grid_color_verts[vertNum] = { glm::vec3((float)j-offset,0.0f,(float)k)-offset,glm::vec3(1.0f,1.0f,1.0f) };
		// }
	 //}

 }

 //----------------------------------FOR LAB09------------------------------------
 //----------------------------------FOR LAB09------------------------------------
 //----------------------------------FOR LAB09------------------------------------
 //----------------------------------FOR LAB09------------------------------------
 //----------------------------------FOR LAB09------------------------------------
 //----------------------------------FOR LAB09------------------------------------


 bool ShapeGenerator::ReadSceneFile(const char * filename, GraphicalObject * gob, const char * texture)
 {
	 static int m_UniquefilesRead = -1;
	 bool fileExists = false;
	 int fileLoc = 0;
	 static Mesh * storedMeshes[m_filesReadSize]{ nullptr };

	 for (int j = 0; j < m_filesReadSize; j++)
	 {
		 if (m_filesRead[j] != nullptr) {
			 if (strcmp(m_filesRead[j], filename) == 0)
			 {
				 fileExists = true;
				 fileLoc = j;
				 break;
			 }
		 }

	 }

	 

	 if (!fileExists) {
		 if (m_UniquefilesRead < m_filesReadSize)
		 {
			 ++m_UniquefilesRead;
			 m_filesRead[m_UniquefilesRead] = _strdup(filename);
			 //strncpy_s(m_filesRead[m_UniquefilesRead],25,filename,25);
		 }
		 //if not already read-------------------


		 std::ifstream inputStream(filename, std::ios::binary | std::ios::in);

		 if (!inputStream)
		 {
			 //GameLogger::Log(LogMsgType::)
			 return false;
		 }

		 int datalen;// int renderInfolen;
		
		 inputStream.read(reinterpret_cast<char*>(&datalen), sizeof(datalen));
		 //inputStream.read(reinterpret_cast<char*>(&renderInfolen), sizeof(renderInfolen));
		 printf("--------------(%s)\nReading %d bytes\n", filename, datalen);

		 char * data = new char[datalen];

		 assert(data);
		 memset(data, 0, datalen);

		 //Set Mesh to public

		 inputStream.read(data, datalen);
		 inputStream.close();

		 Mesh * sceneMesh = reinterpret_cast<Mesh*>(data);
		/* if (sceneMesh->GetNumIndices() <= (int)ModelSize::Small)
		 {
			 sceneMesh->m_indexSizeEnum = IndexSizeInBytesEnum::Ubyte;
		 }
		 
		 else if (sceneMesh->GetNumIndices() <= (int)ModelSize::Medium)
		 {
			 sceneMesh->m_indexSizeEnum = IndexSizeInBytesEnum::Ushort;
		 }
		 else 
		 {
			 sceneMesh->m_indexSizeEnum = IndexSizeInBytesEnum::Uint;
		 }*/
		 char * r = data;
		 r += sizeof(*sceneMesh);
		
		 RenderInfo * sceneRenderInfo = reinterpret_cast<RenderInfo*>(r);

		 sceneMesh->m_renderInfo = *sceneRenderInfo;
		 char * p = data;
		 p += sizeof(*sceneMesh) + sizeof(*sceneRenderInfo);
		 sceneMesh->m_mesh = reinterpret_cast<float*>(p);

		 p += sceneMesh->GetVertSizeInBytes();

		 IndexSizeInBytesEnum temp_isb = sceneMesh->GetIndexSizeEnum();



		 //TODO: change

		 switch (temp_isb)
		 {
		 case IndexSizeInBytesEnum::Ubyte:
			 sceneMesh->m_indices = reinterpret_cast<GLubyte*>(p);
			 break;
		 case IndexSizeInBytesEnum::Ushort:
			 sceneMesh->m_indices = reinterpret_cast<GLushort*>(p);
			 break;
		 case IndexSizeInBytesEnum::Uint:
			 sceneMesh->m_indices = reinterpret_cast<GLuint*>(p);
			 break;
		 default:
			 GameLogger::Log(LogMsgType::cProgrammerError, "ShapeGenerator::ReadSceneFile(): IndexSizeInBytesEnum not set for [%s]", filename);
			 return false;
			 break;
		 }

		
		 
		 if (!RenderEngine::AddMesh(sceneMesh, sceneMesh->m_renderInfo.m_wroteShader, sceneMesh->m_renderInfo.m_draw_mode, sceneMesh->m_renderInfo.m_vertexFormat)) return false;
		// if (!RenderEngine::AddMesh(sceneMesh, 4, sceneMesh->m_renderInfo.m_draw_mode, sceneMesh->m_renderInfo.m_vertexFormat)) return false;

		 
		 sceneMesh->m_renderInfo.m_indexed = sceneMesh->m_secondIndexed;
		 

		/* GLfloat * m_buffer = new GLfloat[500];
		 glGetBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, 500, m_buffer);*/


		 /*for (int j = 0; j < 500; j++)
		 {

		 printf("Val[%d]: %f\n",j ,*m_buffer);
		 ++m_buffer;
		 }
		 delete[] m_buffer;*/
		 

		 printf("--------------------------------\n");

		 //-------------------------------------------------------------

		 //All of the above should only happen the first time this file is read,
		 //After that, the mesh is simply inserted into the passed graphical object.
		 storedMeshes[m_UniquefilesRead] = sceneMesh;
		
	 gob->SetMesh(sceneMesh);//Warning! this is the only owner of this object
							 //Must be deleted by owner!
	 //^done.
	 gob->SetHasData(true);

	 if (strcmp(texture, "none") != 0) {
		 if (TextureManager::GetIDByName(texture) == 0)
		 {
			 if (TextureManager::LoadGameBitmap(texture) == 0) 
			 {
				 return false;
			 }
			 
		 }
		 gob->SetTexture(TextureManager::GetIDByName(texture));
	 }

	 GameLogger::Log(LogMsgType::Info, "ShapeGenerator::ReadSceneFile(): Added new scene [%s] successfully.", filename);
	 }
	 else
	 {
		 gob->SetMesh(storedMeshes[fileLoc]);
		 if (strcmp(texture, "none") != 0) {
			 if (TextureManager::GetIDByName(texture) == 0)
			 {
				 if (TextureManager::LoadGameBitmap(texture) == 0)
				 {
					 return false;
				 }
				
			 }
			 gob->SetTexture(TextureManager::GetIDByName(texture));
		 }
	 }



	 return true;


 }

 //-----------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------
 //-----------------------------------------------------------------------------------
 void ShapeGenerator::SetColors(float * color0, int numVerts, int stride)
 {
	 srand((unsigned)time(0));//Init rand

	 float * colorPtr = color0;
	 for (int j = 0; j < numVerts; ++j)
	 {
		float * colorPartPtr = colorPtr;
		for (int k = 0; k < 3; ++k)
		{
			*colorPartPtr = glm::linearRand(0.01f, 1.0f);
			++colorPartPtr;
		}
		colorPtr += stride;
	 }

 }

 void ShapeGenerator::SetAllColorsTo(float * color0, int numVerts, int stride, glm::vec3 color)
 {

	 float * colorPtr = color0;
	 for (int j = 0; j < numVerts; ++j)
	 {
		 float * colorPartPtr = colorPtr;
		 float * colorToCopyPtr = &color.r;
		 for (int k = 0; k < 3; ++k)
		 {
	
			*colorPartPtr = *colorToCopyPtr;
			 ++colorPartPtr;
			 ++colorToCopyPtr;
		 }
		 colorPtr += stride;
	 }

 }
