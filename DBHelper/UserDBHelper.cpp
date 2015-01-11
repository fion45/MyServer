#include "stdafx.h"
#include "UserDBHelper.h"
#include "otlv4.h"

UserDBHelper* UserDBHelper::mInstance = 0;
CritSect UserDBHelper::mCritSect;

UserDBHelper::UserDBHelper(string tableName)
: BaseHelper(tableName)
{
}


UserDBHelper::~UserDBHelper()
{

}

UserDBHelper* UserDBHelper::GetInstance()
{
	if (mInstance == NULL)
	{   //double check  
		ThreadLock ListLock(mCritSect);           //用lock实现线程安全，用资源管理类，实现异常安全  
		//使用资源管理类，在抛出异常的时候，资源管理类对象会被析构，析构总是发生的无论是因为异常抛出还是语句块结束。  
		if (mInstance == NULL)
		{
			mInstance = new UserDBHelper();
		}
	}
	return mInstance;
}

void UserDBHelper::SetColumnType(otl_stream &stream)
{

}

string UserDBHelper::BuildSQLStrForAddIn()
{
	string result = ":f1<int>,:f2<char[10000]>,:f3<char[10000]>,:f4<char[10000]>,:f5<char[10000]>,:f6<int>,"
		":f7<int>,:f8<char[10000]>,:f9<int>,:f10<char[10000]>,:f11<char[10000]>,:f12<char[10000]>,:f13<char[10000]>,:f14<char[10000]>,";
	return result;
}

string UserDBHelper::BuildSQLStrForUpdateSet()
{
	string result = "UID=:f1<int>,UserName=:f2<char[10000]>,LoginID=:f3<char[10000]>,LoginPSW=:f4<char[10000]>,Email=:f5<char[10000]>,"
		"Sex=:f6<int>,DefaultAddrID=:f7<int>,Permission=:f8<char[10000]>,Gift=:f9<int>,QQOpenID=:f10<char[10000]>,QQAccessToken=:f11<char[10000]>,"
		"WBID=:f12<char[10000]>,UserID=:f13<char[10000]>,LastLoginDT=:f14<char[10000]>";
	return result;
}

string UserDBHelper::BuildSQLStrForSelect()
{
	string result = "UID:#1<int>,UserName:#2<char[10000]>,LoginID:#3<char[10000]>,LoginPSW:#4<char[10000]>,Email:#5<char[10000]>,"
		"Sex:#6<int>,DefaultAddrID:#7<int>,Permission:#8<char[10000]>,Gift:#9<int>,QQOpenID:#10<char[10000]>,QQAccessToken:#11<char[10000]>,"
		"WBID:#12<char[10000]>,UserID:#12<char[10000]>,LastLoginDT:#14<char[10000]>";
	return result;
}

void UserDBHelper::StreamToObj(otl_stream &stream, void* &obj)
{
	SUser* user = new SUser();
	char tmpCArr[MAXCHAR];
	stream >> user->UID;
	stream >> user->UserName;
	stream >> user->LoginID;
	stream >> user->LoginPSW;
	stream >> user->Email;
	stream >> user->Sex;
	stream >> user->DefaultAddrID;
	stream >> user->Permission;
	stream >> user->Gift;
	stream >> user->QQOpenID;
	stream >> user->QQAccessToken;
	stream >> user->WBID;
	stream >> user->UserID;
	stream >> user->LastLoginDT;
	obj = user;
}

void UserDBHelper::ObjToStream(void* obj, otl_stream &stream)
{
	SUser* user = (SUser*)obj;
	stream << user->UID << *user->UserName.data() << *user->LoginID.data() 
		<< *user->LoginPSW.data() << *user->Email.data() << user->Sex 
		<< user->DefaultAddrID << *user->Permission.data() << user->Gift 
		<< *user->QQOpenID.data() << *user->QQAccessToken.data() << *user->WBID.data()
		<< *user->UserID.data() << *user->LastLoginDT.data();
}

void UserDBHelper::NextPtr(void* &objPtr)
{
	SUser* user = (SUser*)objPtr;
	user += 1;
	objPtr = user;
}

bool UserDBHelper::Login(string LoginID, string LoginPSW)
{
	void** UserArr;
	int UserArrLen = 0;
	void* argArr[2];
	argArr[0] = &LoginID;
	argArr[1] = &LoginPSW;
	//if (GetByWhere(UserArr, UserArrLen, "LoginID=:f1<char[10000]> and LoginPSW=:f2<char[10000]>", argArr, 2))
	if (GetByWhere(UserArr, UserArrLen, "LoginID='" + LoginID + "' and LoginPSW='" + LoginPSW + "'", NULL, 0))
	{

		return UserArrLen == 1;
	}
	return false;
}