// SetWorkingSet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <stdlib.h>
#include <string>
using namespace std;
typedef basic_string<TCHAR> tstring;

static tstring GetOSErrorMessage( DWORD ErrorCode )
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		ErrorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	// Process any inserts in lpMsgBuf.
	// ...
	// Return the string.
	tstring strErr = (LPCTSTR)lpMsgBuf;

	// Free the buffer.
	LocalFree( lpMsgBuf );

	return strErr;
}

int _tmain(int argc, _TCHAR* argv[] )
{
	int RetVal;

	const DWORD pid = ( argc > 1 ) ? _tcstoul( argv[1], NULL, 10) : 0; 

	if ( pid != 0 )
	{
		SIZE_T minWS;
		SIZE_T maxWS;

		if ( argc > 3 )
		{
			minWS = _tcstoul( argv[2], NULL, 10 );
			maxWS = _tcstoul( argv[3], NULL, 10 );
		}
		else
		{
			minWS = maxWS = static_cast<SIZE_T>(~0);
		}

		HANDLE hProcess = OpenProcess( PROCESS_SET_QUOTA, FALSE, pid ); 

		if ( hProcess != NULL )
		{
			if ( SetProcessWorkingSetSize( hProcess, minWS, maxWS ) )
			{
				_putts( _T("Success\n") );
				RetVal = 0;
			}
			else
			{
				RetVal = GetLastError();
				const tstring strErr{ GetOSErrorMessage( RetVal ) };
				_tprintf( _T("Failed to SetProcessWorkingSetSize - %s\n"), strErr.c_str() );
			}
			CloseHandle(hProcess); 
		}
		else
		{
			RetVal = GetLastError();
			const tstring strErr{ GetOSErrorMessage( RetVal ) };
			_tprintf( _T("Failed to OpenProcess - %s\n"), strErr.c_str() );
		}
	}
	else
	{
		_putts(	/*_T("Invalid argument.\n")*/
				_T("Usage: SetWorkingSet PID [MinSize MaxSize]\n")
				_T("\tPID = decimal value of the process ID you want to alter.\n")
				_T("\tMinSize MaxSize = values passed to the SetProcessWorkingSetSize API. If ommitted, -1 values are used.") );
		RetVal = 1;
	}

	return RetVal;
}

