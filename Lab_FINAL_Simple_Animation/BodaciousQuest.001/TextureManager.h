#ifndef  TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201)
#include "GL\glew.h"
#include "mat4x4.hpp"
#pragma warning(pop)
#include "RenderEngine.h"
#include "Perspective.h"
#include "Camera.h"
#include <string>
//typedef void(*DrawCallback)(glm::mat4, glm::mat4);


struct ImageInfo
{
	unsigned int w, h;
	unsigned int size;
	GLuint texID;
	std::string texturePath;
};


class TextureManager
{
private:

	//static DrawCallback DrawCallback;
	static int m_currentImage;
	//static int m_currentRenderBuff;
	static const int MAX_IMAGES = 10;
	//static Perspective m_persp;
	static GLuint m_frameBuffer;
	static GLuint m_renderBuffer;
	static GLuint m_frameTexture;
	static GLuint m_cubemap;
	

	static GLuint m_imageIDs[MAX_IMAGES];
	static char * m_imageData[MAX_IMAGES];
	static char * m_frameData;
	static ImageInfo m_imageInfos[MAX_IMAGES];
	
	static bool BindToBuffer(GLuint texture);
public:
	static bool GenFrameBuffer();
	//static bool Draw();
	static bool Initialize();
	static bool Shutdown();
	static bool CreateRenderBuffer(int size_x, int size_y);
	static bool Draw(glm::mat4 persp,glm::mat4 cam, int x, int y,glm::vec4 fbCol, glm::vec4 normCol,glm::mat4 option);

	static GLuint LoadGameBitmap(const char * imagePath);

	//static GLuint CreateCubemap();

	//static bool DrawToCubemap(Camera * cam, GLuint cubemap, int x, int y, glm::vec4 fbCol, glm::vec4 normCol);
	static GLuint GetIDByName(const char * path);
	static GLuint GetFrameBufferTexID();
	static GLuint GetLoadedImage(int index);
	static bool BindImage(int index);

	

	static bool BindImageByID(GLuint id);
	

	static char * GetData(int index);
};

#endif //TEXTURE_MANAGER_H
