#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project6/DeviceDriver.cpp"
#include "../Project6/app.cpp"
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

TEST(APPLICATION, tc_ReadAndPrint)
{
	FlashMemoryDeviceMock mock;
	DeviceDriver dd(&mock);
	App app(&dd);

	EXPECT_CALL(mock, read(0))
		.Times(5)
		.WillRepeatedly(Return(0x0));
	EXPECT_CALL(mock, read(1))
		.Times(5)
		.WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock, read(2))
		.Times(5)
		.WillRepeatedly(Return(0x2));
	EXPECT_CALL(mock, read(3))
		.Times(5)
		.WillRepeatedly(Return(0x3));
	EXPECT_CALL(mock, read(4))
		.Times(5)
		.WillRepeatedly(Return(0x4));

	app.ReadAndPrint(0, 4);
}

TEST(APPLICATION, tc_WriteAll)
{
	FlashMemoryDeviceMock mock;
	DeviceDriver dd(&mock);
	App app(&dd);

	EXPECT_CALL(mock, read(0))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock, read(1))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock, read(2))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock, read(3))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock, read(4))
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(mock, write(0, 78))
		.Times(1);
	EXPECT_CALL(mock, write(1, 78))
		.Times(1);
	EXPECT_CALL(mock, write(2, 78))
		.Times(1);
	EXPECT_CALL(mock, write(3, 78))
		.Times(1);
	EXPECT_CALL(mock, write(4, 78))
		.Times(1);

	app.WriteAll(78);
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