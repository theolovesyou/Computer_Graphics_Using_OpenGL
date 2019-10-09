#include <gl\glew.h>
#include <MeGlWindow.h>
#include <iostream>
#include <fstream>
using namespace std;

void sendDataToOpenGL()
{
	const float RED_TRIANGLE_Z = 0.5;
	const float BLUE_TRIANGLE_Z = -0.5;

	// ������������ ���������� �߰��ص� fragment shader ó���� ����� ������ �ٲ��.
	GLfloat verts[] =
	{
		-1.0f, -1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f,
		+1.0f, -1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f,

		-1.0f, +1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f,
		+0.0f, -1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f,
	};

	GLuint myBufferID;

	// create buffer obj. how many buffers, store logical address
	glGenBuffers(1, &myBufferID);

	// bind object to GL_ARRAY_BUFFER point.
	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);

	// GL_ARRAY_BUFFER�� ���� bound�� object Ȯ�� �� address ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// in order to openGL to send the data from the RAM in the grphics card to pipeline, tell openGL to enable that attribute
	glEnableVertexAttribArray(0);

	// tell openGL what that data means. ���ؽ��� 3 float. 
	// stride is the distance and bytes between vertex attributes. attribute ������ ���� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	// for color attribute
	glEnableVertexAttribArray(1);

	// ������ ������ �ش絥������ ���������� ������ �����Ʈ�� �����ľ� �ϳ�.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLushort indices[] = { 0,1,2, 3,4,5, };
	GLuint indexBufferID;

	// gen another buffer and bind to another point. 
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	// send data to buffer that bound to GL_ELEMENT_ARRAY_BUFFER |||||-[]----* ������ indices[]�� copy to memory 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}

void installShaders()
{
	// VSO, FSO ����
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	// c++ ������ obj ������ obj���� link �� exe ���� ���� ����
	// Program object ����
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glUseProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
}

void MeGlWindow::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	// Update���Ƿ� ������â ũ�� �����ϸ� ���� ����.
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}