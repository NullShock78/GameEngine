#ifndef  COLOR_VERTEX_H
#define COLOR_VERTEX_H

//Kyle St.Amant
//7/6/2016
//description here

#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings																								 
#include "vec3.hpp"																														 
//#include "gtc/matrix_transform.hpp"																												 
#pragma warning(pop) //return to previous warning state		


struct ColorVertex
{
public:
	glm::vec3 m_position;
	glm::vec3 m_color;


public:
	static unsigned GetPositionOffset()
	{
		return 0;
	};

	static unsigned GetColorOffset()
	{
		return sizeof(m_position);
	};
	
	static unsigned GetStrideBytes() 
	{
		return (sizeof(m_position) + sizeof(m_color));
	};
	static unsigned GetStride()
	{
		return 6;
	};

	static int GetNumPositions()
	{
		return 3;
	};
	static int GetNumCols()
	{
		return 3;
	};

};


#endif //def COLOR_VERTEX_H


