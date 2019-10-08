#include <gl\glew.h>
#include <MeGlWindow.h>

void MeGlWindow::initializeGL()
{
	glewInit();

	GLfloat verts[] =
	{
		+0.0f, +0.0f, +0.0f, +0.0f, +0.0f,
		+1.0f, +1.0f, +0.0f, +0.0f, +0.0f,
		-1.0f, +1.0f, +0.0f, +0.0f, +0.0f,
		-1.0f, -1.0f, +0.0f, +0.0f, +0.0f,
		+1.0f, -1.0f, +0.0f, +0.0f, +0.0f,
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

	// tell openGL what that data means. ���ؽ��� 2 float. 
	// stride is the distance and bytes between vertex attributes. attribute ������ ���� ����
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	// for color attribute
	glEnableVertexAttribArray(1);

	// ������ ������ �ش絥������ ���������� ������ �����Ʈ�� �����ľ� �ϳ�.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(sizeof(float) * 2));

	GLushort indices[] = { 0,1,2, 0,3,4 };
	GLuint indexBufferID;

	// gen another buffer and bind to another point. 
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	// send data to buffer that bound to GL_ELEMENT_ARRAY_BUFFER |||||-[]----* ������ indices[]�� copy to memory 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MeGlWindow::paintGL()
{
	// Update���Ƿ� ������â ũ�� �����ϸ� ���� ����.
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}