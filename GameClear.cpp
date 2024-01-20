#include "GameClear.h"

#include "Title.h"
#include "TextureManager.h"

void GameClear::Initialize(
    Sprite* spriteGameClear, Sprite* spriteKey, 
	uint32_t textureHandleGameClear, uint32_t textureHandleKey) {

	// ファイル名を指定してテクスチャを読み込む
	textureHandleGameClear_ = textureHandleGameClear;
	textureHandleKey_ = textureHandleKey;

	// スプライトの生成
	spriteGameClear_ = spriteGameClear;
	spriteKey_ = spriteKey;
}

bool GameClear::Update() {
	timer_++;
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		return true;
	}
	return false;
}

void GameClear::Draw() {
	spriteGameClear_->Draw();
	if (timer_ % 40 < 20) {
		spriteKey_->Draw();
	}
}
