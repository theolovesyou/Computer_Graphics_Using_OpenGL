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

	// GL_ARRAY_BUFFER로 가서 bound된 object 확인 후 address 전달
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// in order to openGL to send the data from the RAM in the grphics card to pipeline, tell openGL to enable that attribute
	glEnableVertexAttribArray(0);

	// tell openGL what that data means. 버텍스당 2 float.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void MeGlWindow::paintGL()
{
	// Update도므로 윈도우창 크기 변경하면 같이 변함.
	glViewport(0, 0, width(), height());

	// go get that data and draw
	glDrawArrays(GL_TRIANGLES, 0, 6);
}