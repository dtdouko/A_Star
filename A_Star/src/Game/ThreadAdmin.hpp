#pragma once

#include <iostream>
#include <thread>
#include <unordered_map>

namespace Manager
{

	class ThreadAdmin
	{
	private:
		ThreadAdmin() {}
		ThreadAdmin(const ThreadAdmin&) {}
		ThreadAdmin& operator= (const ThreadAdmin& p){}


		static ThreadAdmin* m_pThreadAdmin;
		std::unordered_map<std::thread::id,std::thread*> m_Threads;
		
		void DetachAllThreads()
		{
			if (!m_Threads.empty())
			{
				std::vector<std::thread*>temp;
				for (auto& thread : m_Threads)
					temp.push_back(thread.second);
				m_Threads.clear();
				for (auto& thread : temp)
				{
					thread->join();
					delete thread;
				}
			}
		}
	public:
		~ThreadAdmin()
		{
			
		}
		static ThreadAdmin* GetInstance()
		{
			if (!m_pThreadAdmin)
				m_pThreadAdmin = new ThreadAdmin;
			return m_pThreadAdmin;
		}


		void Delete()
		{
			DetachAllThreads();
			delete m_pThreadAdmin;
		}

		std::thread::id CreateThread(std::thread* new_thread)
		{
			m_Threads.insert(std::make_pair(new_thread->get_id(), new_thread));
#ifdef _DEBUG
			std::cout << "Start Thread. ID:0x" << std::hex << new_thread->get_id() << std::endl;
#endif
			return new_thread->get_id();
		}

		void DetachThread(std::thread::id threadId) 
		{
			auto itr = m_Threads.find(threadId);
			if (itr != m_Threads.end())
			{
				itr->second->detach();
				delete itr->second;
#ifdef _DEBUG
				std::cout << "END Thread. ID:0x" << std::hex <<itr->first << std::endl;
#endif
				m_Threads.erase(itr);
			}
		}

		void JoinThread(std::thread::id thread)
		{
			auto itr = m_Threads.find(thread);
			if (itr != m_Threads.end())
			{
				itr->second->join();
				delete itr->second;
#ifdef _DEBUG
				std::cout << "END Thread. ID:0x" << std::hex << itr->first << std::endl;
#endif
				m_Threads.erase(itr);
			}
		}

		bool SearchThread(std::thread::id threadId) const
		{
			if (m_Threads.find(threadId) != m_Threads.end())
				return true;
			else
				return false;
		}

	};
}
