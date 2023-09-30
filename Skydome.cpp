﻿#include "Skydome.h"
// #include "ImGuiManager.h"
// #include "Vector3.h"
#include <cassert>

// 初期化
void Skydome::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);

	// メンバ変数に受け取った値を代入
	// textureHandle_ = textureHandle;
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

// 更新
void Skydome::Update() {}

// 描画
void Skydome::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection);
}
