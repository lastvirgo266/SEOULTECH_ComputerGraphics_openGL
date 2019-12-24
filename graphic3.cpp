//#include <GL/glew.h> 
//#include <GL/glut.h> // or <GL/freeglut.h>
//
//GLuint VertexBufferID;
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
//}
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
