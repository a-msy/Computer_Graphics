//基本的なヘッダファイルのインクルード
#include <iostream>
#include <stdio.h>
#include <math.h>

// GLUT ヘッダファイルのインクルード
#include <GL/glut.h>

// 視点操作のための変数
float camera_roll = -30.0; // Ｘ軸を軸とするカメラの回転角度

// マウスのドラッグのための変数
int drag_lmouse = 0; // 左ボタンをドラッグ中かどうかのフラグ（0:ドラッグしてない,1:ドラッグ中）
int mouse_x; // 最後に記録されたマウスカーソルのＸ座標
int mouse_y; // 最後に記録されたマウスカーソルのＹ座標

const int num_pyramid_vertices = 5; // 頂点数
const int num_pyramid_triangles = 6; // 三角面数

// 角すいの頂点座標の配列
GLdouble pyramid_vertices[num_pyramid_vertices][3] = {
{ 0.0, 1.0, 0.0 }, { -1.0,-0.8, 1.0 }, { 1.0,-0.8,1.0 },
{1.0,-0.8, -1.0 }, {-1.0,-0.8,-1.0 }
};

// 三角面インデックス（各三角面を構成する頂点の頂点番号）の配列
int pyramid_tri_index[num_pyramid_triangles][3] = {
{ 0,1,2 }, { 0,2,3 }, { 0,3,4 }, { 0,4,1 }, { 1,3,2 }, { 1,4,3 }
};

// 三角面の法線ベクトル
/*
GLdouble pyramid_tri_normal[num_pyramid_vertices][3] = {
{ nx0, ny0, nz0 }, { nx1, ny1, nz1 }, { nx2, ny2, nz2 },
{ nx3, ny3, nz3 }, { nx4, ny4, nz4 }, { nx5, ny5, nz5 }
};
*/
GLdouble pyramid_tri_normal[num_pyramid_triangles][3] = {
{ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 },
{ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }
};

// ウィンドウを描画する時に実行
void display(void)
{
	// 画面をクリア（ピクセルデータとＺバッファの両方をクリア）
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 変換行列を設定（ワールド座標系→カメラ座標系）

	// モデルビュー変換行列の初期化
	glLoadIdentity();

	// 視点の移動
	glTranslatef(0.0, 0.0, -15.0);
	glRotatef(-camera_roll, 1.0, 0.0, 0.0);

	// 光源位置を設定
	float light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// 地面を描画
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(5.0, 0.0, 5.0);
	glVertex3f(5.0, 0.0, -5.0);
	glVertex3f(-5.0, 0.0, -5.0);
	glVertex3f(-5.0, 0.0, 5.0);
	glEnd();

	// 変換行列を設定（物体のモデル座標系→カメラ座標系）
	glTranslatef(0.0, 1.0, 0.0); //物体が (0.0, 1.0, 0.0) の位置にあり，静止している

	// オブジェクトを描画
	for (int i = 0; i < num_pyramid_triangles; i++) {
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		for (int j = 0; j < 3; j++) {
			glVertex3dv(pyramid_vertices[pyramid_tri_index[i][j]]);
		}
		glEnd();
	}

	// バックバッファに描画した画面をフロントバッファに表示
	glutSwapBuffers();
}
// ウィンドウがリサイズされた時に実行
void resize(int w, int h)
{
	// ウィンドウ全体をビューポートにする
	glViewport(0, 0, w, h);

	// カメラ座標系→スクリーン座標系への変換行列を設定

	// 透視変換行列の指定
	glMatrixMode(GL_PROJECTION);

	// 透視変換行列の初期化
	glLoadIdentity();
	gluPerspective(40, (double)w / h, 1, 100);

	// モデルビュー変換行列の指定
	glMatrixMode(GL_MODELVIEW);
}
// マウスボタンが押された時に実行
void mouse(int button, int state, int x, int y)
{
	// 左ボタンを押したらドラッグ開始のフラグを立てる
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			drag_lmouse = 1;
		// 左ボタンを離したらドラッグ終了のフラグを立てる
		else
			drag_lmouse = 0;
	}
	// 現在のマウスの位置を記録
	mouse_x = x;
	mouse_y = y;
}
// マウスをドラッグした時に実行
void motion(int x, int y)
{
	// 右ボタンのドラッグ中であれば、マウスの移動量に応じて視点を回転する
	if (drag_lmouse == 1)
	{
		// マウスの縦方向の移動に応じてＸ軸を中心に回転
		camera_roll -= (y - mouse_y) * 1.0;
		if (camera_roll < -90.0)
			camera_roll = -90.0;
		else if (camera_roll > 90.0)
			camera_roll = 90.0;
	}
	// 今回のマウス座標を記録
	mouse_x = x;
	mouse_y = y;

	// 再描画の指示を出す（この後で再描画のコールバック関数が呼ばれる）
	glutPostRedisplay();
}
// アイドル時に呼ばれるコールバック関数
void idle(void)
{
}
// 初期設定
void init(void)
{
	// 光源
	float light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
	float light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float light0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glEnable(GL_LIGHT0);
	// 光源計算を有効にする
	glEnable(GL_LIGHTING);
	// 物体の色情報を有効にする
	glEnable(GL_COLOR_MATERIAL);
	// Ｚテストを有効にする
	glEnable(GL_DEPTH_TEST);
	// 背面除去を有効にする
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	// 背景色を設定
	glClearColor(0.5, 0.5, 0.8, 0.0);
}
// Main 関数
int main(int argc, char** argv)
{
	// GLUT の初期化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL 3D");
	// コールバック関数の登録
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);
	// 初期設定
	init();
	// GLUT のメインループに処理を移す
	glutMainLoop();
	// プログラムを終了
	return 0;
}
