#pragma once

#include <vector>
#include <list>

#include "../../../../lib/ci_ext/object.hpp"

#include "../ThreadAdmin.hpp"
#include "../World/World.h"


class MovingEntity;
/*
@class Navigation
@brief ナビゲーションクラス。ルートの作成、セルの状態を管理する
*/
class Navigation:public ci_ext::Object
{
	static MovingEntity* m_pAgent;//<! @brief ナビゲーション対象のエージェント

	std::list<Cell*> m_lOpen;//! @brief オープンノードリスト
	std::list<Cell*> m_lClosed;//! @brief クローズドノードリスト

	Manager::ThreadAdmin* m_pThreadAdminInstance;
	std::thread::id m_ThreadId;//! @brief ルート計算スレッド 

	static std::list<Cell*> m_lRoute;//! @brief ルートノード

	static Cell* m_pGoalNode;//! @brief ゴールノード

	static bool m_bCreateRoute;//! @brief ルート生成フラグ
	/*
	@brief スコア計算
	@param Node 計算対象のノード
	*/
	void CalcScore(Cell* Node);
	/*
	@brief オープンリストのもっともスコアが小さいノードを取得
	@return 該当ノードのポインタ
	*/
	Cell* Get_MostCheapNode();
public:
	/*
	@brief コンストラクタ
	*/
	Navigation();
	/*
	@brief デストラクタ
	*/
	~Navigation();
	/*
	@brief 更新処理
	*/
	void update() override;
	/*
	@brief セルの状態管理
	*/
	void ChengeCellStatus();
	/*
	@brief A*アルゴリズム
	*/
	void AStar();
	/*
	@brief 完成したルートのポインタ取得
	@return m_lRouteのポインタ
	*/
	static std::list<Cell*> *Get_Route() { return &m_lRoute; }
	/*
	@brief エージェントのポインタ取得
	@return エージェントのポインタ
	*/
	static MovingEntity* Get_Agent() { return m_pAgent; }
	/*
	@brief ゴールノードのポインタ取得
	@return ゴールノードのポインタ
	*/
	static Cell* Get_GoalNode() { return m_pGoalNode; }
	/*
	@brief ゴールノードの取得
	@param new_goalnode 設定するノード
	*/
	static void Set_GoalNode(Cell* new_goalnode) { m_pGoalNode = new_goalnode; }
	/*
	@brief ルート作成フラグ取得
	*/
	static bool IsCreateRoute() { return m_bCreateRoute; }
	/*
	@brief ルート作成開始
	*/
	static void Do_CreateRoute() { m_bCreateRoute = true; }
};
