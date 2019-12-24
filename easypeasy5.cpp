//#include <GL/glew.h> 
//#include <GL/glut.h> // or <GL/freeglut.h>
//#include<vector>
//#include<string>
//#include<fstream>
//#include<sstream>
//#include <glm/gtc/matrix_transform.hpp>
//
//GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
//
//
//GLuint programID;
//GLuint VertexBufferID;
//GLuint ColorBufferID;
//
//glm::mat4 Projection;
//glm::mat4 View;
//glm::mat4 Model;
//glm::mat4 mvp;
//
//float angle;
//
//struct point3
//{
//	point3(float a, float b, float c) : x(a), y(b), z(c) {};
//	float x;
//	float y;
//	float z;
//};
//
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
//void timer(int value) {
//	angle += glm::radians(5.0f);
//	glutPostRedisplay();
//	glutTimerFunc(20, timer, 0);
//}
//
//
//void transform() {
//	// Model matrix : an identity matrix (model will be at the origin)
//	Model = glm::mat4(1.0f);
//	Model = glm::rotate(Model, angle, glm::vec3(0, 1, 0));
//
//	// ModelViewProjection
//	mvp = Projection * View * Model;
//
//	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
//}
//
//void myreshape(int w, int h) {
//	glViewport(0, 0, w, h);
//
//	Projection = glm::perspective(glm::radians(45.0f),
//		(float)w / (float)h, 0.1f, 100.0f);
//
//	View = glm::lookAt(
//		glm::vec3(3, 4, 3), // Camera is at (3,4,3), in World Space
//		glm::vec3(0, 0, 0), // and looks at the origin
//		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
//	);
//	transform();
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
//	point3 vertices[39] = {
//		point3(-1.0f,-10.0f,-1.0f), point3(-1.0f,-1.0f, 1.0f), point3(-1.0f, 1.0f, 1.0f),
//		point3(1.0f, 1.0f,-1.0f), point3(-1.0f,-1.0f,-1.0f), point3(-1.0f, 1.0f,-1.0f),
//		point3(1.0f,-1.0f, 1.0f), point3(-1.0f,-1.0f,-1.0f), point3(1.0f,-1.0f,-1.0f),
//		point3(1.0f, 1.0f,-1.0f), point3(1.0f,-1.0f,-1.0f), point3(-1.0f,-1.0f,-1.0f),
//		point3(-1.0f,-1.0f,-1.0f), point3(-1.0f, 1.0f, 1.0f), point3(-1.0f, 1.0f,-1.0f),
//		point3(1.0f,-1.0f, 1.0f), point3(-1.0f,-1.0f, 1.0f), point3(-1.0f,-1.0f,-1.0f),
//		point3(-1.0f, 1.0f, 1.0f), point3(-1.0f,-1.0f, 1.0f), point3(1.0f,-1.0f, 1.0f),
//		point3(1.0f, 1.0f, 1.0f), point3(1.0f,-1.0f,-1.0f), point3(1.0f, 1.0f,-1.0f),
//		point3(1.0f,-1.0f,-1.0f), point3(1.0f, 1.0f, 1.0f), point3(1.0f,-1.0f, 1.0f),
//		point3(1.0f, 1.0f, 1.0f), point3(1.0f, 1.0f,-1.0f), point3(-1.0f, 1.0f,-1.0f),
//		point3(1.0f, 1.0f, 1.0f), point3(-1.0f, 1.0f,-1.0f), point3(-1.0f, 1.0f, 1.0f),
//		point3(1.0f, 1.0f, 1.0f), point3(1.0f, 1.0f, 1.0f), point3(1.0f,-1.0f, 1.0f),
//		point3(1.0f, -1.0f, 1.0f), point3(1.0f, 10.0f, 1.0f), point3(1.0f,-1.0f, 1.5f)
//	};
//
//	glGenBuffers(1, &VertexBufferID);
//	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//
//	point3 colors[39] = {
//		point3(1.0f, 10.0f, 0.0f), point3(1.0f, 0.0f, 0.0f), point3(1.0f, 0.0f, 0.0f),
//		point3(1.0f, 2.0f, 0.0f), point3(1.0f, 0.0f, 0.0f), point3(1.0f, 0.0f, 0.0f),
//		point3(0.0f, 1.0f, 0.0f), point3(0.0f, 1.0f, 0.0f), point3(0.0f, 1.0f, 0.0f),
//		point3(0.0f, 1.0f, 0.0f), point3(0.0f, 1.0f, 0.0f), point3(0.0f, 1.0f, 0.0f),
//		point3(0.0f, 0.0f, 1.0f), point3(0.0f, 0.0f, 1.0f), point3(0.0f, 0.0f, 1.0f),
//		point3(0.0f, 0.0f, 1.0f), point3(0.0f, 0.0f, 1.0f), point3(0.0f, 0.0f, 1.0f),
//		point3(0.0f, 1.0f, 1.0f), point3(0.0f, 1.0f, 1.0f), point3(0.0f, 1.0f, 1.0f),
//		point3(0.0f, 1.0f, 1.0f), point3(0.0f, 1.0f, 1.0f), point3(0.0f, 1.0f, 1.0f),
//		point3(1.0f, 0.0f, 1.0f), point3(1.0f, 0.0f, 1.0f), point3(1.0f, 0.0f, 1.0f),
//		point3(1.0f, 0.0f, 1.0f), point3(1.0f, 0.0f, 1.0f), point3(1.0f, 0.0f, 1.0f),
//		point3(1.0f, 1.0f, 0.0f), point3(1.0f, 1.0f, 0.0f), point3(1.0f, 1.0f, 0.0f),
//		point3(1.0f, 1.0f, 0.0f), point3(1.0f, 1.0f, 0.0f), point3(1.0f, 1.0f, 0.0f),
//		point3(0.0f, 1.0f, 1.0f), point3(0.0f, 1.0f, 1.0f), point3(0.0f, 1.0f, 1.0f)
//
//	};
//
//	glGenBuffers(1, &ColorBufferID);
//	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//
//	programID = LoadShaders("simple.vshader", "simple.fshader");
//	glUseProgram(programID);
//
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//}
//
//
//void mydisplay() {
//	transform();
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glDisableVertexAttribArray(0);
//
//	glutSwapBuffers();
//}
//
//
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitWindowSize(400, 400);
//	glutInitWindowPosition(500, 500);
//	glutCreateWindow("Tutorial 03");
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutTimerFunc(0, timer, 0);
//
//
//	glutDisplayFunc(mydisplay);
//	glutReshapeFunc(myreshape);
//
//	GLenum err = glewInit();
//	if (err == GLEW_OK) {
//		init();
//		glutMainLoop();
//	}
//
//}
