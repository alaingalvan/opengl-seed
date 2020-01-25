#include "Triangle.h"
#include "Utils.h"

#ifndef __EMSCRIPTEN__
#include "glad/glad.h"
#endif

#define EMBED_SHADERS 1

/**************************************************************
 * 🌎 Globals
 **************************************************************/

// 🧚🏻 Shader Strings

const char* vertShader = R"(
#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 vColor;

void main()
{
    vColor = inColor;
    gl_Position = vec4(inPosition, 1.0);
}
)";

const char* fragShader = R"(
#version 410

precision mediump float;
precision highp int;

layout(location = 0) in highp vec3 vColor;

layout(location = 0) out highp vec4 outFragColor;


void main()
{
    outFragColor = vec4(vColor, 1.0);
}
)";

 // 📈 Triangle Buffer Data
float positions[3 * 3] = { 1.0f,  -1.0f,  0.0f,
						  -1.0f,  -1.0f,  0.0f,
						   0.0f, 1.0f,  0.0f };

float colors[3 * 3] = { 1.0f,  0.0f,  0.0f,
					    0.0f,  1.0f,  0.0f,
					    0.0f,  0.0f,  1.0f };

GLuint indexBufferData[3] = { 0, 1, 2 };


// GLHandles. Any value > 0 means the handle has been created.
GLuint positionVBO = 0;
GLuint colorVBO = 0;
GLuint ibo = 0;
GLuint vs = 0;
GLuint fs = 0;
GLuint vbo = 0;
GLuint program = 0;
GLuint vao = 0;

/**************************************************************
 * 🔺 Create, Draw, and Destroy
 **************************************************************/

bool loadOpenGL()
{
	#if !defined(XWIN_WASM)
	if (!gladLoadGL())
	{
		std::cout << "Failed to load OpenGL.";
		return false;
	}
	#endif
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cout << "OpenGL started with error code: " << err;
		return false;
	}
	
    int majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    std::cout << "OpenGL Version: " << majorVersion << "." << minorVersion
              << std::endl;

	// Most OpenGL Apps will want to enable these settings:

	// 🖍️ Set default clear color to gray ⚫
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// 🔺 Enable depth testing
	glEnable(GL_DEPTH_TEST);
	// <= Set Depth Test Function
	glDepthFunc(GL_LEQUAL);

	// Enable anything else like blend modes, etc...

	return true;
}

bool createTriangle()
{
	// ⚪ Create VBO
	glGenBuffers(1, &positionVBO);
	// 🩹 Bind VBO to GLState
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	// 💾 Push data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, positions, GL_STATIC_DRAW);

	// ⚪ Create VBO
	glGenBuffers(1, &colorVBO);
	// 🩹 Bind VBO to GLState
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	// 💾 Push data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, colors, GL_STATIC_DRAW);

	// ⚪ Create IBO
	glGenBuffers(1, &ibo);
	// 🩹 Bind IBO to GLState
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	// 💾 Push data to IBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3, indexBufferData, GL_STATIC_DRAW);

	// 📂 Load Vertex Shader String
#ifndef EMBED_SHADERS
	std::string vsPath = getAppDirectory() + "assets/shaders/triangle.vert";
	std::vector<char> vertShaderCode = readFile(vsPath);
	const char* vertString = vertShaderCode.data();
	int vertStringSize = static_cast<int>(vertShaderCode.size());
#else
	const char* vertString = vertShader;
	int vertStringSize = strlen(vertShader);
#endif
	// ⚪ Create Shader Data Structure
	vs = glCreateShader(GL_VERTEX_SHADER);
	// 📰 Pass Vertex Shader String
	glShaderSource(vs, 1, &vertString, &vertStringSize);
	// 🔨 Compile Vertex Shader (and check for errors)
	glCompileShader(vs);
	if (!checkShaderCompilation(vs)) return false;

	// 📂 Load Fragment Shader String
#ifndef EMBED_SHADERS
	std::string fsPath = getAppDirectory() + "assets/shaders/triangle.frag";
	std::vector<char> fragShaderCode = readFile(fsPath);
	const char* fragString = fragShaderCode.data();
	int fragStringSize = static_cast<int>(fragShaderCode.size());
#else
	const char* fragString = fragShader;
	int fragStringSize = strlen(fragShader);
#endif
	// ⚪ Create Shader Data Structure
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	// 📰 Pass Fragment Shader String
	glShaderSource(fs, 1, &fragString, &fragStringSize);
	// 🔨 Compile Vertex Shader (and check for errors)
	glCompileShader(fs);
	if (!checkShaderCompilation(fs)) return false;

	// ⚪ Create Shader Program
	program = glCreateProgram();
	// 🩹 Attach Shader Stages to Program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	// 🔗 Link Program (and check for errors)
	glLinkProgram(program);
	if (!checkProgramCompilation(program)) return false;

	// 📐 Create Vertex Array Object
	glGenVertexArrays(1, &vao);

	// 💕 Bind Vertex Array Object
	glBindVertexArray(vao);

	// 🔺 Bind positionVBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	// 🔎 Get position of attribute from shader program
	GLint positionAttrib = glGetAttribLocation(program, "inPosition");
	// 🩹 Bind positionVBO to VAO with the index of positionAttrib (0)
	glEnableVertexAttribArray(positionAttrib);
	// 💬 Describe data layout of VBO
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, (void*)0);

	// 🎨 Bind colorVBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	// 🔎 Get position of attribute from shader program
	GLint colorAttrib = glGetAttribLocation(program, "inColor");
	// 🩹 Bind positionVBO to VAO with the index of colorAttrib (1)
	glEnableVertexAttribArray(colorAttrib);
	// 💬 Describe data layout of VBO
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, (void*)0);

	// 🗄️ Bind IBO to VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	return true;
}

void drawTriangle(unsigned width, unsigned height)
{
	// 🖼️ Set the Viewport size to where you'll be drawing
	glViewport(0, 0, width, height);

	// 🧪 Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 🎨 Bind Shader
	glUseProgram(program);

	// 🩹 Bind VAO
	glBindVertexArray(vao);

	// 🛆 Draw
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void destroyTriangle()
{
	glDeleteBuffers(1, &positionVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &ibo);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
}
