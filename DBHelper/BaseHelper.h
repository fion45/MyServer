#pragma once
#include "stdafx.h"

class BaseHelper
{
private:
	string mTableName;
public:
	BaseHelper(string tableName);
	~BaseHelper();

	int GetCount();

	virtual void SetColumnType(otl_stream &stream) = 0;

	virtual string BuildSQLStrForSelect() = 0;

	bool GetAll(void** &ObjArr, int &ArrLen);

	bool GetByWhere(void** &ObjArr, int &ArrLen, string where, void** argArr, int argArrLen);

	virtual string BuildSQLStrForAddIn() = 0;

	bool AddIn(void* &objArr, int ArrLen);

	virtual string BuildSQLStrForUpdateSet() = 0;

	bool UpdateSet(void* objPtr, string where);

	bool DeleteByWhere(string where);

	virtual void StreamToObj(otl_stream &stream,void* &obj) = 0;

	virtual void ObjToStream(void* obj, otl_stream &stream) = 0;

	virtual void NextPtr(void* &objPtr) = 0;
};