#pragma once

#include <memory>

#include "../../../../lib/ci_ext/object.hpp"
#include "../ObjectBase/MovingEntity.h"

/*
@class Agent
@brief キャラクター管理クラス
*/
class Agent :public ci_ext::Object
{
	std::shared_ptr<MovingEntity> m_pAgent;//<! @brief キャラクターポインタ

public:
	/*
	@brief コンストラクタ
	*/
	Agent();
	/*
	@brief デストラクタ
	*/
	~Agent();
	/*
	@brief 更新処理
	*/
	void update() override;
	/*
	@brief 描画処理
	*/
	void render() override;
};