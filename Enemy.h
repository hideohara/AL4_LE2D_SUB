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

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }

private:
	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;

	// 3Dモデル
	Model* modelBody_ = nullptr;
};
