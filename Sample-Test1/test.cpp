#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project6/DeviceDriver.cpp"
using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data),(override));
};

TEST(DEVICEDRIVER, tc_Read1)
{
	FlashMemoryDeviceMock mock;
	DeviceDriver dd(&mock);

	EXPECT_CALL(mock, read(1))
		.Times(5)
		.WillRepeatedly(Return(5));

	EXPECT_THAT(5, dd.read(1));
}

TEST(DEVICEDRIVER, tc_Read2)
{
	FlashMemoryDeviceMock mock;
	DeviceDriver dd(&mock);

	EXPECT_CALL(mock, read(1))
		.WillOnce(Return(3))
		.WillRepeatedly(Return(5));

	EXPECT_THROW(dd.read(1), ReadFailException);
}

TEST(DEVICEDRIVER, tc_Write1)
{
	FlashMemoryDeviceMock mock;
	DeviceDriver dd(&mock);

	EXPECT_CALL(mock, read(1))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock, write(1, '1'))
		.Times(1);

	dd.write(1, '1');
}

TEST(DEVICEDRIVER, tc_Write2)
{
	FlashMemoryDeviceMock mock;
	DeviceDriver dd(&mock);

	EXPECT_CALL(mock, read(1))
		.Times(1)
		.WillRepeatedly(Return(0x0));
	EXPECT_CALL(mock, write(1, '1'))
		.Times(0);

	EXPECT_THROW(dd.write(1, '1'), WriteFailException);
}

#if 0
#include "../Project6/source.cpp"
using namespace std;
using namespace testing;

class CalMock : public Cal
{
public:
	MOCK_METHOD(int, getSum, (int a, int b), ());
	MOCK_METHOD(int, getValue, (), ());
};

TEST(TestCaseName, TestName) {
	CalMock mock;

	//stub
	EXPECT_CALL(mock, getValue())
	.Times(2).
	WillRepeatedly(Return(10000));

	mock.getValue();

	//behavior verification
	EXPECT_THAT(10000, mock.getValue());
}

class DBMock : public DBAPI
{
public:
	MOCK_METHOD(string, getDBName, (), (override));
};

TEST(DBTEST,TC1)
{
	DBMock mock;

	EXPECT_CALL(mock, getDBName()).WillRepeatedly(Return(string("aa")));

	LogSystem app(&mock);
	cout << app.getLogMessage();
}
#endif