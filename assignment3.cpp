#include <GL/glew.h> 
#include <GL/glut.h> // or <GL/freeglut.h>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<time.h>
#include <glm/gtc/matrix_transform.hpp>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);


GLuint programID;
GLuint VertexBufferID;
GLuint ColorBufferID;

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 mvp;

float angle;

struct point3
{
	//point3(float a, float b, float c) : x(a), y(b), z(c) {};
	float x;
	float y;
	float z;
};

point3 *vertex;


struct Face {
	int v1;
	int v2;
	int v3;
};
Face *face;

int vertexNumber = 0;
int faceNumber = 0;

int size_buf = 0;

float min_X = 999999.0;
float max_X = -999999.0;
float min_Y = 999999.0;
float max_Y = -999999.0;
float min_Z = 999999.0;
float max_Z = -999999.0;



void test() {

	for (int i = 0; i < vertexNumber; i++) {
		printf("%f %f %f\n", vertex[i].x, vertex[i].y, vertex[i].z);
	}


	for (int i = 0; i < faceNumber; i++) {
		printf("%d %d %d\n", face[i].v1, face[i].v2, face[i].v3);
	}
}


GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


void fileLoad() {
	FILE *fp;
	int i;
	char temp[9999];

	fp = fopen("Vase.dat", "r");

	fscanf(fp, "%s %s %d", temp, temp, &vertexNumber);

	vertex = new point3[vertexNumber];

	for (i = 0; i < vertexNumber; i++) {
		fscanf(fp, "%f %f %f", &vertex[i].x, &vertex[i].y, &vertex[i].z);

		max_X = max_X > vertex[i].x ? max_X : vertex[i].x;
		min_X = min_X < vertex[i].x ? min_X : vertex[i].x;

		max_Y = max_Y > vertex[i].y ? max_Y : vertex[i].y;
		min_Y = min_Y < vertex[i].y ? min_Y : vertex[i].y;

		max_Z = max_Z > vertex[i].z ? max_Z : vertex[i].z;
		min_Z = min_Z < vertex[i].z ? min_Z : vertex[i].z;
		
	}

	fscanf(fp, "%s %s %d", temp, temp, &faceNumber);
	face = new Face[faceNumber];

	for (i = 0; i < faceNumber; i++) {
		fscanf(fp, "%d %d %d", &face[i].v1, &face[i].v2, &face[i].v3);
	}

	printf("Read Complete\n");
	
}


void timer(int value) {
	angle += glm::radians(5.0f);
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

void transform() {
	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f);
	
	//translate
	glm::mat4 trans = glm::translate(Model, glm::vec3( -(max_X + min_X) / 2, -(max_Y + min_Y) / 2, -(max_Z + min_Z) / 2));
	
	//rotate
	Model = glm::rotate(Model, angle, glm::vec3(0, 1, 0));
	
	
	
	float max = max_X > max_Y ? max_X : max_Y;
	max = max > max_Z ? max : max_Z;


	//Scaling
	Model = glm::scale(Model, glm::vec3(1/max, 1/max, 1/max));



	// ModelViewProjection
	mvp = Projection * View * Model * trans;

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void myreshape(int w, int h) {
	glViewport(0, 0, w, h);

	Projection = glm::perspective(glm::radians(45.0f),
		(float)w / (float)h, 0.1f, 100.0f);

	View = glm::lookAt(
		glm::vec3(3, 4, 3), // Camera is at (3,4,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	transform();
}


void init()
{
	fileLoad();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	
	point3 *vertices = new point3[faceNumber*3];



	for (int i = 0; i < faceNumber; i++) {
		vertices[i*3] = vertex[face[i].v1];
		vertices[i*3+1] = vertex[face[i].v2];
		vertices[i*3+2] = vertex[face[i].v3];
	}

	



	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point3)*faceNumber*3, vertices, GL_STATIC_DRAW);

	point3 *colors = new point3[faceNumber*3];

	srand((unsigned int)time(NULL));

	for (int i = 0; i < faceNumber*3; i+= 3) {
		point3 *temp = new point3;
		temp->x = rand() % 2;
		temp->y = rand() % 2;
		temp->z = rand() % 2;

		colors[i] = *temp;
		colors[i + 1] = *temp;
		colors[i + 2] = *temp;
	}



	glGenBuffers(1, &ColorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point3)* faceNumber * 3, colors, GL_STATIC_DRAW);

	programID = LoadShaders("simple.vshader", "simple.fshader");
	glUseProgram(programID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


void mydisplay() {
	transform();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, faceNumber*3);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Tutorial 03");
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutTimerFunc(0, timer, 0);


	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		init();
		glutMainLoop();
	}

}
