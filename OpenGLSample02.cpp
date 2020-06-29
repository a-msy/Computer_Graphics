#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

void display(void)//コールバック関数 // 画面の再描画が必要な時に呼ばれる
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);

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

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	/*
	glViewport(x, y, w, h)：ビューポートの指定(開いたウィンドウの中で，実際に描画される領域)
	x,y: 描画領域の左下隅の位置
	w,h: 描画領域の幅（w）と高さ（h）
	*/
	glLoadIdentity();//：変換行列の初期化
	glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
	/*
		glOrtho(l, r, b, t, n, f)：ワールド座標系を正規化デバイス座標系に平行投影
	*/

	/*
		表示図形のサイズを，ビューポートの大きさに関係なく一定にするには
		glOrtho(l*w/W, r *w/W, b*h/H, t *h/H, n, f)
		元のウィンドウの大きさ ：W✕H
		リサイズ後のウィンドウの大きさ：w✕h
	*/
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
	/*
		glutReshapeFunc(void (*func)(int w, int h))：
		ウィンドウがリサイズされた時に実行
		関数funcの引数には，リサイズ後の幅（w）と高さ（h）が渡される
	*/
	init();// 環境初期化
	glutMainLoop();// GLUTのメインループに処理を移す
	return 0;

	/*
		位置やサイズを指定してウィンドウを開く

		glutInitWindowPosition(x, y)：ウィンドウの位置（x, y）を指定
		glutInitWindowSize(w, h)：ウィンドウの幅（w）と高さ（h）を指定
	*/
}