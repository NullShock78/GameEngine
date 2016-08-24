#include "TextureManager.h"
#include <fstream>
#include "GameLogger.h"
int TextureManager::m_currentImage;
const int TextureManager::MAX_IMAGES;
GLuint TextureManager::m_imageIDs[MAX_IMAGES];
char *  TextureManager::m_imageData[MAX_IMAGES];
ImageInfo TextureManager::m_imageInfos[MAX_IMAGES];
GLuint TextureManager::m_frameTexture;
char * TextureManager::m_frameData;
GLuint TextureManager::m_renderBuffer;
GLuint TextureManager::m_frameBuffer;
GLuint TextureManager::m_cubemap;
//DrawCallback TextureManager::DrawCallback{ nullptr };
//TODO: struct for image data

const int CUBEMAP_SIZE = 512;
const int F_BUFFER_SIZE = 512;//256,512
const int F_PIX_ROOT = 8;//4,8
//Not always the same as pix root
const int F_PIX_SIZE = 1;//4, 1
bool TextureManager::GenFrameBuffer()
{
	
	glGenTextures(1, &m_frameTexture);
	glBindTexture(GL_TEXTURE_2D, m_frameTexture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, F_BUFFER_SIZE, F_BUFFER_SIZE, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	//--------

	glGenFramebuffersEXT(1, &m_frameBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frameBuffer);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_frameTexture, 0);

	//----------
	glGenRenderbuffersEXT(1, &m_renderBuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_renderBuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, F_BUFFER_SIZE, F_BUFFER_SIZE);
	//----------

	//Attach
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_renderBuffer);
	
	//-------------

	GLenum status;
	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		break;
	default:
		GameLogger::Log(LogMsgType::cFatalError, " TextureManager::GenFrameBuffer(): GL_FRAMEBUFFER_STATUS bad.");
		return false;
	}
	//------------
	
	
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	return true;
}

bool TextureManager::BindToBuffer(GLuint /*texture*/)
{
	return false;
}

bool TextureManager::Initialize()
{
	m_currentImage = 0;
	//DrawCallback = RenderEngine::Draw;
	return true;
}

bool TextureManager::Shutdown()
{
	for (int j = 0; j < m_currentImage; ++j)
	{
		delete[] m_imageData[j];
	}

	if (m_frameBuffer != 0) {
		glDeleteTextures(1, &m_frameTexture);
		glDeleteRenderbuffersEXT(1, &m_renderBuffer);
		//Bind 0, which means render to back buffer, as a result, fb is unbound
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glDeleteFramebuffersEXT(1, &m_frameBuffer);
	}
	return true;
}

bool TextureManager::CreateRenderBuffer(int /*size_x*/, int /*size_y*/)
{
	return true;
}

bool TextureManager::Draw( glm::mat4 persp,glm::mat4 cam, int x, int y, glm::vec4 fbCol, glm::vec4 normCol, glm::mat4 option)
{
	//glBindRenderbuffer
	//To render to tex2d->
	glBindTexture(GL_TEXTURE_2D, m_frameTexture);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_frameBuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_renderBuffer);
	glClearColor(fbCol.r, fbCol.g, fbCol.b, fbCol.a);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//------------

	//int x, y;
	//x = glGetViewWidth

	glViewport(0, 0, F_BUFFER_SIZE, F_BUFFER_SIZE);

	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);

	//DrawCallback(persp, cam);
	if (!RenderEngine::Draw(persp, cam, option)) {
		return false;
	}

	GLubyte pixels[F_PIX_ROOT * F_PIX_ROOT * F_PIX_ROOT];
	glReadPixels(0, 0, F_PIX_SIZE, F_PIX_SIZE, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

	glEnable(GL_TEXTURE_2D);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);


	glClearColor(normCol.r, normCol.g, normCol.b, normCol.a);
	glViewport(0, 0, x, y);
	return true;

}


