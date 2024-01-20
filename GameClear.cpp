#include "GameClear.h"

#include "Title.h"
#include "TextureManager.h"

void GameClear::Initialize() {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("gameclear.png");
	textureHandleKey_ = TextureManager::Load("enter.png");

	// スプライトの生成
	sprite_.reset(Sprite::Create(textureHandle_, {0, 0}));
	spriteKey_.reset(Sprite::Create(textureHandleKey_, {400, 500}));
}

bool GameClear::Update() {
	timer_++;
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		return true;
	}
	return false;
}

void GameClear::Draw() {
	sprite_->Draw();
	if (timer_ % 40 < 20) {
		spriteKey_->Draw();
	}
}
