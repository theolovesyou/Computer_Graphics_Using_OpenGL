// shader code�� �׳� string�̰� openGL�� ��Ÿ�ӿ� �������Ѵ�. �׷���ī�� instruction�� �޶�
// vertex attribute�� vertexShader�� �����ϴ� ��Ұ� location. 
// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); ���� ù��° ����
// vec2 position;���� vec2�� 2, GL_FLOAT
// vertex shader�� ���� vertex ouput�� hardware�� � pixel�� Ŀ���ľ� �ϴ��� ��°� gl_position

const char* vertexShaderCode =
"#version 430\r\n"
""
"in layout(location=0) vec2 position;"
"in layout(location=1) vec3 vertexColor;"
""
"out vec3 theColor;"
""
"void main()"
"{"
"	gl_Position = vec4(position, 0.0, 1.0);"
"	theColor = vertexColor;"
"}"
"";

// vec4�� 4��° ���ڴ� ���İ�. 1�̸� opaque
const char* fragmentShaderCode =
"#version 430\r\n"
""
"out vec4 daColor;"
"in vec3 theColor;"
""
"void main()"
"{"
"	daColor = vec4(theColor, 1.0);"
"}";