#ifndef  SHAPE_GENERATOR
#define SHAPE_GENERATOR

//Kyle St.Amant
//7/7/2016
//description here
//#include "GraphicalObject"
#include "ColorVertex.h"
#include "Mesh.h"
class GraphicalObject;
class ConfigReader;



typedef struct { glm::vec3 p1, p2, p3; } Facet3; // 3 points per Facet
enum SphereDefines
{
	NUMSPHEREITERATIONS = 3,  // if you change this, you must change the next one too!!!
	FOUR_TO_NUM_ITERATIONS = 64,    // 4^numIterations, ie, 4 to the power of
	NUMSPHEREFACETS = FOUR_TO_NUM_ITERATIONS * 8, // 4^numIterations * 8
	NUMSPHEREVERTS = 3 * NUMSPHEREFACETS, // 3 verts per facet/triangle
	NUMSPHEREINDICES = 2 * NUMSPHEREVERTS   // two indices per point
};
class ShapeGenerator
{


	
	
	public:
		static void MakeSphere(GraphicalObject * gob, glm::vec3 color = glm::vec3(1.0f,0.0f,1.0f));
	private:
		static int  GenerateSphere(Facet3 * facets, int iterations);
		static void BuildSphere(glm::vec3 color);

		

		static ColorVertex sphereVerts[NUMSPHEREVERTS];
		static Facet3      sphereFacets[NUMSPHEREFACETS];
		static GLuint    sphereIndices[NUMSPHEREINDICES];

public:

	static bool Initialize(ConfigReader * config);

	//static float * GetCubeVerts(int &numVerts);
	//static float * GetTriVerts(int &numVerts);
	//static float * GetHouseVerts(int &numVerts);
	static void MakeCube(GraphicalObject * gob);
	static void MakeSpecialCube(GraphicalObject * gob);
	static void MakeDebugCube(GraphicalObject * gob, glm::vec3 color);
	static void MakePyramid(GraphicalObject * gob);
	static void MakeTexturedPlane(GraphicalObject * gob);

	static void MakeGrid(GraphicalObject * gob, glm::vec3 color);
		//static float * GetCubeVertPositions(int &numVerts);
		//static float * GetCubeVertCols(int &numVerts);
	static bool Shutdown();
	static bool ReadSceneFile(const char * filename, GraphicalObject * gob, const char * texture = "none");

private:

	static const int m_filesReadSize = 100;
	//static float cubeVerts[36];
	static char * m_filesRead[m_filesReadSize];
	static void FillGrid(int size);

	static Mesh m_cubeMesh;
	static Mesh m_specialCubeMesh;
	static Mesh m_pyramidMesh;
	static Mesh m_gridMesh;
	static Mesh m_debugSphereMesh;
	static Mesh m_debugCubeMesh;
	static Mesh m_planeMesh;
	//static Mesh m_debuglineMesh;

	static int m_gridSizeVert;
	static int m_gridSizeIndex;
	static ColorVertex m_grid_color_verts[400];
	static GLuint m_grid_indices[404];

	static ColorVertex cube_colorVerts[24];
	static GLuint cube_indices[36];
	static ColorVertex special_cube_colorVerts[36];
	static ColorVertex pyramid_colorVerts[4];
	static GLuint pyramid_indices[12];


	static float m_debug_cube_verts[24];
	static GLushort m_debug_cube_indices[24];


	static float plane_texVerts[20];
	static GLuint plane_indices[6];

	static void SetColors(float * color0, int numVerts, int stride);
	static void SetAllColorsTo(float * color0, int numVerts, int stride,glm::vec3 color);
};

#endif //def SHAPE_GENERATOR


