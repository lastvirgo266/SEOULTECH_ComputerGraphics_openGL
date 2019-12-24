//#include <GL/glew.h> 
//#include <GL/glut.h> // or <GL/freeglut.h>
//#include<vector>
//#include<string>
//#include<fstream>
//#include<sstream>
//
//GLuint VertexBufferID;
//
//GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
//GLuint programID;
//
//
//struct point3
//{
//	point3(float a, float b, float c) : x(a), y(b), z(c) {};
//	float x;
//	float y;
//	float z;
//};
//
//void mydisplay() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	// Starting from vertex 0; 3 vertices -> 1 triangle
//	glDisableVertexAttribArray(0);
//
//	glFlush();
//}
//
//
//void init()
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	GLuint VertexArrayID;
//	glGenVertexArrays(1, &VertexArrayID);
//	glBindVertexArray(VertexArrayID);
//
//	point3 vertices[3] = { point3(0.0, 0.0, 0.0), point3(0.0, 0.9, 0.0), point3(0.9, 0.9, 0.0) };
//
//	glGenBuffers(1, &VertexBufferID);
//	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	programID = LoadShaders("simple.vshader", "simple.fshader");
//	glUseProgram(programID);
//
//}
//
//GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
//
//	// Create the shaders
//	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//
//	// Read the Vertex Shader code from the file
//	std::string VertexShaderCode;
//	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
//	if (VertexShaderStream.is_open()) {
//		std::stringstream sstr;
//		sstr << VertexShaderStream.rdbuf();
//		VertexShaderCode = sstr.str();
//		VertexShaderStream.close();
//	}
//	else {
//		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
//		getchar();
//		return 0;
//	}
//
//	// Read the Fragment Shader code from the file
//	std::string FragmentShaderCode;
//	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
//	if (FragmentShaderStream.is_open()) {
//		std::stringstream sstr;
//		sstr << FragmentShaderStream.rdbuf();
//		FragmentShaderCode = sstr.str();
//		FragmentShaderStream.close();
//	}
//
//	GLint Result = GL_FALSE;
//	int InfoLogLength;
//
//	// Compile Vertex Shader
//	printf("Compiling shader : %s\n", vertex_file_path);
//	char const* VertexSourcePointer = VertexShaderCode.c_str();
//	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
//	glCompileShader(VertexShaderID);
//
//	// Check Vertex Shader
//	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
//		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//		printf("%s\n", &VertexShaderErrorMessage[0]);
//	}
//
//	// Compile Fragment Shader
//	printf("Compiling shader : %s\n", fragment_file_path);
//	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
//	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
//	glCompileShader(FragmentShaderID);
//
//	// Check Fragment Shader
//	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
//		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
//		printf("%s\n", &FragmentShaderErrorMessage[0]);
//	}
//
//	// Link the program
//	printf("Linking program\n");
//	GLuint ProgramID = glCreateProgram();
//	glAttachShader(ProgramID, VertexShaderID);
//	glAttachShader(ProgramID, FragmentShaderID);
//	glLinkProgram(ProgramID);
//
//	// Check the program
//	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
//	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	if (InfoLogLength > 0) {
//		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
//		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//		printf("%s\n", &ProgramErrorMessage[0]);
//	}
//
//	glDetachShader(ProgramID, VertexShaderID);
//	glDetachShader(ProgramID, FragmentShaderID);
//
//	glDeleteShader(VertexShaderID);
//	glDeleteShader(FragmentShaderID);
//
//	return ProgramID;
//}
//
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitWindowSize(400, 400);
//	glutInitWindowPosition(500, 500);
//	glutCreateWindow("Tutorial 02");
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
//	glutDisplayFunc(mydisplay);
//
//	GLenum err = glewInit();
//	if (err == GLEW_OK) {
//		init();
//		glutMainLoop();
//	}
//}
