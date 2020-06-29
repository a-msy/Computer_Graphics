#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

// マウスボタンをクリック

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			printf("left");
			break;
		
		case GLUT_MIDDLE_BUTTON:
			printf("middle");
			break;

		case GLUT_RIGHT_BUTTON:
			printf("right");
			break;

		default:
			break;
	}

	printf("button is");

	switch (state) {
	case GLUT_UP:
		printf("up");
		break;

	case GLUT_DOWN:
		printf("down");
		break;

	default:
		break;
	}

	printf(" at (%d %d)\n", x, y);
}

void init(void)//初期化
{
	glClearColor(1.0, 1.0, 1.0, 1.0);// ウィンドウを塗りつぶす色を指定
	//            R    G    B   透明度（0:透明，1:不透明）
}

int main(int argc, char* argv[])//開始
{
	glutInit(&argc, argv);// GLUTおよびOpenGLの初期化
	glutInitDisplayMode(GLUT_RGBA);// ディスプレイの表示モードを設定
	glutCreateWindow(argv[0]);// ウィンドウを開く

	// コールバック関数の登録
	glutDisplayFunc(display);// ウィンドウが開かれたりなど，ウィンドウを再描画する時に実行
	glutReshapeFunc(resize); // コールバック関数の追加
	glutMouseFunc(mouse); // コールバック関数の追加
	/*
		glutMouseFunc(void (*func)(int button, int state, int x, int y)：
		- マウスボタンが押された時に実行
		- 関数funcの引数
			button：押されたボタン GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON
			state ：「押した」（GLUT_DOWN），「離した」（GLUT_UP）
			x,y ：マウスの位置
	*/
	init();// 環境初期化
	glutMainLoop();// GLUTのメインループに処理を移す
	return 0;
}