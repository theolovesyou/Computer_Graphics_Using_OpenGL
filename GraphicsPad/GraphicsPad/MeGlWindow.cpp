#include <gl\glew.h>
#include <MeGlWindow.h>

void MeGlWindow::initializeGL()
{
	glewInit();

	GLfloat verts[] =
	{
		+0.0f, +0.0f,
		+1.0f, +1.0f,
		-1.0f, +1.0f,

		+0.0f, +0.0f,
		-1.0f, -1.0f,
		+1.0f, -1.0f,
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void MeGlWindow::paintGL()
{
	// Update���Ƿ� ������â ũ�� �����ϸ� ���� ����.
	glViewport(0, 0, width(), height());

	// go get that data and draw
	glDrawArrays(GL_TRIANGLES, 0, 6);
}