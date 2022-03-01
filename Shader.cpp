#include "Shader.h"
#include <iostream>
#include <fstream>
#include "Vector3.h"

#ifndef NDEBUG
#include "Clock.h"
#endif

garbage::Shader::~Shader()
{
	if (m_id != 0)
	{
		glDeleteProgram(m_id);
	}
}


std::string Internal_PreprocessInclude(std::ifstream& in)
{
	std::string out;

	std::string includeDirective;
	for (uint8_t i = 0; i < 8; i++) includeDirective += in.get() ^ ASSET_XOR;
	if (includeDirective != "INCLUDE(") return "ALR_SyntaxError";

	std::string fileToInclude;
	if (in.eof()) return "ALR_UnexceptedEndOfFile";
	do
	{
		char c2 = in.get() ^ ASSET_XOR;
		if (c2 == ')') break;
		fileToInclude += c2;

		if (in.eof()) return "ALR_UnexceptedEndOfFile";
	} while (true);

	if (fileToInclude.empty()) return "ALR_SyntaxError";

	try {
		std::string fileToIncludeContent = garbage::utils::GetFileContents(fileToInclude.c_str());
		out += fileToIncludeContent + "\n";
	}
	catch (...) { return "ALR_FileNotFound"; }

	return out;
}

const garbage::AssetLoadResult garbage::Shader::LoadFromFile(std::string filename)
{
	try
	{
#ifndef NDEBUG
		Clock loadClock;
#endif

		m_originalFile = filename;

		std::ifstream in;
		in.open(m_originalFile, std::ios::binary);

		AssetLoadResult loadResult = LoadFileHeaders(in, "SHADER");

		if (loadResult != ALR_HeadersOk)
		{
			return loadResult;
		}

		int vertShaderLength = 0;
		in >> vertShaderLength;

		std::string vertShader;
		for (int i = 0; i < vertShaderLength; i++)
		{
			char c = in.get() ^ ASSET_XOR;

			if (c == '@')
			{
				std::string result = Internal_PreprocessInclude(in);
				AssetLoadResult alr = ENUM_StringToALR(result);
				if (alr == ALR_None) vertShader += result;
				else return alr;
			}
			else vertShader += c;
		}

		std::cout << "\n";

		int fragShaderLength = 0;
		in >> fragShaderLength;

		std::string fragShader;
		for (int i = 0; i < fragShaderLength; i++)
		{
			char c = in.get() ^ ASSET_XOR;
			if (c == '@')
			{
				std::string result = Internal_PreprocessInclude(in);
				AssetLoadResult alr = ENUM_StringToALR(result);
				if (alr == ALR_None) fragShader += result;
				else return alr;
			}
			else fragShader += c;
		}

		// irn, but without this shit it wont work for some reason
		fragShader = garbage::utils::Replace(fragShader, "eeeeeeeeeeeeeeeeeeeeeeeeeee", "");

		in.close();

		m_vertShader = vertShader;
		m_fragShader = fragShader;

#ifndef NDEBUG
		std::cout << "DEBUG: Shader " << filename << " took " << loadClock.Restart() * 1000.f << " ms to load." << std::endl;
#endif

		return ALR_Success;
	}
	catch (...)
	{
		return ALR_UnknownError;
	}
}

const garbage::AssetLoadResult garbage::Shader::LoadFromMasterFile(std::string filename, MasterShaderParameters msp)
{
	AssetLoadResult loadResult = LoadFromFile(filename);

	if (loadResult != ALR_Success)
	{
		return loadResult;
	}

	std::string vert_replaces;
	std::string frag_replaces;

	if (msp & MSP_DiffuseMap)
	{
		frag_replaces.append("\n#define DIFFUSE_MAP");
	}

	if (msp & MSP_SpecularReflections)
	{
		frag_replaces.append("\n#define SPECULAR_REFLECTIONS");

		if (msp & MSP_SpecularMap)
		{
			frag_replaces.append("\n#define SPECULAR_MAP");
		}
	}

	if (msp & MSP_AlphaClip)
	{
		frag_replaces.append("\n#define ALPHA_CLIP");
	}

#ifndef NDEBUG
	std::cout << "Vert shader replaces:" << vert_replaces << "\nFrag shader replaces: " << frag_replaces << std::endl;
#endif

	m_vertShader = garbage::utils::Replace(m_vertShader, "{DEFINES}", vert_replaces);
	m_fragShader = garbage::utils::Replace(m_fragShader, "{DEFINES}", frag_replaces);

	return ALR_Success;
}

