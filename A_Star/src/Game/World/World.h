#pragma once

#include <map>

#include "../../../../lib/ci_ext/object.hpp"

#include "Cell\Cell.h"

/*
@class World
@brief フィールド作成クラス
*/
class World :public ci_ext::Object
{

	static std::map<std::pair<int, int>, Cell*>m_Cells;//<! @brief セルを格納。firstがインデックスXsecondがインデックスY

	static double m_dWorldWidth;//<! @brief フィールドサイズ　X

	static double m_dWorldHeight;//<! @brief フィールドサイズ　Y

	static double m_dCellPartitionSize;//<! @brief フィールドを分割するセルのサイズ

public:
	/*
	@brief コンストラクタ
	@param WorldWidth フィールドサイズ　X
	@param WorldHeight フィールドサイズ　Y
	@param CellPartitionSize セルのサイズ 
	*/
	World(const double WorldWidth,const double WorldHeight,const double CellPartitionSize=NULL);
	/*
	@brief デストラクタ
	*/
	~World();
	/*
	@brief m_Cellsポインタ取得
	@return &m_Cells
	*/
	static std::map<std::pair<int, int>, Cell*>* Get_AllCells() { return &m_Cells; }
	/*
	@brief 指定したインデックスのセルのポインタ取得
	@param IndexX インデックスX
	@param IndexY インデックスY
	@return 該当セルのポインタ。存在しない場合はnullptr
	*/
	static Cell* IndexToCell(int IndexX, int IndexY);
	/*
	@brief 指定した座標を内包するセルのポインタ取得
	@param Position 座標
	@return 該当せるのポインタ。存在しない場合はnullptr
	*/
	static Cell* PositionToCell(Vector2D Position);
	/*
	@brief 指定したセルのインデックス取得
	@param cell セルのポインタ
	@return 指定セルのインデックス。firstがX、secondがY
	*/
	static const std::pair<int, int> CellToIndex(Cell* cell);
	/*
	@brief フィールドの幅取得
	@return フィールド幅
	*/
	static double Get_WorldWidth() { return m_dWorldWidth; }
	/*
	@brief フィールドの高さ取得
	@return フィールド高さ
	*/
	static double Get_WorldHeight() { return m_dWorldHeight; }
	/*
	@brief セルのサイズ取得
	@return セルのサイズ
	*/
	static double Get_CellPartitionSize() { return m_dCellPartitionSize; }
	/*
	@brief 初期化処理
	*/
	void init() override;
	/*
	@brief 更新処理
	*/
	void update() override;
	/*
	@brief 描画処理
	*/
	void render() override;
};