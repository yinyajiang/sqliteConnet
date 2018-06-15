#pragma once
void DeleteDbPtr::operator()(sqlite3* p)
{
	if (p)
	{
		sqlite3_close(p);
	}
}
void DeleteStmtPtr::operator()(sqlite3_stmt* p)
{
	if (p)
	{
		sqlite3_finalize(p);
	}
}



template<typename T, typename D>
PTR_STORAGE<T, D>::PTR_STORAGE(T* p):m_p(p)
{

}


template<typename T, typename D>
PTR_STORAGE<T,D>::~PTR_STORAGE()
{
	Release();
}


template<typename T, typename D>
void PTR_STORAGE<T, D>::Release()
{
	if (m_p)
	{
		D d;
		d(m_p);
		m_p = NULL;
	}
}

template<typename T, typename D>
PTR_STORAGE<T, D>::operator T*()
{
	return m_p;
}



template<typename T, typename D>
PTR_STORAGE<T, D>& PTR_STORAGE<T, D>::operator =(T* that)
{
	Release();
	m_p = that;
	return *this;
}




sqlite3*		GetOriginalPtr(Db_Ptr& t)
{
	if (!t)
	{
		return NULL;
	}
	return (sqlite3*)(*t);
}
sqlite3_stmt*	GetOriginalPtr(Sql_Stmt_Ptr& t)
{
	if (!t)
	{
		return NULL;
	}
	return (sqlite3_stmt*)(*t);
}