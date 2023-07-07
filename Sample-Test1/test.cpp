#include "gtest/gtest.h"
#include "gmock/gmock.h"

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