void garbage::Shader::SetMaxNumberOfPointLights(int number)
{
	m_fragShader = garbage::utils::Replace(m_fragShader, "{MAX_NUMBER_OF_POINT_LIGHTS}", std::to_string(number));
}

const garbage::ShaderCompileResult garbage::Shader::Compile()
{
	const char* vertexSource = m_vertShader.c_str();
	const char* fragmentSource = m_fragShader.c_str();

	int success;

#ifndef NDEBUG
	char infoLog[512];
#endif

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// print compile errors if any
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
#ifndef NDEBUG
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
#endif
		return SCR_Failure;
	};

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
#ifndef NDEBUG
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
#endif
		return SCR_Failure;
	};

	m_id = glCreateProgram();

	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);

	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
#ifndef NDEBUG
		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
#endif
		m_id = 0;
		return SCR_Failure;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return SCR_Success;
}

void garbage::Shader::Bind()
{
	glUseProgram(m_id);
}

void garbage::Shader::Unbind()
{
	glUseProgram(0);
}

GLuint garbage::Shader::HashUniform(const std::string& name) const { return glGetUniformLocation(m_id, name.c_str()); }

void garbage::Shader::SetBool(const std::string& name, bool value) const { glUniform1i(HashUniform(name), value); }

void garbage::Shader::SetInt(const std::string& name, int value) const { glUniform1i(HashUniform(name), value); }

void garbage::Shader::SetFloat(const std::string& name, float value) const { glUniform1f(HashUniform(name), value); }

void garbage::Shader::SetVec2(const std::string& name, glm::vec2 value) const { glUniform2fv(HashUniform(name), 1, glm::value_ptr(value)); }

void garbage::Shader::SetVec2(const std::string& name, float x, float y) const { glUniform3fv(HashUniform(name), 1, glm::value_ptr(glm::vec2(x, y))); }

void garbage::Shader::SetVec3(const std::string& name, glm::vec3 value) const { glUniform3fv(HashUniform(name), 1, glm::value_ptr(value)); }

void garbage::Shader::SetVec3(const std::string& name, float x, float y, float z) const { glUniform3fv(HashUniform(name), 1, glm::value_ptr(glm::vec3(x, y, z))); }

void garbage::Shader::SetVec4(const std::string& name, glm::vec4 value) const { glUniform4fv(HashUniform(name), 1, glm::value_ptr(value)); }

void garbage::Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const { glUniform4fv(HashUniform(name), 1, glm::value_ptr(glm::vec4(x, y, z, w))); }

void garbage::Shader::SetMat3(const std::string& name, glm::mat3 value) const { glUniformMatrix3fv(HashUniform(name), 1, GL_FALSE, glm::value_ptr(value)); }

void garbage::Shader::SetMat4(const std::string& name, glm::mat4 value) const { glUniformMatrix4fv(HashUniform(name), 1, GL_FALSE, glm::value_ptr(value)); }

void garbage::Shader::SetMaterial(UMaterial& material) const
{
	SetVec4("material.color", material.Color);

	if (material.UseDiffuseMap)
	{
		SetInt("material.diffuse", material.DiffuseMap);
	}

	if (material.UseSpecularReflections)
	{
		if (material.UseSpeclarMap)
		{
			SetInt("material.specular", material.SpecularMap);
		}
		else
		{
			SetFloat("material.specular", material.Specular);
		}

		SetFloat("material.shininess", material.Shininess);
	}
}
