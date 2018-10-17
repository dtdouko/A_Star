
#include "../Meta/Meta.h"

#include <boost\random.hpp>

#include "../Navigation/Naviogation.h"
#include "../World/World.h"
#include "../ObjectBase/MovingEntity.h"
#include "../../../../lib/gplib.h"

Meta::Meta()
	:
	Object("Meta"),
	m_bEnable(true),
	m_iResetTime(World::Get_AllCells()->size())
{
	m_dRatioOfWall = 0.25;
	m_iResetTimer = 0;
}

Meta::~Meta()
{

}

template <class T>
inline void Meta::VectorShuffle(std::vector<T> &vec)
{
	boost::mt19937 gen(static_cast<unsigned long>(time(0)));
	boost::uniform_smallint<> dst(0, vec.size()-1);
	boost::variate_generator<boost::mt19937&, boost::uniform_smallint<>>rand(gen, dst);
	for (unsigned int i = 0; i<vec.size(); i++)
	{
		int temp = rand();
		T t = vec[i];
		vec[i] = vec[temp];
		vec[temp] = t;
	}
}

void Meta::CreateWalls()
{
	m_NormalCells.clear();
	for (auto& cell : *World::Get_AllCells())
	{
		if (cell.second->Get_Type() != Cell::normal)
			cell.second->Set_Type(Cell::normal);
		if (cell.second != World::PositionToCell(Navigation::Get_Agent()->Pos()))
			m_NormalCells.push_back(cell.second);
	}
	VectorShuffle<Cell*>(m_NormalCells);
	for (int i = 0; i < static_cast<int>(m_NormalCells.size()*(m_dRatioOfWall)); ++i)
		m_NormalCells[i]->Set_Type(Cell::wall);
}

void Meta::SetGoal()
{
	std::vector<Cell*>Temp;
	for (auto& cell : *World::Get_AllCells())
		if (cell.second->Get_Type() != Cell::wall&&cell.second != World::PositionToCell(Navigation::Get_Agent()->Pos()))
			Temp.push_back(cell.second);
	VectorShuffle<Cell*>(Temp);
	Temp.back()->Set_Type(Cell::goal);
	Navigation::Set_GoalNode(Temp.back());
	Navigation::Do_CreateRoute();
}

void Meta::update()
{
	if (gplib::input::CheckPush(gplib::input::KEY_F1)) {
		if (!m_bEnable) {
			for (auto& cell : *World::Get_AllCells())
				cell.second->Set_Type(Cell::normal);
		}
		m_bEnable = !m_bEnable;
	}
	if (m_bEnable)
	{
		if ((Navigation::Get_GoalNode() && Navigation::Get_GoalNode()->Get_Type() != Cell::goal) || m_iResetTimer-- < 0)
		{
			m_iResetTimer = m_iResetTime;
			CreateWalls();
			SetGoal();
		}
	}

}