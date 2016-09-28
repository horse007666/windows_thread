#include<Windows.h>
#include<iostream>
#include<process.h>
using namespace std;

struct myelem{
	int a;
	char ch;
};

void myfun(PVOID arg)
{
	cout<<"myfun start..."<<endl;
	int i=100000;
	while(1){
		cout<<"myfun "<<++i<<endl;
		Sleep(1000);
	}
}
void myfun2(PVOID arg)
{
	cout<<"myfun2 start..."<<endl;
	int i=500;
	while(1){
		cout<<"myfun2 "<<++i<<endl;
		Sleep(1000);
		if(i>=505)ExitThread(10);
	}

}
void myfun3(void *p)
{
	cout<<"myfun3 start..."<<endl;
	myelem* myp=(myelem*)p;
	cout<<"myfun3 "<<myp->a<<" "<<myp->ch<<endl;
	ExitThread(111);//设置退出码
	
}

int main()
{
	int i=0;
	//_beginthread 函数
	HANDLE handle=(HANDLE)_beginthread(myfun,0, NULL);
	DWORD sid=0;
	HANDLE handle2=(HANDLE)CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)myfun2,0,0,&sid);
	cout<<sid<<endl;
	myelem e;
	e.a=10;e.ch='A';

	HANDLE handle3=(HANDLE)_beginthread(myfun3,0,&e);//传入参数
	Sleep(1000);
	if(GetExitCodeThread(handle3,&sid))cout<<"sid "<<sid<<endl;
	TerminateThread(handle2,sid+10); 
	Sleep(2000);//如果不加这一句下面的GetExitCodeThread获得的就是259
	GetExitCodeThread(handle2,&sid);cout<<"sid "<<sid<<endl;
	SuspendThread(handle);//suspend
	Sleep(2000);
	
	while(1){
		cout<<++i<<endl;
		Sleep(1000);
		if(i>2)ResumeThread(handle);//resume
	}
}
