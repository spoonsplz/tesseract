#include "aerobox.h"
#include "tesseract.h"

using namespace std;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	tesseract::init();
}

void display() {
	glViewport(0, 0, (GLsizei)aerobox::viewport_width, (GLsizei)aerobox::viewport_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(aerobox::fov,
		(GLfloat)aerobox::viewport_width / (GLfloat)aerobox::viewport_height,
		aerobox::viewport_near, aerobox::viewport_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(aerobox::viewport_position[0], aerobox::viewport_position[1],
		aerobox::viewport_position[2], aerobox::viewport_lookat[0], aerobox::viewport_lookat[1],
		aerobox::viewport_lookat[2],
		aerobox::viewport_up[0], aerobox::viewport_up[1], aerobox::viewport_up[2]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	aerobox::calc_ray();

	tesseract::update();

	aerobox::keyboard_update();
	aerobox::mouse_update();
	glutPostRedisplay();
	glFlush();
}

void reshape(int w, int h) {
	aerobox::viewport_width = w;
	aerobox::viewport_height = h;
}

int main(int argc, char* argv[]) {
	glutInitWindowSize(720, 480);
	glutInitWindowPosition(500, 500);
	glutInit(&argc, argv);

	glutCreateWindow(argv[0]);

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutIgnoreKeyRepeat(1);

	glutKeyboardFunc(aerobox::keyboard_func);
	glutKeyboardUpFunc(aerobox::keyboard_up_func);
	glutMouseFunc(aerobox::mouse_func);
	glutMotionFunc(aerobox::motion_func);
	glutPassiveMotionFunc(aerobox::passive_motion_func);
	glutMainLoop();
}