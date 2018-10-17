#pragma once

#include <map>


#include "../../ObjectBase/Vector2D.hpp"

/*
@class Cell
@brief フィールドを分割セルのクラス
*/
class Cell
{
public:
	/*
	@enum CellType
	@brief セルの種類列挙
	*/
	enum
	{
		normal,
		wall,
		route,
		goal,
	};
	/*
	@enum Direction
	@brief 方角の列挙
	*/
	enum
	{
		north,
		east,
		south,
		west
	};

private:

	int m_iType;//!< @brief セルの状態

	Vector2D m_vCenter;//!< @brief セルの中心座標

	double m_dSize;//!< @brief セルの大きさ

	Cell* m_NeighborCells[4];//!< @brief セルに隣接セルのポインタを格納。0北1東2南3西

	Cell* m_pParent = nullptr;//!< @brief 親となるセルのポインタを格納。Ａ*で使用

	int m_iCost = 0;//!< @brief セルのコスト。A*で使用

	int m_iScore = 0;//!< @brief セルのスコア。通常、コスト+ヒューリスティックコストとなる。A*で使用

	static Cell* m_pGoal;//!< @brief ゴールに指定されているセルのポインタ

	bool m_bFill;//!< @brief 塗りつぶし

	/*
	struct Color
	@brief 色の宣言に使用
	*/
	struct
	{
		int m_iAlpha;
		int m_iRed;
		int m_iGreen;
		int m_iBlue;
	}m_FillColor, m_FrameColor;

public:
	/*
	@brief コンストラクタ
	@param Center セルの中心座標
	@param Size セルのサイズ
	@param Type セルの種類
	*/
	Cell(Vector2D Center,double Size, int Type = normal);
	/*
	@brief デストラクタ
	*/
	~Cell();
	/*
	@brief セルの種類取得
	@return セルの種類
	*/
	int Get_Type() const { return m_iType; }
	/*
	@brief セルの種類設定
	@param new_type セルの種類
	*/
	void Set_Type(int new_type) { m_iType = new_type; }
	/*
	@brief セルの中心座標取得
	@return セルの中心座標
	*/
	Vector2D Get_Center() const { return m_vCenter; }
	/*
	@brief セルのサイズ取得
	@return セルのサイズ
	*/
	double Get_CellSize() const { return m_dSize; }
	/*
	@brief セルに隣接セルのポインタ設定
	@param pNorth 北のセル
	@param pEast 東のセル
	@param pSouth 南のセル
	@param pWest 西のセル
	*/
	void Set_NeighborCells(Cell* pNorth, Cell* pEast, Cell* pSouth, Cell* pWest) { m_NeighborCells[north] = pNorth; m_NeighborCells[east] = pEast; m_NeighborCells[south] = pSouth; m_NeighborCells[west] = pWest; }
	/*
	@brief 指定した方向に隣接するセルのポインタ取得
	@param direction 方角
	@return 指定した方向に隣接するセルのポインタ
	*/
	Cell* Get_TheAdjacentDirectionCell(int direction) const { return m_NeighborCells[direction]; }
	/*
	@brief セルの親となるセルのポインタ取得
	@return 親ポインタ
	*/
	Cell* Get_Parent() const { return m_pParent; }
	/*
	@brief 親となるセルのポインタ設定
	@param 親のポインタ
	*/
	void Set_Parent(Cell* pCell) { m_pParent = pCell; }
	/*
	@brief コストの設定
	@param new_cost コスト
	*/
	void Set_Cost(int new_cost) { m_iCost = new_cost; }
	/*
	@brief コストの取得
	@return コスト
	*/
	int Get_Cost() const { return m_iCost; }
	/*
	@brief スコアの設定
	@param new_score スコア
	*/
	void Set_Score(int new_score) { m_iScore = new_score; }
	/*
	@brief スコアの取得
	@return スコア
	*/
	int Get_Score() const { return m_iScore; }
	/*
	@brief 塗りつぶし有効化
	*/
	void Enable_Fill() { m_bFill = true; }
	/*
	@brief 塗りつぶし無効化
	*/
	void Disable_Fill() { m_bFill = false; }
	/*
	@brief 塗りつぶしの色設定
	@param Alpha アルファ
	@param Red 赤
	@param Green 緑
	@param Blue 青
	*/
	void Set_FillColor(int Alpha, int Red, int Green, int Blue) { m_FillColor.m_iAlpha = Alpha; m_FillColor.m_iRed = Red; m_FillColor.m_iGreen = Green; m_FillColor.m_iBlue = Blue; }
	/*
	@brief セルの更新
	*/
	void Update();
	/*
	@brief セルの描画
	*/
	void Render();
};