#include <gl\glew.h>
#include <MeGlWindow.h>
#include <iostream>
#include <fstream>
using namespace std;

void sendDataToOpenGL()
{
	// 정점정보에서 색상정보를 추가해도 fragment shader 처리를 해줘야 색상이 바뀐다.
	GLfloat verts[] =
	{
		+0.0f, +1.0f,
		+1.0f, +0.0f, +0.0f,
		-1.0f, -1.0f,
		+0.0f, +1.0f, +0.0f,
		+1.0f, -1.0f,
		+0.0f, +0.0f, +1.0f,
	};

	GLuint myBufferID;

	// create buffer obj. how many buffers, store logical address
	glGenBuffers(1, &myBufferID);

	// bind object to GL_ARRAY_BUFFER point.
	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);

	// GL_ARRAY_BUFFER로 가서 bound된 object 확인 후 address 전달
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// in order to openGL to send the data from the RAM in the grphics card to pipeline, tell openGL to enable that attribute
	glEnableVertexAttribArray(0);

	// tell openGL what that data means. 버텍스당 2 float. 
	// stride is the distance and bytes between vertex attributes. attribute 시작점 간의 간격
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	// for color attribute
	glEnableVertexAttribArray(1);

	// 마지막 변수는 해당데이터의 시작점으로 가려면 몇바이트를 지나쳐야 하나.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

	GLushort indices[] = { 0,1,2 };
	GLuint indexBufferID;

	// gen another buffer and bind to another point. 
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	// send data to buffer that bound to GL_ELEMENT_ARRAY_BUFFER |||||-[]----* 간단히 indices[]를 copy to memory 
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
	// VSO, FSO 생성
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

	// c++ 컴파일 obj 나오면 obj끼리 link 후 exe 생성 같은 개념
	// Program object 생성
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
	sendDataToOpenGL();
	installShaders();
}

void MeGlWindow::paintGL()
{
	// Update도므로 윈도우창 크기 변경하면 같이 변함.
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}