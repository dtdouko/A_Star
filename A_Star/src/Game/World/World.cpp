
#include "World.h"


std::map<std::pair<int, int>, Cell*>World::m_Cells;
double World::m_dWorldWidth;
double World::m_dWorldHeight;
double World::m_dCellPartitionSize;

/*
@brief ユークリッドの互除法
@param a 数値１
@param b 数値２
@return 数値１と数値2の最大公約数
*/
int GCD(int a, int b)
{
	int c;

	if (a < b) {
		a += b; b = a - b; a -= b;
	}

	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}

	return a;
}

World::World(const double WorldWidth, const double WorldHeight,const double CellPartitionSize)
	:
	Object("World")
{
	m_dWorldWidth = WorldWidth;
	m_dWorldHeight = WorldHeight;
	m_dCellPartitionSize = CellPartitionSize;
	if(!CellPartitionSize)//サイズが指定されていない時
		m_dCellPartitionSize = GCD(static_cast<int>(m_dWorldWidth), static_cast<int>(m_dWorldHeight));//XとYの最大公約数からセルのサイズを決定する。

	for (int width = 0; width < static_cast<int>(m_dWorldWidth / m_dCellPartitionSize); ++width)//width=IndexX
		for (int height = 0; height < static_cast<int>(m_dWorldHeight / m_dCellPartitionSize); ++height)//height=IndexY
			m_Cells.insert(std::make_pair(std::make_pair(width, height), new Cell(Vector2D(width*m_dCellPartitionSize + m_dCellPartitionSize / 2, height*m_dCellPartitionSize + m_dCellPartitionSize / 2), m_dCellPartitionSize, Cell::normal)));//セルの生成
}

World::~World()
{
	for (auto& cell : m_Cells)
		delete cell.second;
}

Cell* World::IndexToCell(int IndexX, int IndexY)
{
	std::map<std::pair<int, int>, Cell*>::iterator itr = m_Cells.find(std::make_pair(IndexX, IndexY));

	if (itr != m_Cells.end())
		return itr->second;
	else
		return nullptr;
}

Cell*  World::PositionToCell(Vector2D Position)
{
	int IndexX = static_cast<int>(m_dWorldWidth / m_dCellPartitionSize* Position.x / m_dWorldWidth);
	int IndexY = static_cast<int>(m_dWorldHeight / m_dCellPartitionSize * Position.y / m_dWorldHeight);

	return IndexToCell(IndexX, IndexY);
}

const std::pair<int, int> World::CellToIndex(Cell* cell)
{
	for (auto& cells : m_Cells)
	{
		if (cells.second == cell)
			return cells.first;
	}
	return std::make_pair(-1, -1);
}

void World::init()
{
	for (auto& cell : m_Cells)
		cell.second->Set_NeighborCells(IndexToCell(cell.first.first, cell.first.second - 1),IndexToCell(cell.first.first + 1, cell.first.second),IndexToCell(cell.first.first, cell.first.second + 1),IndexToCell(cell.first.first - 1, cell.first.second));
}

void World::update()
{
	for (auto& cell : m_Cells)
		cell.second->Update();
}

void World::render()
{
	for (auto& cell : m_Cells)
		cell.second->Render();
}