#pragma once

#include <map>


#include "../../ObjectBase/Vector2D.hpp"

/*
@class Cell
@brief �t�B�[���h�𕪊��Z���̃N���X
*/
class Cell
{
public:
	/*
	@enum CellType
	@brief �Z���̎�ޗ�
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
	@brief ���p�̗�
	*/
	enum
	{
		north,
		east,
		south,
		west
	};

private:

	int m_iType;//!< @brief �Z���̏��

	Vector2D m_vCenter;//!< @brief �Z���̒��S���W

	double m_dSize;//!< @brief �Z���̑傫��

	Cell* m_NeighborCells[4];//!< @brief �Z���ɗאڃZ���̃|�C���^���i�[�B0�k1��2��3��

	Cell* m_pParent = nullptr;//!< @brief �e�ƂȂ�Z���̃|�C���^���i�[�B�`*�Ŏg�p

	int m_iCost = 0;//!< @brief �Z���̃R�X�g�BA*�Ŏg�p

	int m_iScore = 0;//!< @brief �Z���̃X�R�A�B�ʏ�A�R�X�g+�q���[���X�e�B�b�N�R�X�g�ƂȂ�BA*�Ŏg�p

	static Cell* m_pGoal;//!< @brief �S�[���Ɏw�肳��Ă���Z���̃|�C���^

	bool m_bFill;//!< @brief �h��Ԃ�

	/*
	struct Color
	@brief �F�̐錾�Ɏg�p
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
	@brief �R���X�g���N�^
	@param Center �Z���̒��S���W
	@param Size �Z���̃T�C�Y
	@param Type �Z���̎��
	*/
	Cell(Vector2D Center,double Size, int Type = normal);
	/*
	@brief �f�X�g���N�^
	*/
	~Cell();
	/*
	@brief �Z���̎�ގ擾
	@return �Z���̎��
	*/
	int Get_Type() const { return m_iType; }
	/*
	@brief �Z���̎�ސݒ�
	@param new_type �Z���̎��
	*/
	void Set_Type(int new_type) { m_iType = new_type; }
	/*
	@brief �Z���̒��S���W�擾
	@return �Z���̒��S���W
	*/
	Vector2D Get_Center() const { return m_vCenter; }
	/*
	@brief �Z���̃T�C�Y�擾
	@return �Z���̃T�C�Y
	*/
	double Get_CellSize() const { return m_dSize; }
	/*
	@brief �Z���ɗאڃZ���̃|�C���^�ݒ�
	@param pNorth �k�̃Z��
	@param pEast ���̃Z��
	@param pSouth ��̃Z��
	@param pWest ���̃Z��
	*/
	void Set_NeighborCells(Cell* pNorth, Cell* pEast, Cell* pSouth, Cell* pWest) { m_NeighborCells[north] = pNorth; m_NeighborCells[east] = pEast; m_NeighborCells[south] = pSouth; m_NeighborCells[west] = pWest; }
	/*
	@brief �w�肵�������ɗאڂ���Z���̃|�C���^�擾
	@param direction ���p
	@return �w�肵�������ɗאڂ���Z���̃|�C���^
	*/
	Cell* Get_TheAdjacentDirectionCell(int direction) const { return m_NeighborCells[direction]; }
	/*
	@brief �Z���̐e�ƂȂ�Z���̃|�C���^�擾
	@return �e�|�C���^
	*/
	Cell* Get_Parent() const { return m_pParent; }
	/*
	@brief �e�ƂȂ�Z���̃|�C���^�ݒ�
	@param �e�̃|�C���^
	*/
	void Set_Parent(Cell* pCell) { m_pParent = pCell; }
	/*
	@brief �R�X�g�̐ݒ�
	@param new_cost �R�X�g
	*/
	void Set_Cost(int new_cost) { m_iCost = new_cost; }
	/*
	@brief �R�X�g�̎擾
	@return �R�X�g
	*/
	int Get_Cost() const { return m_iCost; }
	/*
	@brief �X�R�A�̐ݒ�
	@param new_score �X�R�A
	*/
	void Set_Score(int new_score) { m_iScore = new_score; }
	/*
	@brief �X�R�A�̎擾
	@return �X�R�A
	*/
	int Get_Score() const { return m_iScore; }
	/*
	@brief �h��Ԃ��L����
	*/
	void Enable_Fill() { m_bFill = true; }
	/*
	@brief �h��Ԃ�������
	*/
	void Disable_Fill() { m_bFill = false; }
	/*
	@brief �h��Ԃ��̐F�ݒ�
	@param Alpha �A���t�@
	@param Red ��
	@param Green ��
	@param Blue ��
	*/
	void Set_FillColor(int Alpha, int Red, int Green, int Blue) { m_FillColor.m_iAlpha = Alpha; m_FillColor.m_iRed = Red; m_FillColor.m_iGreen = Green; m_FillColor.m_iBlue = Blue; }
	/*
	@brief �Z���̍X�V
	*/
	void Update();
	/*
	@brief �Z���̕`��
	*/
	void Render();
};