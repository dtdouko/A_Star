#pragma once

#include <memory>

#include "../../../../lib/ci_ext/object.hpp"
#include "../ObjectBase/MovingEntity.h"

/*
@class Agent
@brief �L�����N�^�[�Ǘ��N���X
*/
class Agent :public ci_ext::Object
{
	std::shared_ptr<MovingEntity> m_pAgent;//<! @brief �L�����N�^�[�|�C���^

public:
	/*
	@brief �R���X�g���N�^
	*/
	Agent();
	/*
	@brief �f�X�g���N�^
	*/
	~Agent();
	/*
	@brief �X�V����
	*/
	void update() override;
	/*
	@brief �`�揈��
	*/
	void render() override;
};