// OddWriter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>
#include<fstream>
using namespace std;


HANDLE thEvenWriter = NULL;

HANDLE hOddEvent = NULL;
HANDLE hEvenEvent = NULL;
DWORD tEvenId;

fstream fs;


void Write(const char *ch,int i) {

	fs.open("C:\\Users\\Sahil.Tamboli\\source\\CPP\\practice\\mainFile.txt", ios::app);
	fs << ch << i << endl;
	cout << ch << i << endl;
	fs.close();

}
void EvenWriter() {
	Sleep(1000);

	for (int i = 0; i < 20; i+=2)
	{
		
	
		Sleep(1000);
		Write("EVEN WRITER Thread :" , i);
		
		ResetEvent(hEvenEvent);
		SetEvent(hOddEvent);

		DWORD dw1 = WaitForSingleObject(hEvenEvent, INFINITE);
		
	}

}


int main()
{
	hOddEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("EVENT_Odd_2D9A9092-1DAB-4F1A-B8C1-B38702F6C34D"));
	if (GetLastError() != 0 && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		cout << endl << "Event Kernel Object is not created..";
		return EXIT_FAILURE;
	}

	hEvenEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("EVENT_Even_E2F64F32-5320-481A-9329-4CFD41A113FA"));
	if (GetLastError() != 0 && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		cout << endl << "Event Kernel Object is not created..";
		return EXIT_FAILURE;
	}



	thEvenWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)EvenWriter,NULL, 0, &tEvenId);
	if (GetLastError() != 0 && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		cout << endl << "Mutex Kernel Object is not created..";
		return EXIT_FAILURE;
	}

	
	WaitForSingleObject(thEvenWriter,INFINITE);

	CloseHandle(thEvenWriter);
	CloseHandle(hEvenEvent);
	CloseHandle(hOddEvent);
	thEvenWriter = NULL;
	hEvenEvent = NULL;
	hOddEvent = NULL;
	return 0;
}

