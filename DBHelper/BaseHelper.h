#pragma once
#include <string>

using namespace std;

class BaseHelper
{
private:
	string mTableName;
public:
	BaseHelper();
	~BaseHelper();

	int GetCount();

	bool GetAll(void* &ObjArr, int &ArrLen);

	bool GetByWhere(void* &ObjArr, int &ArrLen, string where);

	
};