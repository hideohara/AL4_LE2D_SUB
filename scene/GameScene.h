#pragma once

#include "Audio.h"
#include "AxisIndicator.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "FollowCamera.h"
#include "Ground.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Skydome.h"
#include "Sprite.h"
#include "Title.h"
#include "GameClear.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// ビュープロジェクション
	ViewProjection viewProjection_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// モデルデータ
	// std::unique_ptr<Model> modelFighter_;
	// 3Dモデル
	std::unique_ptr<Model> modelSkydome_;
	// 3Dモデル
	std::unique_ptr<Model> modelGround_;

	// クラス
	std::unique_ptr<Player> player_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<Title> title_;
	std::unique_ptr<GameClear> gameClear_;

	// 3Dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;
	std::unique_ptr<Model> modelEnemy_;

	// テクスチャハンドル
	uint32_t textureHandleTitle_ = 0u;
	uint32_t textureHandleGameClear_ = 0u;
	uint32_t textureHandleKey_ = 0u;

	// スプライト
	std::unique_ptr<Sprite> spriteTitle_;
	std::unique_ptr<Sprite> spriteGameClear_;
	std::unique_ptr<Sprite> spriteKey_;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	// 追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// ゲームシーン
	uint32_t sceneMode_ = 1;

	uint32_t hitCount_ = 0;
};
