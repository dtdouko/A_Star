#pragma once

#include <map>

#include "../../../../lib/ci_ext/object.hpp"

#include "Cell\Cell.h"

/*
@class World
@brief �t�B�[���h�쐬�N���X
*/
class World :public ci_ext::Object
{

	static std::map<std::pair<int, int>, Cell*>m_Cells;//<! @brief �Z�����i�[�Bfirst���C���f�b�N�XXsecond���C���f�b�N�XY

	static double m_dWorldWidth;//<! @brief �t�B�[���h�T�C�Y�@X

	static double m_dWorldHeight;//<! @brief �t�B�[���h�T�C�Y�@Y

	static double m_dCellPartitionSize;//<! @brief �t�B�[���h�𕪊�����Z���̃T�C�Y

public:
	/*
	@brief �R���X�g���N�^
	@param WorldWidth �t�B�[���h�T�C�Y�@X
	@param WorldHeight �t�B�[���h�T�C�Y�@Y
	@param CellPartitionSize �Z���̃T�C�Y 
	*/
	World(const double WorldWidth,const double WorldHeight,const double CellPartitionSize=NULL);
	/*
	@brief �f�X�g���N�^
	*/
	~World();
	/*
	@brief m_Cells�|�C���^�擾
	@return &m_Cells
	*/
	static std::map<std::pair<int, int>, Cell*>* Get_AllCells() { return &m_Cells; }
	/*
	@brief �w�肵���C���f�b�N�X�̃Z���̃|�C���^�擾
	@param IndexX �C���f�b�N�XX
	@param IndexY �C���f�b�N�XY
	@return �Y���Z���̃|�C���^�B���݂��Ȃ��ꍇ��nullptr
	*/
	static Cell* IndexToCell(int IndexX, int IndexY);
	/*
	@brief �w�肵�����W������Z���̃|�C���^�擾
	@param Position ���W
	@return �Y������̃|�C���^�B���݂��Ȃ��ꍇ��nullptr
	*/
	static Cell* PositionToCell(Vector2D Position);
	/*
	@brief �w�肵���Z���̃C���f�b�N�X�擾
	@param cell �Z���̃|�C���^
	@return �w��Z���̃C���f�b�N�X�Bfirst��X�Asecond��Y
	*/
	static const std::pair<int, int> CellToIndex(Cell* cell);
	/*
	@brief �t�B�[���h�̕��擾
	@return �t�B�[���h��
	*/
	static double Get_WorldWidth() { return m_dWorldWidth; }
	/*
	@brief �t�B�[���h�̍����擾
	@return �t�B�[���h����
	*/
	static double Get_WorldHeight() { return m_dWorldHeight; }
	/*
	@brief �Z���̃T�C�Y�擾
	@return �Z���̃T�C�Y
	*/
	static double Get_CellPartitionSize() { return m_dCellPartitionSize; }
	/*
	@brief ����������
	*/
	void init() override;
	/*
	@brief �X�V����
	*/
	void update() override;
	/*
	@brief �`�揈��
	*/
	void render() override;
};