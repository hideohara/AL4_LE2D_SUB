#pragma once

#include "MathUtilityForText.h"
#include "Model.h"
#include "WorldTransform.h"

// 敵
class Enemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* modelBody);
	// 更新
	void Update();

	// 描画
	void Draw(const ViewProjection& viewProjection);

	// const WorldTransform& GetWorldTransform() { return worldTransformBase_; }

	float GetX() { return worldTransformBase_.matWorld_.m[3][0]; }
	float GetY() { return worldTransformBase_.matWorld_.m[3][1]; }
	float GetZ() { return worldTransformBase_.matWorld_.m[3][2]; }

	void Hit();

private:
	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;

	// 3Dモデル
	Model* modelBody_ = nullptr;

	// ジャンプ
	bool jumpFlag_ = false;
	float jumpSpeed_ = 0;
};
