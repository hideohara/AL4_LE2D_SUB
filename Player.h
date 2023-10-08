﻿#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "Input.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);


	// 更新
	void Update();

	// 描画
	void Draw(const ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }

	
    void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

private:
	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	// モデル
	//Model* model_ = nullptr;
	// 3Dモデル
	Model* modelBody_ = nullptr;
	Model* modelHead_ = nullptr;
	Model* modelL_arm_ = nullptr;
	Model* modelR_arm_ = nullptr;


	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 入力
	Input* input_ = nullptr;

	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;


    // 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	// 浮遊移動のサイクル<sec>
	//int32_t floatingCycle_ = 90;
	// 浮遊振幅
	//float floatingAmplitude_ = 0.2f;
	// 待機モーションの腕角度最大値
	//float idleArmAngleMax_ = 30.0f;

	// ギミック初期化
	void InitializeFloatingGimmick();
	// ギミック更新
	void UpdateFloatingGimmick();
};
