#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

// マウスで線を引く
#define MAXPOINTS 100
GLint point[MAXPOINTS][2];
int pointnum = 0;
int rubberband = 0;	// ラバーバンドの消去



void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);

	if (pointnum > 1) {
		glColor3d(1.0, 0.0, 0.0);//henko 1
		glBegin(GL_LINES);
		for (i = 0; i < pointnum; ++i) {
			glVertex2iv(point[i]);
		}
		glEnd();
	}

	glFlush();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	// スクリーン上の座標系をマウスの座標系に一致させる
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

// 変更
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:

		point[pointnum][0] = x;
		point[pointnum][1] = y;

		if (state == GLUT_UP) {
			glColor3d(1.0, 0.0, 0.0);//henko 2
			glBegin(GL_LINES);
			glVertex2iv(point[pointnum - 1]);
			glVertex2iv(point[pointnum]);
			glEnd();
			glFlush();

			// 始点では，ラバーバンドを描いてないので消さない
			rubberband = 0;
		}
		else {
		}
		if (pointnum < MAXPOINTS - 1)
			++pointnum;
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}

// 追加
void motion(int x, int y)
{
	static GLint savepoint[2];	// 以前のラバーバンドの端点

	// 論理演算機能　ON
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_INVERT);

	glBegin(GL_LINES);
	if (rubberband) {
		// 以前のラバーバンドを消す
		glVertex2iv(point[pointnum - 1]);
		glVertex2iv(savepoint);
	}
	// 新しいラバーバンドを描く
	glVertex2iv(point[pointnum - 1]);
	glVertex2i(x, y);
	glEnd();

	glFlush();

	// 論理演算機能　OFF
	glLogicOp(GL_COPY);
	glDisable(GL_COLOR_LOGIC_OP);

	// 今描いたラバーバンドの端点を保存
	savepoint[0] = x;
	savepoint[1] = y;

	// 今描いたラバーバンドは次のタイミングで消す
	rubberband = 1;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			printf("Another Key\n");
			break;
	}
}

void init(void)
{
	glClearColor(0.0, 1.0, 1.0, 1.0);
}

int main(int argc, char* argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);//henko

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("09430509");//henko
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	// コールバック関数の追加	
	glutMotionFunc(motion);

	init();
	glutMainLoop();
	return 0;
}
