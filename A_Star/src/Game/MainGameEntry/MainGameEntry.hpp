#pragma once

#include "../../../../lib/ci_ext/object.hpp"
#include "../../../../lib/gplib.h"

#include "../ThreadAdmin.hpp"

#include "../World/World.h"
#include "../Agent/Agent.h"
#include "../Navigation/Naviogation.h"
#include "../Meta/Meta.h"
/*
@class MainGameEntry
@brief ���C���Q�[���̃G���g���|�C���g
*/
class MainGameEntry :public ci_ext::Object
{

public:
	/*
	@brief �R���X�g���N�^
	�I�u�W�F�N�g�����͊�{�R���X�g���N�^�ōs��
	*/
	MainGameEntry()
		:
		Object("MainGameEntry")
	{
		insertAsChild(new World((double)gplib::system::WINW, (double)gplib::system::WINH,40));
		insertAsChild(new Agent());
		insertAsChild(new Navigation());
		insertAsChild(new Meta());
	}
	/*
	@brief �f�X�g���N�^
	*/
	~MainGameEntry()
	{

	}
	/*
	@brief �`�揈��
	*/
	void render() override
	{

	}
};
