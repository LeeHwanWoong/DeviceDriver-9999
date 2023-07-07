#include "DeviceDriver.h"
#include "exception"
#include <windows.h>
using namespace std;

class ReadFailException : public exception {
public:
    const char* what() const throw()
    {
        return "Read Fail\n";
    }
};

class WriteFailException : public exception {
public:
    const char* what() const throw()
    {
        return "Write Fail\n";
    }
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int read_result = (int)(m_hardware->read(address));

    for (int i = 0; i < 4; ++i)
    {
        Sleep(200);
        if(read_result != ((int)m_hardware->read(address)))
        {
            ReadFailException RFE;
            throw RFE;
        }
    }

    return read_result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if(((int)m_hardware->read(address)) != 0xFF)
    {
        WriteFailException WFE;
        throw WFE;
    }

    m_hardware->write(address, (unsigned char)data);
}