#pragma once
template<typename T>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, T& val)
{
	int nRet = CODE_ERROR;
	return nRet;
}

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, Unspecial& val)
{
	return CODE_OK;
}

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, BIN& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		if (SQLITE_NULL == sqlite3_column_type(pStmt, nColum))
		{
			nRet = CODE_OK;
			break;
		}
		
		const void* pBlob = sqlite3_column_blob(pStmt, nColum);
		CHECK_BREAK(!pBlob);
		int nSize = sqlite3_column_bytes(pStmt, nColum);
		CHECK_BREAK(nSize <= 0);
		val.Reset(pBlob, nSize);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, WSTR& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);

		STR strTmp;
		CHECK_BREAK(CODE_OK != ToValue(stmt, nColum, strTmp));
		if (strTmp.length())
		{
			val = utf8_to_wstring(strTmp);
		}
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, STR& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		if (SQLITE_NULL == sqlite3_column_type(pStmt, nColum))
		{
			nRet = CODE_OK;
			break;
		}
		const unsigned char* p = sqlite3_column_text(pStmt, nColum);
		CHECK_BREAK(!p);
		int nSize = sqlite3_column_bytes(pStmt, nColum);
		CHECK_BREAK(nSize <= 0);
		val = (const char*)p;
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}



template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, I32& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		val = sqlite3_column_int(pStmt, nColum);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, I64& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		val = sqlite3_column_int64(pStmt, nColum);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}


template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, DOUBLE& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		val = sqlite3_column_double(pStmt, nColum);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}



template<typename T>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, T& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		
	CHECK_END
	return nRet;
}

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, WSTR& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		STR strTmp;
		strTmp = wstring_to_utf8(val);
		nRet = ToBind(stmt,nColum,strTmp);
	CHECK_END
	return nRet;
}

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, STR& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0 );
		if (val.empty())
		{
			CHECK_BREAK(SQLITE_OK != sqlite3_bind_null(pStmt, nColum));
		}
		else
		{
			CHECK_BREAK(SQLITE_OK != sqlite3_bind_text(pStmt, nColum, val.c_str(), val.size(), SQLITE_TRANSIENT));
		}
		
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, I32& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		int nError = sqlite3_bind_int(pStmt, nColum, val);
		CHECK_BREAK(SQLITE_OK != nError);
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, I64& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		CHECK_BREAK(SQLITE_OK != sqlite3_bind_int64(pStmt, nColum, val));
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, DOUBLE& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		CHECK_BREAK(SQLITE_OK != sqlite3_bind_double(pStmt, nColum, val));
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, BIN& val)
{
	int nRet = CODE_ERROR;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt || nColum < 0);
		if (!val.Size())
		{
			CHECK_BREAK(SQLITE_OK != sqlite3_bind_null(pStmt, nColum));
		}
		else
		{
			CHECK_BREAK(SQLITE_OK != sqlite3_bind_blob(pStmt, nColum, val.Data(),val.Size(), SQLITE_TRANSIENT));
		}
		
		nRet = CODE_OK;
	CHECK_END
	return nRet;
}



#define N(n)	  n
#define M_N(n)	  m_##n

template<typename T>
BOOL CRecord_1<T>::Parse(Sql_Stmt_Ptr& stmt)
{	
	BOOL bRet = FALSE;
	CHECK_BEGIN
		sqlite3_stmt* pStmt = GetOriginalPtr(stmt);
		CHECK_BREAK(!pStmt);
		CHECK_BREAK(0 >= sqlite3_column_count(pStmt));
		bRet = (CODE_OK == ToValue(stmt, N(0), M_N(1)));
	CHECK_END
	return bRet;
}

template<typename T1, typename T2>
BOOL CRecord_2<T1, T2>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(1), M_N(2)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3>
BOOL CRecord_3<T1, T2, T3>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(2), M_N(3)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4>
BOOL CRecord_4<T1, T2, T3, T4>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(3), M_N(4)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}
template<typename T1, typename T2, typename T3, typename T4, typename T5>
BOOL CRecord_5< T1, T2, T3, T4, T5>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(4), M_N(5)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
BOOL CRecord_6< T1, T2, T3, T4, T5, T6>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(5), M_N(6)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
BOOL CRecord_7< T1, T2, T3, T4, T5, T6, T7>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(6), M_N(7)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
BOOL CRecord_8< T1, T2, T3, T4, T5, T6, T7, T8>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(7), M_N(8)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
BOOL CRecord_9< T1, T2, T3, T4, T5, T6, T7, T8, T9>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(8), M_N(9)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
BOOL CRecord_10< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(9), M_N(10)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
BOOL CRecord_11< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(10), M_N(11)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
BOOL CRecord_12< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(11), M_N(12)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
BOOL CRecord_13< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(12), M_N(13)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
BOOL CRecord_14< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(13), M_N(14)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}


template<typename T1, typename T2 = Unspecial, typename T3 = Unspecial, typename T4 = Unspecial,
	typename T5 = Unspecial, typename T6 = Unspecial, typename T7 = Unspecial, typename T8 = Unspecial,
	typename T9 = Unspecial, typename T10 = Unspecial, typename T11 = Unspecial, typename T12 = Unspecial,
	typename T13 = Unspecial, typename T14 = Unspecial, typename T15 = Unspecial>
BOOL CRecord_15< T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>::Parse(Sql_Stmt_Ptr& stmt)
{
	BOOL bRet = FALSE;
	CHECK_BEGIN
		CHECK_BREAK(TRUE != Base::Parse(stmt));
		CHECK_BREAK(CODE_OK != ToValue(stmt, N(14), M_N(15)));
		bRet = TRUE;
	CHECK_END
	return bRet;
}