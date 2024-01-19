#include "Player.h"
#include "ImGuiManager.h"
// #include "Vector3.h"
#include <cassert>

// 初期化
void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {

	// NULLポインタチェック
	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	// メンバ変数に受け取った値を代入
	modelBody_ = modelBody;
	modelHead_ = modelHead;
	modelL_arm_ = modelL_arm;
	modelR_arm_ = modelR_arm;

	// 親子構造
	// ワールド変換の初期化
	worldTransformBase_.Initialize();

	worldTransformBody_.Initialize();
	worldTransformBody_.parent_ = &worldTransformBase_;

	worldTransformHead_.Initialize();
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformHead_.translation_.y = 1.5038f;

	worldTransformL_arm_.Initialize();
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.translation_.x = -0.5275f;
	worldTransformL_arm_.translation_.y = 1.2619f;

	worldTransformR_arm_.Initialize();
	worldTransformR_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.translation_.x = +0.5275f;
	worldTransformR_arm_.translation_.y = 1.2619f;

	// 移動

	// インプット
	input_ = Input::GetInstance();

	// ギミック初期化
	InitializeFloatingGimmick();
}

// 更新
void Player::Update() {
	// ImGui::Begin("Debug1");
	// ImGui::Text("%d.%d.%d", 2050, 12, 31);
	// ImGui::End();

	// ギミック更新
	UpdateFloatingGimmick();

	const float speed = 0.3f;
	Vector3 move = {0.0f, 0.0f, 0.0f};
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = 1.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		move.x = -1.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		move.z = 1.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN)) {
		move.z = -1.0f;
	}

	move = Normalize(move) * speed;

	if (viewProjection_) {
		// カメラの回転行列
		Matrix4x4 matRotX = MakeRotateXMatrix(viewProjection_->rotation_.x);
		Matrix4x4 matRotY = MakeRotateYMatrix(viewProjection_->rotation_.y);
		Matrix4x4 matRotZ = MakeRotateZMatrix(viewProjection_->rotation_.z);
		// 回転行列の合成
		Matrix4x4 matRot = matRotZ * matRotX * matRotY;

		// 移動量をカメラの回転に合わせて回転させる
		move = TransformNormal(move, matRot);
	}

	worldTransformBase_.translation_ += move;

	// 移動ベクトルのY軸周り角度
	worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);

	// round
	// worldTransformL_arm_.rotation_.x += 0.1f;

	// 変換行列を更新
	worldTransformBase_.matWorld_ = MakeAffineMatrix(
	    worldTransformBase_.scale_, worldTransformBase_.rotation_,
	    worldTransformBase_.translation_);
	// 変換行列を定数バッファに転送
	worldTransformBase_.TransferMatrix();

	// 変換行列を更新（BODY）
	worldTransformBody_.matWorld_ = MakeAffineMatrix(
	    worldTransformBody_.scale_, worldTransformBody_.rotation_,
	    worldTransformBody_.translation_);
	// 親があれば親のワールド行列を掛ける
	if (worldTransformBody_.parent_) {
		worldTransformBody_.matWorld_ *= worldTransformBody_.parent_->matWorld_;
	} // 変換行列を定数バッファに転送
	worldTransformBody_.TransferMatrix();

	// 変換行列を更新（HEAD）
	worldTransformHead_.matWorld_ = MakeAffineMatrix(
	    worldTransformHead_.scale_, worldTransformHead_.rotation_,
	    worldTransformHead_.translation_);
	// 親があれば親のワールド行列を掛ける
	if (worldTransformHead_.parent_) {
		worldTransformHead_.matWorld_ *= worldTransformHead_.parent_->matWorld_;
	} // 変換行列を定数バッファに転送
	worldTransformHead_.TransferMatrix();

	// 変換行列を更新（左手）
	worldTransformL_arm_.matWorld_ = MakeAffineMatrix(
	    worldTransformL_arm_.scale_, worldTransformL_arm_.rotation_,
	    worldTransformL_arm_.translation_);
	// 親があれば親のワールド行列を掛ける
	if (worldTransformL_arm_.parent_) {
		worldTransformL_arm_.matWorld_ *= worldTransformL_arm_.parent_->matWorld_;
	} // 変換行列を定数バッファに転送
	worldTransformL_arm_.TransferMatrix();

	// 変換行列を更新（右手）
	worldTransformR_arm_.matWorld_ = MakeAffineMatrix(
	    worldTransformR_arm_.scale_, worldTransformR_arm_.rotation_,
	    worldTransformR_arm_.translation_);
	// 親があれば親のワールド行列を掛ける
	if (worldTransformR_arm_.parent_) {
		worldTransformR_arm_.matWorld_ *= worldTransformR_arm_.parent_->matWorld_;
	} // 変換行列を定数バッファに転送
	worldTransformR_arm_.TransferMatrix();

	ImGui::Begin("Player");
	ImGui::SliderFloat3(
	    "Head Translation", reinterpret_cast<float*>(&worldTransformHead_.translation_), -10.0f,
	    10.0f);
	ImGui::SliderFloat3(
	    "ArmL Translation", reinterpret_cast<float*>(&worldTransformL_arm_.translation_), -10.0f,
	    10.0f);
	ImGui::SliderFloat3(
	    "ArmR Translation", reinterpret_cast<float*>(&worldTransformR_arm_.translation_), -10.0f,
	    10.0f);
	// ImGui::SliderInt("floatingCycle", reinterpret_cast<int*>(&floatingCycle_), 1, 200);
	// ImGui::SliderFloat("floatingAmplitude", &floatingAmplitude_, 0.0f, 10.0f);
	// ImGui::SliderFloat("idleArmAngleMax_", &idleArmAngleMax_, 0.0f, 180.0f);
	ImGui::End();
}

// 描画
void Player::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	modelBody_->Draw(worldTransformBody_, viewProjection);
	modelHead_->Draw(worldTransformHead_, viewProjection);
	modelL_arm_->Draw(worldTransformL_arm_, viewProjection);
	modelR_arm_->Draw(worldTransformR_arm_, viewProjection);
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {

	// 最もシンプルな処理
	floatingParameter_ += 0.1f;
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * 0.2f;
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * 0.5f;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * 0.5f;

	/*
	const float floatingStep = PI * 2.0f / floatingCycle_;

	// 浮遊ギミックを更新
	floatingParameter_ += floatingStep;
	// 2πを超えたら0に戻す
	floatingParameter_ = fmodf(floatingParameter_, PI * 2.0f);
	// 浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude_;

	worldTransformL_arm_.rotation_.x =
	    std::sin(floatingParameter_) * idleArmAngleMax_ / 180.0f * PI;
	worldTransformR_arm_.rotation_.x =
	    std::sin(floatingParameter_) * idleArmAngleMax_ / 180.0f * PI;
	*/
}
