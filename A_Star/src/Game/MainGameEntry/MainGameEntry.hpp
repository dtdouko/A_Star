#pragma once

#include "../../../../lib/ci_ext/object.hpp"
#include "../../../../lib/gplib.h"

#include "../ThreadAdmin.hpp"

#include "../World/World.h"
#include "../Agent/Agent.h"
#include "../Navigation/Naviogation.h"
#include "../Meta/Meta.h"
/*
@class MainGameEntry
@brief メインゲームのエントリポイント
*/
class MainGameEntry :public ci_ext::Object
{

public:
	/*
	@brief コンストラクタ
	オブジェクト生成は基本コンストラクタで行う
	*/
	MainGameEntry()
		:
		Object("MainGameEntry")
	{
		insertAsChild(new World((double)gplib::system::WINW, (double)gplib::system::WINH,40));
		insertAsChild(new Agent());
		insertAsChild(new Navigation());
		insertAsChild(new Meta());
	}
	/*
	@brief デストラクタ
	*/
	~MainGameEntry()
	{

	}
	/*
	@brief 描画処理
	*/
	void render() override
	{

	}
};
