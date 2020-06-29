#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

void display(void)//コールバック関数 // 画面の再描画が必要な時に呼ばれる
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	/*
	GL_LINE_LOOP,:線をめっちゃつなぐ 
	GL_POINTS, :点だけ
	GL_LINES, :線分
	GL_TRIANGLES,: 三角形
	GL_QUADS, :四角形
	GL,POLYGON:多角形
	*/
	glColor3d(1.0, 0.0, 0.0); // 点の色の指定
	glVertex2d(-0.9, -0.9);

	glColor3d(0.0, 1.0, 0.0); // 点の色の指定
	glVertex2d(0.9, -0.9);

	glColor3d(0.0, 0.0, 1.0); // 点の色の指定
	glVertex2d(0.9, 0.9);

	glColor3d(1.0, 1.0, 0.0); // 点の色の指定
	glVertex2d(-0.9, 0.9);

	glEnd();
	glFlush();
}
/*
glColor3d (r,g,b):0 <= rgb <= 1 (double型)
glColor3f (r,g,b):0 <= rgb <= 1 (float型)

glVertex2d (x, y);座標の指定 double
glVertex2f (x, y);座標の指定 float

glBegin（mode）
glEnd（ ）      glBegin～glEndの間に，描画したい図形の頂点の座標値を設定

*/

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
	init();// 環境初期化
	glutMainLoop();// GLUTのメインループに処理を移す
	return 0;
}

/*

gl～ で始まる関数：OpenGLの標準関数

glut～ で始まる関数：GLUT（OpenGL UtilityToolkit）の関数

*/