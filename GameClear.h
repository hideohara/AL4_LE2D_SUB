#pragma once
#include "Input.h"
#include "Sprite.h"
#include <memory>

class GameClear {
public:
	// 初期化
	void Initialize(
	    Sprite* spriteGameClear, Sprite* spriteKey, uint32_t textureHandleTitle,
	    uint32_t textureHandleKey);
	// 更新
	bool Update();

	// 描画
	void Draw();

private:
	Input* input_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandleGameClear_ = 0;
	uint32_t textureHandleKey_ = 0;

	// スプライト
	Sprite* spriteGameClear_;
	Sprite* spriteKey_;

	// タイマー
	int timer_ = 0;
};
