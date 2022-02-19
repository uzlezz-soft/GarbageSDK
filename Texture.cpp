#include "Texture.h"
#include "Utils.h"
#include <stb/stb_image.h>
#include <fstream>
#include "AssetsManager.h"
#include <sstream>

garbage::Texture::~Texture()
{
	if (m_id != 0)
	{
		glDeleteTextures(1, &m_id);
	}
}

const garbage::AssetLoadResult garbage::Texture::LoadFromFile(std::string filename)
{
	try 
	{
		Asset::LoadFromFile(filename);
		m_originalFile = filename;

		std::ifstream in;
		in.open(m_originalFile, std::ios::binary);

		AssetLoadResult loadResult = LoadFileHeaders(in, "TEXTURE");

		if (loadResult != ALR_HeadersOk)
		{
			return loadResult;
		}

		auto ttype = static_cast<garbage::TType>(in.get());

		switch (ttype)
		{
		case garbage::TT_1D:
			m_type = GL_TEXTURE_1D;
			break;
		case garbage::TT_2D:
			m_type = GL_TEXTURE_2D;
			break;
		case garbage::TT_3D:
			m_type = GL_TEXTURE_3D;
			break;
		case garbage::TT_CubeMap:
			m_type = GL_TEXTURE_CUBE_MAP;
			break;
		default:
			break;
		}

		m_filtering = static_cast<garbage::TFiltering>(in.get());

		m_flipOnLoad = in.get();
		m_mipmaps = in.get();

		std::string data;
		std::stringstream ss;

		while (!in.eof())
		{
			char c = in.get();
			c ^= ASSET_XOR;

			ss << c;
		}
		in.close();

		data = ss.str();

		in.close();

		stbi_set_flip_vertically_on_load(m_flipOnLoad);

		unsigned char* bytes = stbi_load_from_memory((unsigned char*)data.c_str(), data.size(), &m_width, &m_height, &m_numColorChannels, 0);

		glGenTextures(1, &m_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(m_type, m_id);

		glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, m_filtering);
		glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, m_filtering);

		glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (m_numColorChannels == 4)
		{
			glTexImage2D
			(
				m_type,
				0,
				GL_RGBA,
				m_width,
				m_height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				bytes
			);
		}
		else if (m_numColorChannels == 3)
		{
			glTexImage2D
			(
				m_type,
				0,
				GL_RGBA,
				m_width,
				m_height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				bytes
			);
		}
		else if (m_numColorChannels == 1)
		{
			glTexImage2D
			(
				m_type,
				0,
				GL_RGBA,
				m_width,
				m_height,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				bytes
			);
		}
		else
		{
			m_id = 0;
			throw std::invalid_argument("Automatic Texture type recognition failed");
		}

		if (m_mipmaps)
		{
			glGenerateMipmap(m_type);
		}

		stbi_image_free(bytes);
		glBindTexture(m_type, 0);

		m_slot = GL_TEXTURE0;

		return ALR_Success;
	}
	catch (...)
	{
		return ALR_UnknownError;
	}
}

void garbage::Texture::Bind(unsigned int slot)
{
	m_slot = slot;
	glActiveTexture(GL_TEXTURE0 + m_slot);
	glBindTexture(m_type, m_id);
}

void garbage::Texture::Unbind()
{
	glBindTexture(m_type, 0);
	glActiveTexture(GL_TEXTURE0 + m_slot);
}

void garbage::Texture::UnbindAll()
{
	glBindTexture(GL_TEXTURE_1D, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_3D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

const garbage::TFiltering garbage::Texture::FilteringStringToTFiltering(std::string filtering) const
{
	if (filtering == "LINEAR")
	{
		return TFiltering::TF_Linear;
	}
	else if (filtering == "NEAREST")
	{
		return TFiltering::TF_Nearest;
	}
}

GLenum garbage::Texture::TFilteringToGLenum(TFiltering tfiltering) const
{
	switch (tfiltering)
	{
	case garbage::TFiltering::TF_Nearest:
		return GL_NEAREST;
		break;
	case garbage::TFiltering::TF_Linear:
		return GL_LINEAR;
		break;
	default:
		break;
	}

	return GL_NEAREST;
}

const garbage::TType garbage::Texture::TypeStringToTType(std::string type) const
{
	if (type == "TT1D")
	{
		return TType::TT_1D;
	}
	else if (type == "TT2D")
	{
		return TType::TT_2D;
	}
	else if (type == "TT3D")
	{
		return TType::TT_3D;
	}
	else if (type == "TTCUBEMAP")
	{
		return TType::TT_CubeMap;
	}
}

GLenum garbage::Texture::TTypeToGLenum(TType ttype) const
{
	switch (ttype)
	{
	case garbage::TType::TT_1D:
		return GL_TEXTURE_1D;
		break;
	case garbage::TType::TT_2D:
		return GL_TEXTURE_2D;
		break;
	case garbage::TType::TT_3D:
		return GL_TEXTURE_3D;
		break;
	case garbage::TType::TT_CubeMap:
		return GL_TEXTURE_CUBE_MAP;
		break;
	default:
		break;
	}

	return GL_TEXTURE_2D;
}