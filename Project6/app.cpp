#include "DeviceDriver.h"
#include <iostream>
using namespace std;

class App
{
public:
	App(DeviceDriver* temp)
	:dd(temp)
	{}

	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long readAddr = startAddr; readAddr <= endAddr; ++readAddr)
		{
			cout << dd->read(readAddr) << endl;
		}
	}

	void WriteAll(int value)
	{
		for (long i = 0; i <= 4; ++i)
		{
			dd->write(i, value);
		}
	}
private:
	DeviceDriver *dd;
};