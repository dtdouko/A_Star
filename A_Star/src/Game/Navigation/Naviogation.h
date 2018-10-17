#pragma once

#include <vector>
#include <list>

#include "../../../../lib/ci_ext/object.hpp"

#include "../ThreadAdmin.hpp"
#include "../World/World.h"


class MovingEntity;
/*
@class Navigation
@brief �i�r�Q�[�V�����N���X�B���[�g�̍쐬�A�Z���̏�Ԃ��Ǘ�����
*/
class Navigation:public ci_ext::Object
{
	static MovingEntity* m_pAgent;//<! @brief �i�r�Q�[�V�����Ώۂ̃G�[�W�F���g

	std::list<Cell*> m_lOpen;//! @brief �I�[�v���m�[�h���X�g
	std::list<Cell*> m_lClosed;//! @brief �N���[�Y�h�m�[�h���X�g

	Manager::ThreadAdmin* m_pThreadAdminInstance;
	std::thread::id m_ThreadId;//! @brief ���[�g�v�Z�X���b�h 

	static std::list<Cell*> m_lRoute;//! @brief ���[�g�m�[�h

	static Cell* m_pGoalNode;//! @brief �S�[���m�[�h

	static bool m_bCreateRoute;//! @brief ���[�g�����t���O
	/*
	@brief �X�R�A�v�Z
	@param Node �v�Z�Ώۂ̃m�[�h
	*/
	void CalcScore(Cell* Node);
	/*
	@brief �I�[�v�����X�g�̂����Ƃ��X�R�A���������m�[�h���擾
	@return �Y���m�[�h�̃|�C���^
	*/
	Cell* Get_MostCheapNode();
public:
	/*
	@brief �R���X�g���N�^
	*/
	Navigation();
	/*
	@brief �f�X�g���N�^
	*/
	~Navigation();
	/*
	@brief �X�V����
	*/
	void update() override;
	/*
	@brief �Z���̏�ԊǗ�
	*/
	void ChengeCellStatus();
	/*
	@brief A*�A���S���Y��
	*/
	void AStar();
	/*
	@brief �����������[�g�̃|�C���^�擾
	@return m_lRoute�̃|�C���^
	*/
	static std::list<Cell*> *Get_Route() { return &m_lRoute; }
	/*
	@brief �G�[�W�F���g�̃|�C���^�擾
	@return �G�[�W�F���g�̃|�C���^
	*/
	static MovingEntity* Get_Agent() { return m_pAgent; }
	/*
	@brief �S�[���m�[�h�̃|�C���^�擾
	@return �S�[���m�[�h�̃|�C���^
	*/
	static Cell* Get_GoalNode() { return m_pGoalNode; }
	/*
	@brief �S�[���m�[�h�̎擾
	@param new_goalnode �ݒ肷��m�[�h
	*/
	static void Set_GoalNode(Cell* new_goalnode) { m_pGoalNode = new_goalnode; }
	/*
	@brief ���[�g�쐬�t���O�擾
	*/
	static bool IsCreateRoute() { return m_bCreateRoute; }
	/*
	@brief ���[�g�쐬�J�n
	*/
	static void Do_CreateRoute() { m_bCreateRoute = true; }
};
