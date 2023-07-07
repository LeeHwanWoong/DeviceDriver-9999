
#if 0
#include <string>
#define interface struct;
using namespace std;

class Cal
{
public:
	int getSum(int a, int b)
	{
		return a + b;
	}
	int getValue(int a, int b)
	{
		return value;
	}
private:
	int value;
};

struct DBAPI {
	virtual string getDBName() = 0;
};

class DataBaseAPI : public DBAPI
{
public:
	string getDBName()
	{
		return "myDB";
	}
};

class LogSystem
{
public:
	LogSystem()
	{}

	explicit LogSystem(DBAPI* db)
	:DB(db)
	{}

	string getLogMessage()
	{
		return string("[") + DB->getDBName() + string("]");
	}
private:
	DBAPI* DB;
};
#endif