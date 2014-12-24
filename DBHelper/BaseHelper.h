#pragma once

class BaseHelper
{
private:
	string mTableName;
public:
	BaseHelper(string tableName);
	~BaseHelper();

	int GetCount();

	virtual void SetColumnType(otl_stream &stream) = 0;

	bool GetAll(void** &ObjArr, int &ArrLen);

	bool GetByWhere(void** &ObjArr, int &ArrLen, string where);

	virtual string BuildSQLStrForAddIn() = 0;

	bool AddIn(void* &objArr, int ArrLen);

	bool UpdateSet(void* objArr, string where);

	bool DeleteByWhere(string where);

	virtual void StreamToObj(otl_stream &stream,void* &obj) = 0;

	virtual void ObjToStream(void* obj, otl_stream &stream) = 0;
};