// OddWriter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>
#include<fstream>
using namespace std;



HANDLE thOddWriter = NULL;
HANDLE hOddEvent = NULL;
HANDLE hEvenEvent = NULL;

DWORD tOddId;

fstream fs;


void Write(const char* ch, int i) {

	fs.open("C:\\Users\\Sahil.Tamboli\\source\\CPP\\practice\\mainFile.txt", ios::app);
	fs << ch << i << endl;
	cout << ch << i << endl;
	fs.close();

}

void OddWriter() {

	for (int i = 1; i < 20; i += 2)
	{

		DWORD dw = WaitForSingleObject(hOddEvent, INFINITE);
		/*DWORD dw1 = WaitForSingleObject(hMutex, INFINITE);*/
		Sleep(1000);
		Write("ODD WRITER Thread :", i);

		ResetEvent(hOddEvent);
		SetEvent(hEvenEvent);
		//ReleaseMutex(hMutex);


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


	thOddWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OddWriter, NULL, 0, &tOddId);
	if (GetLastError() != 0 && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		cout << endl << "Mutex Kernel Object is not created..";
		return EXIT_FAILURE;
	}



	WaitForSingleObject(thOddWriter, INFINITE);
	CloseHandle(thOddWriter);
	CloseHandle(hOddEvent);
	CloseHandle(hEvenEvent);
	
	hOddEvent = NULL;
	hEvenEvent = NULL;
	thOddWriter = NULL;
	return 0;
}

