#include "stdafx.h"
#include "BaseHelper.h"


BaseHelper::BaseHelper(string tableName)
{
	mTableName = tableName;
}


BaseHelper::~BaseHelper()
{
}




int BaseHelper::GetCount()
{
	otl_stream i;
	i.set_column_type(0, otl_var_int, 0); // use a int instead of default double
	i.open(50, // buffer size
		("SELECT COUNT(*) from " + mTableName).data(),
		db // connect object
		);
	int result = 0;
	if (!i.eof()){ // while not end-of-data
		cout << result << endl;
	}
	return result;
}

bool BaseHelper::GetAll(void** &ObjArr, int &ArrLen)
{
	otl_stream i;
	SetColumnType(i); // use a int instead of default double
	i.open(50, // buffer size
		("SELECT * from " + mTableName).data(),
		db // connect object
		);
	ObjArr = new void*[GetCount()];
	int index = 0;
	while (!i.eof())
	{
		void* obj;
		StreamToObj(i, obj);
		ObjArr[index++] = obj;
	}
	return true;
}


bool BaseHelper::GetByWhere(void** &ObjArr, int &ArrLen, string where)
{
	otl_stream i;
	SetColumnType(i); // use a int instead of default double
	i.open(50, // buffer size
		("SELECT * from " + mTableName + " " + where).data(),
		db // connect object
		);
	ObjArr = new void*[GetCount()];
	int index = 0;
	while (!i.eof())
	{
		void* obj;
		StreamToObj(i, obj);
		ObjArr[index++] = obj;
	}
	return true;

bool BaseHelper::AddIn(void* &objArr, int ArrLen)
{
	otl_stream o(10, // buffer size
		"insert into " + mTableName + " values(" + BuildSQLStrForAddIn() + ")",
		// SQL statement
		db // connect object
		);

	o.set_commit(0); // set stream's auto-commit to OFF.

	for (int i = 0; i < ArrLen; i++)
	{
		ObjToStream(objArr + i);
		o.flush();
	}

	db.commit(); // commit transaction
	return true
}


bool BaseHelper::UpdateSet(void* objArr, string where)
{

}


bool BaseHelper::DeleteByWhere(string where)
{

}
