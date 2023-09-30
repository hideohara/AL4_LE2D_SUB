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
}

// 更新
void Player::Update() {
	//ImGui::Begin("Debug1");
	//ImGui::Text("%d.%d.%d", 2050, 12, 31);
	//ImGui::End();

	//worldTransform_.translation_.x += 0.01f;

	//// 変換行列を更新
	//worldTransform_.matWorld_ = MakeAffineMatrix(
	//    worldTransform_.scale_, worldTransform_.rotation_,
	//    worldTransform_.translation_);
	//// 変換行列を定数バッファに転送
	//worldTransform_.TransferMatrix();
}

// 描画
void Player::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);
}

