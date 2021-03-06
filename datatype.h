#pragma once
#include <string>
#include <map>
#include <list>
#include <memory>
#include <vector>
#include "../Sqlite3/sqlite3.h"


class DeleteDbPtr
{
public:
	void operator()(sqlite3* p);
};

class DeleteStmtPtr
{
public:
	void operator()(sqlite3_stmt* p);
};



template<typename T, typename D>
class PTR_STORAGE
{
public:
	typedef T type;

	PTR_STORAGE(T* p);
	~PTR_STORAGE();
	operator T*();
	PTR_STORAGE& operator =(T* that);
	void Release();
private:
	T* m_p;
};


typedef std::shared_ptr<PTR_STORAGE<sqlite3_stmt, DeleteStmtPtr>>	Sql_Stmt_Ptr;
typedef std::shared_ptr<PTR_STORAGE<sqlite3, DeleteDbPtr>>			Db_Ptr;

sqlite3*		GetOriginalPtr(Db_Ptr& t);
sqlite3_stmt*	GetOriginalPtr(Sql_Stmt_Ptr& t);

#include "datatype_impl.hpp"


