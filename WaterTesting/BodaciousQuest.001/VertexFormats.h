#ifndef VERTEX_FORMATS_H
#define VERTEX_FORMATS_H
enum class VertexFormats
{
	HasPosition = 1,
	HasColor = 2,
	HasTexture = 4,
	HasNormal = 8,
	PositionOnly = HasPosition,
	PositionColor = HasPosition | HasColor,
	PositionTexture = HasPosition | HasTexture,
	PositionNormal = HasPosition | HasNormal,
	PositionColorNormal = HasPosition | HasColor | HasNormal,
	PositionTextureNormal = HasPosition | HasTexture | HasNormal,
	PositionColorTexture = HasPosition | HasColor | HasTexture,
	PositionColorTextureNormal = HasPosition | HasColor | HasTexture | HasNormal
};

class VertStride
{
public:
	static int GetSize(VertexFormats v)
	{
		switch (v)
		{
		case VertexFormats::PositionOnly:
			return 3;
			//break;
		case VertexFormats::PositionColor:
			return 6;
			//break;
		case VertexFormats::PositionTexture:
			return 5;
		case VertexFormats::PositionNormal:
			return 6;
		case VertexFormats::PositionColorNormal:
			return 9;
		case VertexFormats::PositionTextureNormal:
			return 8;
		case VertexFormats::PositionColorTexture:
			return 8;
		case VertexFormats::PositionColorTextureNormal:
			return 11;
		default:
			return 0;

		}
	}
};




#endif //VERTEX_FORMATS_H