GLuint TextureManager::LoadGameBitmap(const char * imagePath)
{
	char header[54]{ 0 }; //54 byte header is standard for all bitmaps
	unsigned int dataPos; //Where data begins
	unsigned int width, height;
	unsigned int imageSize; //w*h*3

	//char * data;//RGB data

	std::ifstream fileStream;
	fileStream.open(imagePath, std::ios::binary);



	if (!fileStream.good()) 
	{ 
		fileStream.close();
		GameLogger::Log(LogMsgType::cFatalError, "TextureManager::LoadBitmap(): file [%s] could not be opened.", imagePath); 
		return 0; 
	}

	fileStream.seekg(0);
	fileStream.read(header, 54);
	if (!fileStream.good())
	{
		fileStream.close();
		GameLogger::Log(LogMsgType::cFatalError, "TextureManager::LoadBitmap(): file [%s] has bad header.", imagePath);
		return 0;
	}

	//printf("\n\n%s\n\n", header);

	if (header[0] != 'B' || header[1] != 'M')
	{
		fileStream.close();
		GameLogger::Log(LogMsgType::cFatalError, "TextureManager::LoadBitmap(): file [%s] not a correct bmp.", imagePath);
		return 0;
	}

	dataPos		= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	width		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);
	
	

	if (imageSize == 0) imageSize = width * height * 3;
	//imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;
	//dataPos = 54;
	m_imageData[m_currentImage] = new char[imageSize];

	
	//fileStream.read

	//fileStream.seekg(dataPos);
	fileStream.read(&m_imageData[m_currentImage][0], imageSize);
	if (!fileStream.good())
	{
		printf("FAIL----------------\n");
		return 0;
	}
	fileStream.close(); //Done with stream

	//printf("\n\n%s\n\n", m_imageData[m_currentImage]);
	glGenTextures(1, &m_imageIDs[m_currentImage]);

	glBindTexture(GL_TEXTURE_2D, m_imageIDs[m_currentImage]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR,GL_UNSIGNED_BYTE, m_imageData[m_currentImage]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	m_imageInfos[m_currentImage] = { width,height,imageSize,m_imageIDs[m_currentImage],imagePath };
	++m_currentImage;

	return m_imageIDs[m_currentImage-1];
}

//GLuint TextureManager::CreateCubemap()
//{
//
//
//	//TODO: generate textures, and draw to them while using framebuffer
//	glGenTextures(1, &m_cubemap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap);
//
//	
//
//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE,NULL);
//	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);//Back
//	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	//glTexImage2D()
//
//
//	return 0;
//}

//bool TextureManager::DrawToCubemap(Camera * cam, GLuint cubemap, int x, int y, glm::vec4 fbCol, glm::vec4 normCol)
//{
//	return false;
//}

GLuint TextureManager::GetIDByName(const char * path)
{
	for (int j = 0; j < m_currentImage; ++j)
	{
		if (strcmp(m_imageInfos[j].texturePath.c_str(), path) == 0) return m_imageInfos[j].texID;
	}

	return 0;
}

GLuint TextureManager::GetFrameBufferTexID()
{
	return m_frameTexture;
}

GLuint TextureManager::GetLoadedImage(int index)
{
	if (index >= m_currentImage || index <= 0) {
		GameLogger::Log(LogMsgType::cError, "TextureManager::GetLoadedImage(): index[%d] out of bounds", index); 
		return 0;
	}
	return m_imageIDs[index];
}

bool TextureManager::BindImage(int index)
{
	//glGenTextures(1, &m_imageIDs[index]);

	glBindTexture(GL_TEXTURE_2D, m_imageIDs[index]);


	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_BGR, GL_UNSIGNED_BYTE, m_imageData[m_currentImage]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return true;
}


//bool TextureManager::BindFB()
//{
//	//glGenTextures(1, &m_imageIDs[index]);
//
//	glBindTexture(GL_TEXTURE_2D, m_frameBuffer);
//
//	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_BGR, GL_UNSIGNED_BYTE, m_imageData[m_currentImage]);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//	return true;
//}

bool TextureManager::BindImageByID(GLuint id)
{
	//glGenTextures(1, &m_imageIDs[index]);

	glBindTexture(GL_TEXTURE_2D, id);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_BGR, GL_UNSIGNED_BYTE, m_imageData[m_currentImage]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return true;
}



char * TextureManager::GetData(int index)
{
	return m_imageData[index];
}
