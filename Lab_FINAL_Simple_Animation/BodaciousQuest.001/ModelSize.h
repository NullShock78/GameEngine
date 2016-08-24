#pragma once
// Enum helps avoid magic numbers
enum class ModelSize
{
	Small = 256,   // use Ubyte for 256 indices or fewer
	Medium = 65536, // use Ushort for 257-65536 indices
	Large = 65537  // use Uint for more than 65536 indices 
};


