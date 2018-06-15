#pragma once

CDBConnect::CDBConnect() {}
CDBConnect::~CDBConnect() {}


CDBConnect::CDBConnect(WSTR dbPath)
{
	Open(dbPath);
}


I32    	CDBConnect::Open(WSTR dbPath)
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		STR path = wstring_to_utf8(dbPath);
		CHECK_BREAK(path.empty());
		sqlite3* pDb = NULL;
		CHECK_BREAK(SQLITE_OK != sqlite3_open(path.c_str(), &pDb));
		m_DBHandle = std::make_shared<PTR_STORAGE<sqlite3, DeleteDbPtr>>(pDb);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

BOOL      CDBConnect::IsOpen()
{
	return m_DBHandle != NULL;
}

void     CDBConnect::Close()
{
	if (m_DBHandle)
	{
		m_DBHandle.reset();
	}
}

I32		 CDBConnect::ExecSql(const WSTR sql)
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		CHECK_BREAK(sql.empty() || !IsOpen());
		STR str = wstring_to_utf8(sql);
		CHECK_BREAK(str.empty());
		int nError = sqlite3_exec(GetOriginalPtr(m_DBHandle), str.c_str(), NULL, NULL, NULL);
		CHECK_BREAK(SQLITE_OK != nError);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}



Sql_Stmt_Ptr	CDBConnect::PrepareSql(const WSTR sql)
{
	Sql_Stmt_Ptr Ret;
	CHECK_BEGIN
		CHECK_BREAK(sql.empty() || !IsOpen());
		STR str = wstring_to_utf8(sql);
		CHECK_BREAK(str.empty());
		sqlite3_stmt* pStmt = NULL;
		CHECK_BREAK(SQLITE_OK != sqlite3_prepare_v2(GetOriginalPtr(m_DBHandle), str.c_str(), (int)str.size(), &pStmt, NULL));
		CHECK_BREAK(!pStmt);
		Ret = std::make_shared<PTR_STORAGE<sqlite3_stmt, DeleteStmtPtr>>(pStmt);
	CHECK_END
	return Ret;
}


template<class ...T>
I32  	 CDBConnect::Query(const WSTR sql, CRecordList<T...>& outRecords)
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		Sql_Stmt_Ptr stmt = PrepareSql(sql);
		nRet = QueryWithCount(stmt, outRecords, -1);
	CHECK_END
	return nRet;
}

template<class ...T>
I32  	CDBConnect::QueryStmt(Sql_Stmt_Ptr& stmt, CRecordList<T...>& outRecords)
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		nRet = QueryWithCount(stmt, outRecords, -1);
	CHECK_END
	return nRet;
}

template<class ...T>
I32  	CDBConnect::QueryWithCount(HQUERY&  hQ, CRecordList<T...>& outRecords, int nCount)
{
	typedef  CRecordList<T...> TList;

	I32 iRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(hQ);
		CHECK_BREAK(!pStmt);

		int nDone = SQLITE_ROW;
		while (SQLITE_ROW == nDone && nCount--)
		{	
			nDone = sqlite3_step(pStmt);
			CHECK_BREAK(SQLITE_ROW != nDone);
			typename TList::RECORD_ELEMENT t;
			if (t.Parse(hQ))
			{
				outRecords.push_back(t);
			}
		}

		if (nCount > 0)
		{
			hQ.reset();
		}
		iRet = CODE_OK;
	CHECK_END
	return iRet;
}



I32	CDBConnect::TransactionBegin()
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		CHECK_BREAK(CODE_OK != ExecSql(L"BEGIN TRANSACTION;"));
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}
I32	CDBConnect::TransactionCommit()
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		CHECK_BREAK(CODE_OK != ExecSql(L"COMMIT;"));
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}
I32	CDBConnect::TansactionRollback()
{
	I32 nRet = CODE_ERROR;
	CHECK_BEGIN
		CHECK_BREAK(CODE_OK != ExecSql(L"ROLLBACK;"));
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}


I32	CDBConnect::ExecStmt(Sql_Stmt_Ptr& stmt)
{
	I32 iRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt);
		int nError = sqlite3_step(pStmt);
		CHECK_BREAK(SQLITE_DONE != nError);
		iRet = CODE_OK;
	CHECK_END
	return iRet;
}

BOOL	CDBConnect::IsEffectStmt(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt);
		bRet = TRUE;
	CHECK_END
	return bRet;
}


template<class ...T>
HQUERY	 CDBConnect::XQuery(const WSTR  sql, CRecordList<T...>& outRecords, int nCount)
{
	Sql_Stmt_Ptr stmtRet;
	CHECK_BEGIN
		stmtRet = PrepareSql(sql);
		nRet = QueryWithCount(stmtRet, outRecords, nCount);
	CHECK_END
	return stmtRet;
}

template<class ...T>
I32	 CDBConnect::XQuery(HQUERY&  hQ, CRecordList<T...>& outRecords, int nCount)
{
	I32 iRet = CODE_ERROR;
	CHECK_BEGIN
		iRet = QueryWithCount(hQ, outRecords, nCount);
	CHECK_END
	return iRet;
}


template<class T>
int	CDBConnect::BindStmt(Sql_Stmt_Ptr& stmt, int nSet, T val)
{
	I32 iRet = CODE_ERROR;
	CHECK_BEGIN
		iRet = ToBind(stmt, nSet, val);
	CHECK_END
	return iRet;
}

int	CDBConnect::StmtReset(Sql_Stmt_Ptr& stmt)
{
	I32 iRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt);
		CHECK_BREAK(SQLITE_OK != sqlite3_reset(pStmt));
		iRet = CODE_OK;
	CHECK_END
	return iRet;
}


LIST<WSTR>	CDBConnect::GetTablesNames()
{
	LIST<WSTR> strRet;
	CRecordList<WSTR> records;
	WSTR strSql = L"select tbl_name from sqlite_master where type = 'table';";
	Query(strSql, records);
	for (CRecordList<WSTR>::iterator it = records.begin(); it != records.end();++it)
	{
		strRet.push_back(it->m_1);
	}
	return strRet;
}