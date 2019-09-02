#pragma once

#include <fstream>
#include <vector>
#if defined(XWIN_WIN32)
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <iostream>

#include "glad/glad.h"

 // Get the current exe directory
inline std::string getAppDirectory()
{
	std::string out;
	char pBuf[2048];
#ifdef XWIN_WIN32
	_getcwd(pBuf, 2048);
	out = pBuf;
	out += "\\";
#else
	getcwd(pBuf, 2048);
	out = pBuf;
	out += "/";
#endif
	return out;
}

// Read a target file
inline std::vector<char> readFile(const std::string& path)
{
	std::ifstream file(path, std::ios::ate | std::ios::binary);
	bool exists = (bool)file;

	if (!exists || !file.is_open())
	{
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

// Check if a shader has compiled correctly and output error if not
inline bool checkShaderCompilation(GLuint shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* errorLog = new char[maxLength]();
		glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);
		glDeleteShader(shader);
		std::cout << errorLog;
		delete errorLog;
		return false;
	}
	return true;
}

// Check if a program was able to link correctly
inline bool checkProgramCompilation(GLuint program)
{
	GLint result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (result != GL_TRUE)
	{
		std::cout << "Program failed to link.";
		return false;
	}

	return true;
}   