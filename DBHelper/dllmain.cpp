// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		otl_connect::otl_initialize(); // initialize ODBC environment
		try
		{
			db.rlogon("UID=sa;PWD=1234;DSN=RGServer"); // connect to ODBC
		}
		catch (otl_exception& p){ // intercept OTL exceptions

		}
		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		db.logoff(); // disconnect from ODBC
		break;
	}
	return TRUE;
}

