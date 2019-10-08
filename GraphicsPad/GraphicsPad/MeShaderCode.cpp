// shader code는 그냥 string이고 openGL이 런타임에 컴파일한다. 그래픽카드 instruction이 달라서
// vertex attribute를 vertexShader로 전달하는 장소가 location. 
// glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); 에서 첫번째 인자
// vec2 position;에서 vec2가 2, GL_FLOAT
// vertex shader가 내논 vertex ouput이 hardware가 어떤 pixel을 커버쳐야 하는지 담는게 gl_position

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

// vec4의 4번째 인자는 알파값. 1이면 opaque
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