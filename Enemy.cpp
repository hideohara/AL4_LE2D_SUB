#include "Enemy.h"
#include <cassert>
void Enemy::Initialize(Model* modelBody) {
	// NULLポインタチェック
	assert(modelBody);

	// メンバ変数に受け取った値を代入
	modelBody_ = modelBody;

	// 親子構造
	// ワールド変換の初期化
	worldTransformBase_.Initialize();

	worldTransformBody_.Initialize();
	worldTransformBody_.parent_ = &worldTransformBase_;
}

void Enemy::Update() {

	// 移動
	const float speed = 0.1f;
	worldTransformBase_.rotation_.y += 0.01f;
	//  移動量
	Vector3 move = {0.0f, 0.0f, speed};
	// 回転行列
	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransformBase_.rotation_.y);
	// 移動量を回転に合わせて回転させる
	move = TransformNormal(move, matRotY);
	// 移動
	worldTransformBase_.translation_ += move;

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
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	modelBody_->Draw(worldTransformBody_, viewProjection);
}
