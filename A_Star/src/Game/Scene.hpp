#pragma once

#include<iostream>
#include "../../../lib/ci_ext/object.hpp"
#include "GameManager.hpp"

#include "MainGameEntry\MainGameEntry.hpp"
#include "ThreadAdmin.hpp"

namespace Manager
{
	GameManager* GameManager::m_pGamemanager;
	ThreadAdmin* ThreadAdmin::m_pThreadAdmin;
}


class Scene :public ci_ext::Object
{
	Manager::GameManager* m_pGamemanager = Manager::GameManager::GetInstance();
	Manager::ThreadAdmin* m_pThreadAdmin = Manager::ThreadAdmin::GetInstance();

public:
	Scene(const std::string& objectName)
		:
		Object(objectName)
	{

	}

	void update()override
	{
		switch (m_pGamemanager->Get_NowGameScene())
		{
		case Manager::GameManager::Title:

			pause();
			break;

		case Manager::GameManager::MainGame:
			insertAsChild(new MainGameEntry());
			pause();
			break;

		case Manager::GameManager::End:
			break;

		}
	}


	~Scene()
	{
		m_pGamemanager->Delete();
		m_pThreadAdmin->Delete();
	}

};

