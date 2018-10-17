
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
	//�Z���̏�����
	if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
	{
		m_lClosed.clear();
		m_lOpen.clear();
		m_lRoute.clear();
		for (auto& cell : *World::Get_AllCells())
			cell.second->Set_Type(Cell::normal);
	}
	//�Z���̏�ԕύX
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

	//�G�[�W�F���g���S�[��������S�[���Z���̏�Ԃ�ύX
	if (Cell* cell = World::PositionToCell(m_pAgent->Pos()))
	{
		if (cell->Get_Type() == Cell::goal)
			cell->Set_Type(Cell::normal);
	}


}

void Navigation::CalcScore(Cell* Node)
{
	Node->Set_Cost(Node->Get_Parent()->Get_Cost() + 1);//�e�m�[�h�̃R�X�g+1���R�X�g�ɐݒ�
	//�R�X�g+�q���[���X�e�B�b�N�R�X�g���X�R�A�ɐݒ�
	//�S�[���ƃX�^�[�g�m�[�h�̃C���f�b�N�X�̐�Βl�����v�������̂��q���[���X�e�B�b�N�R�X�g�Ƃ���
	Node->Set_Score(Node->Get_Cost() + (abs(World::CellToIndex(Node).first - World::CellToIndex(m_pGoalNode).first) + abs(World::CellToIndex(Node).second - World::CellToIndex(m_pGoalNode).second)));
}

Cell* Navigation::Get_MostCheapNode()
{
	//�I�[�v�����X�g���X�R�A�ŏ����ɕ��ёւ��A�擪�̃Z����Ԃ�
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
		while (!m_bCreateRoute)//���[�g���ł���܂ŕ]���𑱂���
		{
			if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
			m_lOpen.push_back(World::PositionToCell(m_pAgent->Pos()));//�J�n�n�_�̃m�[�h���I�[�v�����X�g�ɒǉ�
			while (!m_lOpen.empty())
			{
				if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
				Cell* NowNode = Get_MostCheapNode();//���݂̃m�[�h���A�I�[�v�����X�g�̍ł������ȃX�R�A�̃m�[�h�ɐݒ�
				if (NowNode->Get_Type() == Cell::goal)
				{
					if (!m_pThreadAdminInstance->SearchThread(std::this_thread::get_id()))throw 0;
					m_lRoute.clear();//���[�g��������
					m_lRoute.push_front(m_pGoalNode);//�S�[���m�[�h�����[�g�̐擪�ɒǉ�
					while (m_lRoute.front()->Get_Parent())//�e�̃|�C���^��ullptr�ɂȂ�܂ł��ǂ胋�[�g�𐶐�
						m_lRoute.push_front(m_lRoute.front()->Get_Parent());
					//���[�g�ɂȂ����Z���̏�Ԃ�ύX
					for (auto& route : m_lRoute)
					{
						if (route->Get_Type() != Cell::goal)
							route->Set_Type(Cell::route);
					}
					//���ׂẴZ���̐e��������
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
					m_lClosed.push_back(NowNode);//���݂̃m�[�h���N���[�Y�h���X�g�Ɉړ�
					//�אڂ���Z���̌���
					for (int i = 0; i <= 4; i++)
					{
						if (Cell* Neighbor = NowNode->Get_TheAdjacentDirectionCell(i))//nullptr�̏ꍇ�����邽��
						{
							std::list<Cell*>::iterator itr;
							itr = std::find(m_lOpen.begin(), m_lOpen.end(), Neighbor);
							if (itr == m_lOpen.end())//�m�[�h���I�[�v�����X�g�Ɋ܂܂�Ă��Ȃ���
							{
								itr = std::find(m_lClosed.begin(), m_lClosed.end(), Neighbor);
								if (itr == m_lClosed.end())//�m�[�h���N���[�Y�h���X�g�Ɋ܂܂�Ă��Ȃ���
								{
									if (Neighbor->Get_Type() != Cell::wall)//��Q���ł͂Ȃ���
									{
										Neighbor->Set_Parent(NowNode);//�e�̐ݒ�
										CalcScore(Neighbor);//�X�R�A�v�Z
										m_lOpen.push_back(Neighbor);//�I�[�v�����X�g�ɒǉ�
									}
								}
							}
						}
					}
					m_lOpen.pop_front();//�I�[�v�����X�g���猟�����I������m�[�h���폜
				}
			}
			//���[�g�쐬��I�[�v�����X�g�A�N���[�Y�h���X�g��������
			m_lOpen.clear();
			m_lClosed.clear();
		}
	}
	catch(...)
	{
		return;
	}
}
