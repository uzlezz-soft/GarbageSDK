#ifndef _garbage_shader
#define _garbage_shader

#include "GarbageSDK.h"
#include <glad/glad.h>
#include "Asset.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace garbage
{

	enum GSDK MasterShaderParameters
	{
		MSP_DiffuseMap = 1,
		MSP_SpecularReflections = 2,
		MSP_SpecularMap = 4,
		MSP_AlphaClip = 8
	};

	inline garbage::MasterShaderParameters GSDK operator|(garbage::MasterShaderParameters a, garbage::MasterShaderParameters b)
	{
		return static_cast<garbage::MasterShaderParameters>(static_cast<int>(a) | static_cast<int>(b));
	}

	enum GSDK ShaderCompileResult
	{
		SCR_Success, SCR_Failure
	};

	struct GSDK UMaterial
	{
		glm::vec4 Color;

		int DiffuseMap;
		int SpecularMap;

		bool UseDiffuseMap;
		bool UseSpecularReflections;
		bool UseSpeclarMap;

		float Specular;
		float Shininess;
	};

	class GSDK Shader : public Asset
	{
	public:

		Shader() = default;
		~Shader();

		virtual const AssetLoadResult LoadFromFile(std::string filename) override;
		const AssetLoadResult LoadFromMasterFile(std::string filename, MasterShaderParameters msp);

		const ShaderCompileResult Compile();

		void SetMaxNumberOfPointLights(int number);

		void Bind();
		static void Unbind();

		inline GLuint HashUniform(const std::string& name) const;

		void SetBool(const std::string& name, bool value) const;

		void SetInt(const std::string& name, int value) const;

		void SetFloat(const std::string& name, float value) const;

		void SetVec2(const std::string& name, glm::vec2 value) const;

		void SetVec2(const std::string& name, float x, float y) const;

		void SetVec3(const std::string& name, glm::vec3 value) const;

		void SetVec3(const std::string& name, float x, float y, float z) const;

		void SetVec4(const std::string& name, glm::vec4 value) const;

		void SetVec4(const std::string& name, float x, float y, float z, float w) const;

		void SetMat3(const std::string& name, glm::mat3 value) const;

		void SetMat4(const std::string& name, glm::mat4 value) const;

		void SetMaterial(UMaterial& material) const;

		Shader& operator=(const Shader& other) = delete;

	private:

		GLuint m_id = 0;

		std::string m_vertShader;
		std::string m_fragShader;

	};

}

#endif