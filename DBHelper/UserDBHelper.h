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

	class CGarbo   //����Ψһ��������������������ɾ��CSingleton��ʵ��  
	{
	public:
		~CGarbo()
		{
			if (UserDBHelper::mInstance)
				delete UserDBHelper::mInstance;
		}
	};
	static CGarbo Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ����������������� 

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

