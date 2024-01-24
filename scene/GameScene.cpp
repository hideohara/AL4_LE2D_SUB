#include "GameScene.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	// delete player_; // プレイヤークラス
	// delete model_;  // モデル
}

// 初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.translation_ = {0.0f, 2.0f, -10.0f};
	viewProjection_.Initialize();
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルの生成
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	// modelFighter_.reset(Model::CreateFromOBJ("float", true));

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	modelEnemy_.reset(Model::CreateFromOBJ("needle_Body", true));

	// 自機
	player_ = std::make_unique<Player>();
	// player_->Initialize(modelFighter_.get());
	player_->Initialize(
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get());

	// 敵
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(modelEnemy_.get());

	// 地面
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get());

	// スカイドーム
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get());

	// デバッグカメラ
	debugCamera_ = std::make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
	debugCamera_->SetFarZ(2000.0f);

	// 追従カメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	player_->SetViewProjection(&followCamera_->GetViewProjection());

	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

	// 軸方向表示の表示を有効にする
	// AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	// AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	// テクスチャ
	textureHandleTitle_ = TextureManager::Load("title.png");
	textureHandleGameClear_ = TextureManager::Load("gameclear.png");
	textureHandleKey_ = TextureManager::Load("enter.png");
	textureHandleBlack_ = TextureManager::Load("black.png");
	// スプライトの生成
	spriteTitle_.reset(Sprite::Create(textureHandleTitle_, {0, 0}));
	spriteGameClear_.reset(Sprite::Create(textureHandleGameClear_, {0, 0}));
	spriteKey_.reset(Sprite::Create(textureHandleKey_, {400, 500}));
	spriteBlack_.reset(Sprite::Create(textureHandleBlack_, {0, 0}));

	// シーン
	title_ = std::make_unique<Title>();
	title_->Initialize(
	    spriteTitle_.get(), spriteKey_.get(), textureHandleTitle_, textureHandleKey_);
	gameClear_ = std::make_unique<GameClear>();
	gameClear_->Initialize(
	    spriteGameClear_.get(), spriteKey_.get(), textureHandleTitle_, textureHandleKey_);

	// フェイド
	fade_ = std::make_unique<Fade>();
	fade_->Initialize(spriteBlack_.get(), textureHandleBlack_);
	fade_->StartFadeIn();
}

// 更新
void GameScene::Update() {

	fade_->Update();

	switch (sceneMode_) {
	// ゲームプレイ
	case 0:
		// デバッグカメラの更新
		if (input_->TriggerKey(DIK_0)) {
			// フラグをトグル
			isDebugCameraActive_ = !isDebugCameraActive_;
		}
		if (isDebugCameraActive_ == true) {
			debugCamera_->Update();
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		} else {
			followCamera_->Update();
			viewProjection_.matView = followCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		}
		// ビュープロジェクションの転送
		viewProjection_.TransferMatrix();

		player_->Update();
		enemy_->Update();

		// 衝突判定
		if (enemy_->GetY() == 0) {

			float dx = abs(player_->GetX() - enemy_->GetX());
			float dz = abs(player_->GetZ() - enemy_->GetZ());
			if (dx < 1 && dz < 1) {
				// 衝突
				// ImGui::Begin("Hit");
				// ImGui::InputFloat("DX", &dx);
				// ImGui::InputFloat("DZ", &dz);
				// ImGui::End();

				enemy_->Hit();
				hitCount_++;
			}
		}
		if (hitCount_ >= 10) {
			fade_->StartFadeOut();
		}

		if (fade_->IsEndFadeOut() == true) {
			sceneMode_ = 2;
			fade_->StartFadeIn();
		}

		break;
	// タイトル
	case 1:
		if (title_->Update() == true) {
			fade_->StartFadeOut();
		}
		if (fade_->IsEndFadeOut() == true) {
			sceneMode_ = 0;
			hitCount_ = 0;
			fade_->StartFadeIn();
		}
		break;
	// ゲームクリア
	case 2:
		if (gameClear_->Update() == true) {
			fade_->StartFadeOut();
		}
		if (fade_->IsEndFadeOut() == true) {
			sceneMode_ = 1;
			fade_->StartFadeIn();
		}

		break;
	}
}
// 描画
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	switch (sceneMode_) {
	case 0:

		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// </summary>

		//   // クラスの描画
		// if (isDebugCameraActive_ == true) {
		//	player_->Draw(debugCamera_->GetViewProjection());
		//	ground_->Draw(debugCamera_->GetViewProjection());
		//	skydome_->Draw(debugCamera_->GetViewProjection());
		//} else {
		//	player_->Draw(viewProjection_);
		//	ground_->Draw(viewProjection_);
		//	skydome_->Draw(viewProjection_);
		//}

		player_->Draw(viewProjection_);
		enemy_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (sceneMode_) {
	case 1:
		title_->Draw();
		break;
	case 2:
		gameClear_->Draw();
		break;
	}

	// spriteBlack_->SetColor({1, 1, 1, a});
	// a -= 0.01f;
	// if (a <= 0) {
	//	a = 0;
	// }

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
