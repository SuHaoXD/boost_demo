// boost_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <thread>
#include <time.h>
#include <windows.h>
#include "biology.h"
#include "thread_helper.h"
#include <ctime>
#include <atomic>

using namespace std;

void PrintNumber();
void PrintAlphabetUpper();
void PrintAlphabetLower();
void MutexDemo_NoLock();
void MutexDemo_Lock();
void Read_Write_Demo();


//atomic<int> g_i(0);

int main()
{	
	extern int g_i;
	srand(time(0));
	boost::scoped_ptr<Human> h1(new Human("1","张三",22,'M',"33123531","烽火"));
	boost::shared_ptr<Human> h2(new Human);
	boost::scoped_array<int> h3(new int[4]{0});
	cout << h3[3] << endl;
	h1->PrintInfo();
	h2->PrintInfo();

	//UsingSyn();
	//Plus_and_Min();
	//measure(Plus);                            //非原子操作，无同步 0.02S；   原子操作，同步 0.21S；   互斥量，同步  0.114S;

	//MutexDemo_NoLock();    //互斥量
	//MutexDemo_Lock();

	//Read_Write_Demo();



	
	system("pause");
    return 0;
}


void Read_Write_Demo()
{
	Thread_Read thr1;
	Thread_Read thr2;
	Thread_Read thr3;
	Thread_Read thr4;

	Thread_Write thw1;
	Thread_Write thw2;
	Thread_Write thw3;
	Thread_Write thw4;

	thr1.Initialize();
	thr2.Initialize();
	thr3.Initialize();
	thr4.Initialize();
	thw1.Initialize();
	thw2.Initialize();
	thw3.Initialize();
	thw4.Initialize();

	thr1.Destroy();
	thr2.Destroy();
	thr3.Destroy();
	thr4.Destroy();
	thw1.Destroy();
	thw2.Destroy();
	thw3.Destroy();
	thw4.Destroy();
}

void MutexDemo_NoLock()
{
	Thread_AddNum_NoLock th1;
	Thread_AddNum_NoLock th2;
	Thread_AddNum_NoLock th3;
	Thread_AddNum_NoLock th4;

	th1.Initialize();
	th2.Initialize();
	th3.Initialize();
	th4.Initialize();
	th1.Destroy();
	th2.Destroy();
	th3.Destroy();
	th4.Destroy();
	cout << g_i << endl;
}

void MutexDemo_Lock()
{
	Thread_AddNum_Lock th1;
	Thread_AddNum_Lock th2;
	Thread_AddNum_Lock th3;
	Thread_AddNum_Lock th4;

	th1.Initialize();
	th2.Initialize();
	th3.Initialize();
	th4.Initialize();
	th1.Destroy();
	th2.Destroy();
	th3.Destroy();
	th4.Destroy();
	cout << g_i << endl;
}





















template <class T>
void measure(T &&func)
{
	using namespace std::chrono;
	auto start = system_clock::now();
	func();
	duration<double> diff = system_clock::now() - start;
	cout << "elapsed:" << diff.count() << "seconds" << endl;
}

void PrintNumber()
{
	int i = 1;
	while (true)
	{
		cout << i % 26;
		++i;
		Sleep(500);
	}
}

void PrintAlphabetUpper()
{
	int a = 0;
	while (true)
	{
		if (g_i == 0) 
		{
			cout << (char)(a % 26 + 'A');
			++a;
			Sleep(100);
			++g_i;
		}
	}
}

void PrintAlphabetLower()
{
	int a = 0;
	while (true)
	{
		if (g_i == 1)
		{
			cout << (char)(a % 26 + 'a');
			++a;
			Sleep(100);
			--g_i;
		}
	}
}