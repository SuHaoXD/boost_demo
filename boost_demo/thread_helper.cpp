#include "stdafx.h"
#include "thread_helper.h"
#include <iostream>
#include <boost/thread.hpp>
#include <map>
#include <ctime>
#include <windows.h>
#include <cstdlib>
//#include <functional>
using namespace std;

int g_i = 0;
boost::mutex g_mutex;
boost::shared_mutex g_read_write_mutex;
map<int,double> g_map;


ModuleWithThread::ModuleWithThread():m_bQuit(false),m_bThreadCreate(false){}

bool ModuleWithThread::Initialize()
{
	try
	{
		if (m_bThreadCreate)
		{
			ModuleWithThread::Destroy();
		}
		m_oThread = boost::thread(boost::bind(&ModuleWithThread::run, this));
		m_bThreadCreate = true;
		return true;
	}
	catch(const exception &e)
	{
		(void)e;
		return false;
	}
}

void ModuleWithThread::Destroy()
{
	m_bQuit = true;
	m_oThread.join();
	m_bQuit = false;
	m_bThreadCreate = false;
}

int ModuleWithThread::run()
{
	//while (!m_bQuit)
	//{
		this->Work();
	//}
	return 0;
}

void Thread_AddNum_NoLock::Work()
{
	for (int i = 0; i < 1000000; ++i)
	{
		g_i += 1;
		//g_i -= 1;
	}
	cout << "Addִ����ϣ�" << endl;
}

void Thread_AddNum_Lock::Work()
{
	for (int i = 0; i < 1000000; ++i)
	{
		boost::lock_guard<boost::mutex> lockguard(g_mutex);
		g_i += 1;
		//g_i -= 1;
	}
	cout << "Addִ����ϣ�" << endl;
}

void Thread_Read::Work()
{
	while (true) 
	{
		boost::shared_lock<boost::shared_mutex> lock(g_read_write_mutex);
		cout << "idΪ" << boost::this_thread::get_id() << "���߳̿�ʼ��ȡ" << endl;

		for (auto &e : g_map)
		{
			cout <<"("<<e.first<<","<<e.second << ")"<<endl;
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(rand() % 400 + 100));
		cout << "idΪ" << boost::this_thread::get_id() << "���̶߳�ȡ���" << endl;
	}
}

void Thread_Write::Work()
{
	while (true)
	{
		boost::unique_lock<boost::shared_mutex> lock(g_read_write_mutex);
		cout << "idΪ" << boost::this_thread::get_id() << "���߳̿�ʼд��" << endl;
		g_map.insert(pair<int, double>(rand() % 1000, (double)(clock()) / CLOCKS_PER_SEC));
		boost::this_thread::sleep(boost::posix_time::milliseconds(rand() % 200 + 100));
		cout << "idΪ" << boost::this_thread::get_id() << "���߳�д�����" << endl;
	}
}