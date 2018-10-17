
#include "Agent.h"

#include "../../../../lib/gplib.h"
#include "../World/World.h"
#include "../Navigation/Naviogation.h"

Agent::Agent()
	:
	Object("Agent")
{
	m_pAgent = std::shared_ptr<MovingEntity>(new MovingEntity("", "", 0, 0, 0, 0, World::IndexToCell(5, 5)->Get_Center(), Vector2D(0, 0), 0.0, World::Get_CellPartitionSize() / 4.0, 1.0, Vector2D(1.0, 1.0), World::Get_CellPartitionSize(), BaseGameEntity::type_player));//Agent生成
}

Agent::~Agent()
{

}

void Agent::update()
{
	m_pAgent->Move();//キャラクターが移動するために必要な処理

	if (!Navigation::Get_Route()->empty())//ルートが生成されたら処理を開始
	{
		m_pAgent->Steering()->ArriveOn();
		m_pAgent->Steering()->SetTarget(Navigation::Get_Route()->front()->Get_Center());
		if (m_pAgent->Pos().Distance(Navigation::Get_Route()->front()->Get_Center()) < 0.1)
		{
			Navigation::Get_Route()->front()->Set_Type(Cell::normal);
			Navigation::Get_Route()->pop_front();
		}
	}
	else
	{
		if (World::PositionToCell(m_pAgent->Pos()))
			m_pAgent->SetPos(World::PositionToCell(m_pAgent->Pos())->Get_Center());
		else
			m_pAgent->SetPos(Navigation::Get_GoalNode()->Get_Center());
		m_pAgent->SetVelocity(Vector2D(0, 0));
		m_pAgent->Steering()->ArriveOff();
	}
}

void Agent::render()
{
	gplib::graph::Draw_Circle(static_cast<float>(m_pAgent->Pos().x), static_cast<float>(m_pAgent->Pos().y), static_cast<float>(m_pAgent->Get_Z()), static_cast<float>(World::Get_CellPartitionSize())/2.f, ARGB(255, 0, 255, 0));
}