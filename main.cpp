#include <Novice.h>
#include <cmath>
const char kWindowTitle[] = "MT3_00_05";
struct Matrix4x4
{
	float m[4][4];
};
struct Vector3 {
	float x, y, z;
};
#include <cmath>

// スケール行列を作成
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = {};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;
	return result;
}

//1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 rotationX;
	rotationX.m[0][0] = 1.0f;
	rotationX.m[0][1] = 0.0f;
	rotationX.m[0][2] = 0.0f;
	rotationX.m[0][3] = 0.0f;
	rotationX.m[1][0] = 0.0f;
	rotationX.m[1][1] = std::cos(radian);
	rotationX.m[1][2] = std::sin(radian);
	rotationX.m[1][3] = 0.0f;
	rotationX.m[2][0] = 0.0f;
	rotationX.m[2][1] = -std::sin(radian);
	rotationX.m[2][2] = std::cos(radian);
	rotationX.m[2][3] = 0.0f;
	rotationX.m[3][0] = 0.0f;
	rotationX.m[3][1] = 0.0f;
	rotationX.m[3][2] = 0.0f;
	rotationX.m[3][3] = 1.0f;
	return rotationX;
}
//2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 rotationY;
	rotationY.m[0][0] = std::cos(radian);
	rotationY.m[0][1] = 0.0f;
	rotationY.m[0][2] = -std::sin(radian);
	rotationY.m[0][3] = 0.0f;
	rotationY.m[1][0] = 0.0f;
	rotationY.m[1][1] = 1.0f;
	rotationY.m[1][2] = 0.0f;
	rotationY.m[1][3] = 0.0f;
	rotationY.m[2][0] = std::sin(radian);
	rotationY.m[2][1] = 0.0f;
	rotationY.m[2][2] = std::cos(radian);
	rotationY.m[2][3] = 0.0f;
	rotationY.m[3][0] = 0.0f;
	rotationY.m[3][1] = 0.0f;
	rotationY.m[3][2] = 0.0f;
	rotationY.m[3][3] = 1.0f;
	return rotationY;
}
//3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 rotationZ;
	rotationZ.m[0][0] = std::cos(radian);
	rotationZ.m[0][1] = std::sin(radian);
	rotationZ.m[0][2] = 0.0f;
	rotationZ.m[0][3] = 0.0f;
	rotationZ.m[1][0] = -std::sin(radian);
	rotationZ.m[1][1] = std::cos(radian);
	rotationZ.m[1][2] = 0.0f;
	rotationZ.m[1][3] = 0.0f;
	rotationZ.m[2][0] = 0.0f;
	rotationZ.m[2][1] = 0.0f;
	rotationZ.m[2][2] = 1.0f;
	rotationZ.m[2][3] = 0.0f;
	rotationZ.m[3][0] = 0.0f;
	rotationZ.m[3][1] = 0.0f;
	rotationZ.m[3][2] = 0.0f;
	rotationZ.m[3][3] = 1.0f;
	return rotationZ;
}

// 平行移動行列を作成
Matrix4x4 MakeTranslationMatrix(const Vector3& translate) {
	Matrix4x4 result = {};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}
// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 matrixMultiply = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				matrixMultiply.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return matrixMultiply;
}
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	// スケール行列
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	// 各軸の回転行列を作成
	Matrix4x4 rotationXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotationYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotationZMatrix = MakeRotateZMatrix(rotate.z);

	// 回転行列を合成
	Matrix4x4 rotateMatrix = Multiply(Multiply(rotationZMatrix, rotationYMatrix), rotationXMatrix);

	// 平行移動行列
	Matrix4x4 translationMatrix = MakeTranslationMatrix(translate);

	// スケール、回転、平行移動を合成
	Matrix4x4 worldMatrix = Multiply(Multiply(scaleMatrix, rotateMatrix), translationMatrix);

	return worldMatrix;
}





static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	// 最初にラベルを表示
	Novice::ScreenPrintf(x, y, "%s", label);

	// 次の行から数値を表示
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Novice::ScreenPrintf(x + j * kColumnWidth, y + (i + 1) * kRowHeight, "%6.02f", matrix.m[i][j]);
		}
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	Vector3 scale{ 1.2f,0.79f,-2.1f };
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Vector3 translate{ 2.7f,-4.15f,1.57f };
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, worldMatrix, "World Matrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
