#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	GLuint ID;

	Shader(const std::string& shaderName);
	~Shader();

	GLuint load(GLenum type, const std::string& fileName) const;
	void checkSuccess(GLuint* shader) const;
	void use() const;

	// Uniforms
	void setMat4(const std::string& name, const glm::mat4& mat) const { 
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	};
	void setVec3(const std::string& name, float a, float b, float c) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), a, b, c);
	};
};

