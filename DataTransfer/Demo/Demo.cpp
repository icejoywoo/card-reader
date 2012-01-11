// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Demo.h"
#include "DataTransfer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

bool column_name_printed = false;

void print_row(int n_values, char** values)
{
    int i;
    for (i = 0; i < n_values; ++i) {
        printf("%10s", values[i]);
    }
    printf("\n");
}

int print_result(void* data, int n_columns, char** column_values, char** column_names)
{
	if (!column_name_printed)
	{
		print_row(n_columns, column_names);
		column_name_printed = true;
	}
    print_row(n_columns, column_values);
	
	return 0;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		// using MFC, need msdn.
		DataTransfer transfer;

		TransferRule rule1;
		rule1.SetStart(9);
		rule1.SetEnd(27);
		rule1.SetTag("SFZH");
		transfer.AddRule(rule1);

		TransferRule rule2;
		rule2.SetStart(0);
		rule2.SetEnd(9);
		rule2.SetTag("SBID");
		transfer.AddRule(rule2);

		TransferRule rule3;
		rule3.SetStart(27);
		rule3.SetEnd(47);
		rule3.SetTag("BANKNO");
		transfer.AddRule(rule3);

		TransferRule rule4;
		rule4.SetStart(374);
		rule4.SetEnd(393);
		rule4.SetTag("BANKNO1");
		transfer.AddRule(rule4);

		TransferRule rule5;
		rule5.SetStart(122);
		rule5.SetEnd(128);
		rule5.SetTag("XM");
		transfer.AddRule(rule5);

		TransferRule rule6;
		rule6.SetStart(0);
		rule6.SetEnd(0);
		rule6.SetTag("ENC1");
		transfer.AddRule(rule6);

		TransferRule rule7;
		rule7.SetStart(374);
		rule7.SetEnd(393);
		rule7.SetPrefix(";");
		rule7.SetSuffix("?");
		rule7.SetTag("ENC2");
		transfer.AddRule(rule7);

		TransferRule rule;
		rule.SetStart("$$");
		rule.SetEnd("!!!!");
		rule.SetTag("PersonData");
		
		transfer.AddRule(rule);
		
		transfer.HandleFile("Test.txt");

		// sqlite3 ²âÊÔ
		sqlite3* db = NULL;
		char* errMsg = 0;
		int ret;
		ret = sqlite3_open("data.db", &db);
		if (ret != SQLITE_OK)
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		} 
		else
		{
			printf("open data.db successfully!\n");
		}
		char* sql = "create table students (number varchar(10), name varchar(10))";
		sqlite3_exec(db, sql, NULL, 0, &errMsg);
		sqlite3_exec(db, "INSERT INTO students VALUES('00001', 'Mary');", NULL, 0, &errMsg);
		sqlite3_exec(db, "SELECT * FROM students;", print_result, NULL, &errMsg);
		sqlite3_close(db);
		return 0;
	}

	return nRetCode;
}


