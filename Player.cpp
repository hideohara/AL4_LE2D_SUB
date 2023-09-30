#include "Player.h"
#include "ImGuiManager.h"
//#include "Vector3.h"
#include <cassert>

// 初期化
void Player::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);

	// メンバ変数に受け取った値を代入
	//textureHandle_ = textureHandle;
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// インプット
	input_ = Input::GetInstance();
}

// 更新
void Player::Update() {
	//ImGui::Begin("Debug1");
	//ImGui::Text("%d.%d.%d", 2050, 12, 31);
	//ImGui::End();

	const float speed = 0.3f;
	Vector3 move = {0.0f, 0.0f, 0.0f};
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = 1.0f * speed;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		move.x = -1.0f * speed;
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		move.z = 1.0f * speed;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		move.z = -1.0f * speed;
	}
	worldTransform_.translation_ += move;

	// 変換行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_,
	    worldTransform_.translation_);
	// 変換行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

// 描画
void Player::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);
}

