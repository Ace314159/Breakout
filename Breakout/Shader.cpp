#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

#include "Shader.h"


Shader::Shader(const std::string& shaderName) {
	GLuint vertexShader = load(GL_VERTEX_SHADER, shaderName + ".vert");
	GLuint fragmentShader = load(GL_FRAGMENT_SHADER, shaderName + ".frag");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	checkSuccess(nullptr);
}

Shader::~Shader() {
	glDeleteProgram(ID);
}


GLuint Shader::load(GLenum type, const std::string& fileName) const {
	std::ifstream file(fileName);
	if(!file.is_open()) {
		std::cerr << "Unable to read shader at" << fileName << std::endl;
		throw std::runtime_error("");
	}

	std::ostringstream sstr;
	sstr << file.rdbuf();
	std::string srcStr = sstr.str();
	const GLchar* src = srcStr.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	checkSuccess(&shader);
	return shader;
}

void Shader::checkSuccess(GLuint* shader) const {
	int success;
	char infoLog[512];
	if(shader != nullptr) {
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	} else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
	}
	if(!success) {
		if(shader != nullptr) {
			glGetShaderInfoLog(*shader, 512, nullptr, infoLog);
			std::cerr << "Shader Error: " << infoLog << std::endl;
		} else {
			glGetProgramInfoLog(ID, 512, nullptr, infoLog);
			std::cerr << "Program Error: " << infoLog << std::endl;
		}
		throw std::runtime_error("");
	}
}

void Shader::use() const {
	glUseProgram(ID);
}
