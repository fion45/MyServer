#pragma once
#include "Symbols.h"
#include "BaseHelper.h"
#include "ThreadSync.h"

struct DBHELPER_API SUser
{
	int UID;
	string UserName;
	string LoginID;
	string LoginPSW;
	string Email;
	BYTE Sex;
	int DefaultAddrID;
	string Permission;
	int Gift;
	string QQOpenID;
	string QQAccessToken;
	string WBID;
	string UserID;
	string LastLoginDT;
};

class DBHELPER_API UserDBHelper : public BaseHelper
{
private:
	static UserDBHelper *mInstance;
	static CritSect mCritSect;

	class CGarbo   //它的唯一工作就是在析构函数中删除CSingleton的实例  
	{
	public:
		~CGarbo()
		{
			if (UserDBHelper::mInstance)
				delete UserDBHelper::mInstance;
		}
	};
	static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数 

	UserDBHelper(string tableName = "Users");
public:
	static UserDBHelper* GetInstance();

	~UserDBHelper();

	virtual void SetColumnType(otl_stream &stream);

	virtual string BuildSQLStrForAddIn();

	virtual string BuildSQLStrForUpdateSet();

	virtual void StreamToObj(otl_stream &stream, void* &obj);

	virtual void ObjToStream(void* obj, otl_stream &stream);

	virtual void NextPtr(void* &objPtr);

	bool Login(string LoginID, string LoginPSW);
};

