#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "glad/glad.h"

#define UNLIT_SHADER 0
#define LIT_SHADER 1
#define LIGHT_SHADER 2

namespace GE
{
	struct ShaderStrings
	{
		const char* VertexShader;
		const char* FragmentShader;
	};

	class Shader
	{
	public:
		unsigned int id;



		Shader(std::string vertexPath, std::string fragmentPath);
		Shader(int ShaderType);
		~Shader();

		void Use();

		void SetInt(std::string name, int value);
		void SetFloat(std::string name, float value);

		void SetVec3(std::string name, float* value);
		void SetMat4(std::string name, float* value);
	private:
		ShaderStrings InitializeShader(int ShaderType);
	};
}

