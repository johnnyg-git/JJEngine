#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "JJEngine/Shader.h"

using namespace JJEngine;

std::string GetFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	return {};
}

GLuint CompileShader(const char* source, GLenum type)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
		std::cout << message << "\n";
		glDeleteShader(id);
		return -1;
	}

	return id;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
{
	Load();
}

Shader::~Shader()
{
	glDeleteProgram(m_rendererID);
}

GLint Shader::GetUniformLocation(const char* name)
{
	if (m_uniformLocationCache.contains(name))
		return m_uniformLocationCache[name];

	int location = glGetUniformLocation(m_rendererID, name);
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!\n";

	m_uniformLocationCache[name] = location;
	return location;
}

void Shader::Use() const
{
	glUseProgram(m_rendererID);
}

void Shader::Load()
{
	if(m_rendererID != 0)
		glDeleteProgram(m_rendererID);

	std::string vertexCode = GetFileContents(m_vertexPath);
	std::string fragmentCode = GetFileContents(m_fragmentPath);

	if(vertexCode.empty() || fragmentCode.empty())
	{
		std::cout << "Error: Shader file not found\n";
		return;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;

	vertex = CompileShader(vShaderCode, GL_VERTEX_SHADER);
	fragment = CompileShader(fShaderCode, GL_FRAGMENT_SHADER);

	if(vertex == 0 || fragment == 0)
	{
		std::cout << "Error: Shader compilation failed\n";
		return;
	}

	m_rendererID = glCreateProgram();
	glAttachShader(m_rendererID, vertex);
	glAttachShader(m_rendererID, fragment);
	glLinkProgram(m_rendererID);

	int success;
	char infoLog[512];
	glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_rendererID, 512, nullptr, infoLog);
		std::cout << "Error: Shader program linking failed\n" << infoLog << "\n";
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	std::cout << "Shader loaded successfully\n";
}

void Shader::Load(const char* vertexPath, const char* fragmentPath)
{
	m_vertexPath = vertexPath;
	m_fragmentPath = fragmentPath;
	Load();
}

void Shader::SetUniform1i(const char* name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform2i(const char* name, int v0, int v1)
{
	glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3i(const char* name, int v0, int v1, int v2)
{
	glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4i(const char* name, int v0, int v1, int v2, int v3)
{
	glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1f(const char* name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform2f(const char* name, float v0, float v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3f(const char* name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformVec2(const char* name, const glm::vec2& value)
{
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniformVec3(const char* name, const glm::vec3& value)
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniformVec4(const char* name, const glm::vec4& value)
{
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}
