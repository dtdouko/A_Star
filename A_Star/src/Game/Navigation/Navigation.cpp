
#include "Naviogation.h"
#ifdef _DEBUG
#include <boost\timer.hpp>
#endif
#include "../../../../lib/gplib.h"

#include "../ObjectBase/MovingEntity.h"


bool Navigation::m_bCreateRoute;
Cell* Navigation::m_pGoalNode;
MovingEntity* Navigation::m_pAgent;
std::list<Cell*> Navigation::m_lRoute;
Navigation::Navigation()
	:
	Object("Navigation")
{
	m_bCreateRoute = false;
	m_pAgent = MovingEntity::Get_Entities()->back();
	m_pThreadAdminInstance = Manager::ThreadAdmin::GetInstance();
	m_ThreadId = std::thread::id();
}

Navigation::~Navigation()
{

}

void Navigation::update()
{
	ChengeCellStatus();

	if (m_bCreateRoute)
	{
		m_bCreateRoute = false;
		for (auto& route : m_lRoute)
			route->Set_Type(Cell::normal);
		m_lRoute.clear();

		m_pThreadAdminInstance->DetachThread(m_ThreadId);
		m_ThreadId = m_pThreadAdminInstance->CreateThread(new std::thread(&Navigation::AStar, this));

	}
}

void Navigation::ChengeCellStatus()
{
	//セルの初期化
	if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
	{
		m_lClosed.clear();
		m_lOpen.clear();
		m_lRoute.clear();
		for (auto& cell : *World::Get_AllCells())
			cell.second->Set_Type(Cell::normal);
	}
	//セルの状態変更
	if (Cell* celectCell = World::PositionToCell(Vector2D(gplib::input::GetMousePosition().x, gplib::input::GetMousePosition().y)))
	{
		switch (celectCell->Get_Type())
		{
		case Cell::normal:
			celectCell->Set_FillColor(100, 255, 255, 255);
			celectCell->Enable_Fill();

			if (World::PositionToCell(m_pAgent->Pos()) != celectCell)
			{
				if (gplib::input::CheckPush(gplib::input::KEY_MOUSE_LBTN))
					celectCell->Set_Type(Cell::wall);
				if (gplib::input::CheckPush(gplib::input::KEY_MOUSE_RBTN))
				{
					if (m_pGoalNode)
						m_pGoalNode->Set_Type(Cell::normal);
					celectCell->Set_Type(Cell::goal);
					m_pGoalNode = celectCell;
					m_bCreateRoute = true;
				}
			}
			break;
		case Cell::wall:
			if (gplib::input::CheckPush(gplib::input::KEY_MOUSE_LBTN))
				celectCell->Set_Type(Cell::normal);
			break;
		}
	}

	//エージェントがゴールしたらゴールセルの状態を変更
	if (Cell* cell = World::PositionToCell(m_pAgent->Pos()))
	{
		if (cell->Get_Type() == Cell::goal)
			cell->Set_Type(Cell::normal);
	}


}

void Navigation::CalcScore(Cell* Node)
{
	Node->Set_Cost(Node->Get_Parent()->Get_Cost() + 1);//親ノードのコスト+1をコストに設定
	//コスト+ヒューリスティックコストをスコアに設定
	//ゴールとスタートノードのインデックスの絶対値を合計したものをヒューリスティックコストとする
	Node->Set_Score(Node->Get_Cost() + (abs(World::CellToIndex(Node).first - World::CellToIndex(m_pGoalNode).first) + abs(World::CellToIndex(Node).second - World::CellToIndex(m_pGoalNode).second)));
}

Cell* Navigation::Get_MostCheapNode()
{
	//オープンリストをスコアで昇順に並び替え、先頭のセルを返す
	m_lOpen.sort([&](Cell* cell, Cell* cell2) -> bool {return cell->Get_Score() < cell2->Get_Score(); });
	return m_lOpen.front();
}

void Navigation::AStar()
{
#ifdef _DEBUG
	boost::timer T;
#endif
	while(!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id())){}
	try
	{
		while (!m_bCreateRoute)//ルートができるまで評価を続ける
		{
			if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
			m_lOpen.push_back(World::PositionToCell(m_pAgent->Pos()));//開始地点のノードをオープンリストに追加
			while (!m_lOpen.empty())
			{
				if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
				Cell* NowNode = Get_MostCheapNode();//現在のノードを、オープンリストの最も安価なスコアのノードに設定
				if (NowNode->Get_Type() == Cell::goal)
				{
					if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
					m_lRoute.clear();//ルートを初期化
					m_lRoute.push_front(m_pGoalNode);//ゴールノードをルートの先頭に追加
					while (m_lRoute.front()->Get_Parent())//親のポインタがullptrになるまでたどりルートを生成
						m_lRoute.push_front(m_lRoute.front()->Get_Parent());
					//ルートになったセルの状態を変更
					for (auto& route : m_lRoute)
					{
						if (route->Get_Type() != Cell::goal)
							route->Set_Type(Cell::route);
					}
					//すべてのセルの親を初期化
					for (auto& cell : *World::Get_AllCells())
						cell.second->Set_Parent(nullptr);

					m_lOpen.clear();
					m_lClosed.clear();
					m_bCreateRoute = false;
#ifdef _DEBUG
					std::cout << T.elapsed() << std::endl;
#endif
					return;
				}
				else
				{
					if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
					m_lClosed.push_back(NowNode);//現在のノードをクローズドリストに移動
					//隣接するセルの検索
					for (int i = 0; i <= 4; i++)
					{
						if (Cell* Neighbor = NowNode->Get_TheAdjacentDirectionCell(i))//nullptrの場合があるため
						{
							std::list<Cell*>::iterator itr;
							itr = std::find(m_lOpen.begin(), m_lOpen.end(), Neighbor);
							if (itr == m_lOpen.end())//ノードがオープンリストに含まれていないか
							{
								itr = std::find(m_lClosed.begin(), m_lClosed.end(), Neighbor);
								if (itr == m_lClosed.end())//ノードがクローズドリストに含まれていないか
								{
									if (Neighbor->Get_Type() != Cell::wall)//障害物ではないか
									{
										Neighbor->Set_Parent(NowNode);//親の設定
										CalcScore(Neighbor);//スコア計算
										m_lOpen.push_back(Neighbor);//オープンリストに追加
									}
								}
							}
						}
					}
					m_lOpen.pop_front();//オープンリストから検索が終わったノードを削除
				}
			}
			//ルート作成後オープンリスト、クローズドリストを初期化
			m_lOpen.clear();
			m_lClosed.clear();
		}
	}
	catch(...)
	{
		return;
	}
}
