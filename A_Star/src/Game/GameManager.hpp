#pragma once

namespace Manager
{
	class GameManager
	{
		static GameManager* m_pGamemanager;

	public:

		enum GameScene
		{
			Title,
			MainGame,
			End,
		};
	private:

		GameScene m_eNowGameScene;

		GameManager()
			:
#ifndef _DEBUG
			m_eNowGameScene((GameScene)1) {}
#else
			m_eNowGameScene(MainGame){}
#endif
		GameManager(const GameManager& p) {}
		GameManager& operator=(const GameManager& p) {}
		~GameManager() {}

	public:
		static GameManager* GetInstance()
		{
			if (!m_pGamemanager)
				m_pGamemanager = new GameManager;
			return m_pGamemanager;
		}
		GameScene Get_NowGameScene() { return m_eNowGameScene; }

		void Change_Scene(GameScene new_Scene) { m_eNowGameScene = new_Scene; }

		void Delete()
		{
			delete m_pGamemanager;
			m_pGamemanager = nullptr;
		}
	};
}