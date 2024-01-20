#pragma once
#include "Input.h"
#include "Sprite.h"
#include <memory>

class GameClear {
public:
	// 初期化
	void Initialize();

	// 更新
	bool Update();

	// 描画
	void Draw();

private:
	Input* input_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t textureHandleKey_ = 0;

	// スプライト
	std::unique_ptr<Sprite> sprite_;
	std::unique_ptr<Sprite> spriteKey_;

	// タイマー
	int timer_ = 0;
};
