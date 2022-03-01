#ifndef _garbage_texture
#define _garbage_texture

#include "GarbageSDK.h"
#include <glad/glad.h>
#include "Asset.h"

namespace garbage
{

	enum GSDK TFiltering
	{
		TF_Nearest, TF_Linear
	};

	enum GSDK TType
	{
		TT_1D, TT_2D, TT_3D, TT_CubeMap
	};

	class GSDK Texture : public Asset
	{
	public:

		Texture() = default;
		~Texture();

		virtual const AssetLoadResult LoadFromFile(std::string filename) override;
		
		void Bind(unsigned int slot);
		void Unbind();

		static void UnbindAll();

		Texture& operator=(const Texture& other) = delete;

	private:

		GLuint m_id = 0;
		//std::string m_originalFile;

		GLenum m_type = GL_TEXTURE_2D;
		GLenum m_filtering = GL_NEAREST;

		int m_width = 0;
		int m_height = 0;
		int m_numColorChannels = 0;

		bool m_flipOnLoad = true;
		bool m_mipmaps = true;

		GLenum m_slot = GL_TEXTURE0;

		const TFiltering FilteringStringToTFiltering(std::string filtering) const;
		GLenum TFilteringToGLenum(TFiltering tfiltering) const;

		const TType TypeStringToTType(std::string type) const;
		GLenum TTypeToGLenum(TType ttype) const;

	};

}

#endif
