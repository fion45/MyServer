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

bool BaseHelper::GetByWhere(void** &ObjArr, int &ArrLen, string where, void** argArr, int argArrLen)
{
	otl_stream i;
	SetColumnType(i); // use a int instead of default double
	i.open(500, // buffer size
		("select * from " + mTableName + " where " + where).data(),
		db // connect object
		);
	for (int i = 0; i < argArrLen; i++)
	{
		//i << *(argArr[i]);
	}
	//ObjArr = new void*[GetCount()];
	ObjArr = new void*[2];
	int index = 0;
	while (!i.eof())
	{
		void* obj;
		StreamToObj(i, obj);
		ObjArr[index++] = obj;
	}
	return true;
}

bool BaseHelper::AddIn(void* &objArr, int ArrLen)
{
	otl_stream o(10, // buffer size
		("insert into " + mTableName + " values(" + BuildSQLStrForAddIn() + ")").data(),
		// SQL statement
		db // connect object
		);

	o.set_commit(0); // set stream's auto-commit to OFF.

	void* objPtr = objArr;
	for (int i = 0; i < ArrLen; i++)
	{
		try
		{
			ObjToStream(objPtr, o);
			o.flush();
			NextPtr(objPtr);
		}
		catch (otl_exception& p)
		{
			if (p.code == 2601){
				// ... duplicate key ...
				cout << "STREAM ERROR STATE=" << o.get_error_state() << endl;
				o.clean(1); // clean up the stream's buffer
				// and clean up the stream's internal
				// error flag as well. By doing this, 
				// it's possible to recover from 
				// a database error without closing
				// the stream. Remember, the number of 
				// situtation when it's possible is 
				// limited and the recovery procedure should
				// be carefully designed.
			}
			else
			{
				throw; // re-throw the exception to the outer catch block.
			}
		}
	}

	db.commit(); // commit transaction
	return true;
}


bool BaseHelper::UpdateSet(void* objPtr, string where)
{
	otl_stream o; // defined an otl_stream variable
	o.open(1, // buffer size has to be set to 1 for operations with LOBs
		("update " + mTableName + " set " + BuildSQLStrForUpdateSet() + " where " + where).data(),
		// SQL statement
		db // connect object
		);
	o.set_commit(0);
	ObjToStream(objPtr, o);
	db.commit();
	return true;
}


bool BaseHelper::DeleteByWhere(string where)
{
	otl_stream o; // defined an otl_stream variable
	o.open(1, // buffer size has to be set to 1 for operations with LOBs
		("delete from " + mTableName + " where " + where).data(),
		// SQL statement
		db // connect object
		);
	o.close();
	return true;
}
