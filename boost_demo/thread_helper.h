#pragma once

#include <thread>
#include <vector>
#include <boost/thread.hpp>
using namespace std;

extern int g_i;

class ModuleWithThread
{
public:
	ModuleWithThread();
	virtual bool Initialize();
	virtual void Destroy();

protected:
	virtual int run();
	virtual void Work() = 0;
	boost::thread m_oThread;
	bool m_bThreadCreate;
	volatile bool m_bQuit;
};

class Thread_AddNum_NoLock :public ModuleWithThread
{
	void Work();
};

class Thread_AddNum_Lock :public ModuleWithThread
{
	void Work();
};

class Thread_Read :public ModuleWithThread
{
	void Work();
};

class Thread_Write :public ModuleWithThread
{
	void Work();
};