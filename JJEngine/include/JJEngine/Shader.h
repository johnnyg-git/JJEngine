#pragma once

#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace JJEngine {
	class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		GLint GetUniformLocation(const char* name);

		void Use() const;
		void Load();
		void Load(const char* vertexPath, const char* fragmentPath);

		void SetUniform1i(const char* name, int value);
		void SetUniform2i(const char* name, int x, int y);
		void SetUniform3i(const char* name, int x, int y, int z);
		void SetUniform4i(const char* name, int x, int y, int z, int w);

		void SetUniform1f(const char* name, float value);
		void SetUniform2f(const char* name, float x, float y);
		void SetUniform3f(const char* name, float x, float y, float z);
		void SetUniform4f(const char* name, float x, float y, float z, float w);

		void SetUniformVec2(const char* name, const glm::vec2& value);
		void SetUniformVec3(const char* name, const glm::vec3& value);
		void SetUniformVec4(const char* name, const glm::vec4& value);

		const char* GetVertexPath() const { return m_vertexPath; }
		const char* GetFragmentPath() const { return m_fragmentPath; }

	private:
		const char* m_vertexPath;
		const char* m_fragmentPath;

		GLuint m_rendererID;
		std::unordered_map<const char*, GLint> m_uniformLocationCache;
	};
}