#pragma once
#include "DBRecord.h"

#define BEGIN_TRANSCTION	L"BEGIN TRANSACTION;"
#define END_TRANSCTION		L"COMMIT;"

typedef		Sql_Stmt_Ptr						    HQUERY;


class CDBConnect//: //public IDBConnect
{
public:
	CDBConnect();
	CDBConnect(WSTR dbPath);
	 ~CDBConnect();

	 I32    Open(WSTR path);
	 BOOL   IsOpen();
	 void   Close();

	 I32	ExecSql(const WSTR sql);
	 I32	ExecStmt(Sql_Stmt_Ptr& stmt);

	 I32	TransactionBegin();
	 I32	TransactionCommit();
	 I32	TansactionRollback();

		template<class ...T>
	 I32  	Query(const WSTR sql, CRecordList<T...>& outRecords);
	 template<class ...T>
	 I32  	QueryStmt(Sql_Stmt_Ptr& stmt, CRecordList<T...>& outRecords);
		template<class ...T>
	 HQUERY	XQuery(const WSTR  sql, CRecordList<T...>& outRecords, int nCount = 100);	//分批查询
		template<class ...T>
	 I32	XQuery(HQUERY&  hQ, CRecordList<T...>& outRecords, int nCount = 100);	//分批继续查询

	 LIST<WSTR>		 GetTablesNames();
	 Sql_Stmt_Ptr	 PrepareSql(const WSTR sql);
		template<class T>
	 int			 BindStmt(Sql_Stmt_Ptr& stmt,int nSet,T val);
	 int			 StmtReset(Sql_Stmt_Ptr& stmt);

	 BOOL			 IsEffectStmt(Sql_Stmt_Ptr& stmt);


private:
	 

		template<class ...T>
	 I32  	         QueryWithCount(HQUERY&  hQ, CRecordList<T...>& outRecords, int nCount);

	 Db_Ptr			 m_DBHandle;
};

#include "DBConnect_impl.hpp"





