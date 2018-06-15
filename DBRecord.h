#pragma once
#include "datatype.h"
#include "toolInner.h"

struct Unspecial {};

template<typename T>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, T& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, Unspecial& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, WSTR& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, STR& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, I32& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, I64& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, DOUBLE& val);

template<>
int ToValue(Sql_Stmt_Ptr& stmt, int nColum, BIN& val);


template<typename T>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, T& val);

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, WSTR& val);

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, STR& val);

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, I32& val);

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, I64& val);

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, DOUBLE& val);

template<>
int ToBind(Sql_Stmt_Ptr& stmt, int nColum, BIN& val);






template<typename T>
class CRecord_1
{
public:
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T m_1;
};

template<typename T1, typename T2>
class CRecord_2:public  CRecord_1<T1>
{
public:
	typedef CRecord_1<T1> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T2 m_2;
};

template<typename T1, typename T2, typename T3>
class CRecord_3 :public CRecord_2<T1,T2>
{
public:
	typedef CRecord_2<T1, T2> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T3 m_3;
};

template<typename T1, typename T2, typename T3, typename T4>
class CRecord_4 :public CRecord_3<T1,T2,T3>
{
public:
	typedef CRecord_3<T1, T2, T3> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T4 m_4;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
class CRecord_5 :public CRecord_4<T1, T2, T3,T4>
{
public:
	typedef CRecord_4<T1, T2, T3, T4> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T5 m_5;
};


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class CRecord_6 :public CRecord_5<T1, T2, T3,T4,T5>
{
public:
	typedef CRecord_5<T1, T2, T3, T4, T5> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T6 m_6;
};


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class CRecord_7 :public CRecord_6<T1, T2, T3,T4,T5,T6>
{
public:
	typedef CRecord_6<T1, T2, T3, T4, T5, T6> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T7 m_7;
};


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,typename T8>
class CRecord_8 :public CRecord_7<T1, T2, T3,T4,T5,T6,T7>
{
public:
	typedef CRecord_7<T1, T2, T3, T4, T5, T6, T7> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T8 m_8;
};


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class CRecord_9 :public CRecord_8<T1, T2, T3, T4, T5, T6, T7,T8>
{
public:
	typedef CRecord_8<T1, T2, T3, T4, T5, T6, T7, T8> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T9 m_9;
};


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class CRecord_10 :public CRecord_9<T1, T2, T3, T4, T5, T6, T7, T8,T9>
{
public:
	typedef CRecord_9<T1, T2, T3, T4, T5, T6, T7, T8, T9> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T10 m_10;
};


template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class CRecord_11 :public CRecord_10<T1, T2, T3, T4, T5, T6, T7, T8, T9,T10>
{
public:
	typedef CRecord_10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T11 m_11;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class CRecord_12 :public CRecord_11<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11>
{
public:
	typedef CRecord_11<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T12 m_12;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class CRecord_13 :public CRecord_12<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,T12>
{
public:
	typedef CRecord_12<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T13 m_13;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class CRecord_14 :public CRecord_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,T13>
{
public:
	typedef CRecord_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T14 m_14;
};

template<typename T1, typename T2 = Unspecial, typename T3 = Unspecial, typename T4 = Unspecial,
	typename T5 = Unspecial, typename T6 = Unspecial, typename T7 = Unspecial, typename T8 = Unspecial,
	typename T9 = Unspecial, typename T10 = Unspecial, typename T11 = Unspecial, typename T12 = Unspecial,
	typename T13 = Unspecial, typename T14 = Unspecial, typename T15 = Unspecial>
class CRecord_15 :public CRecord_14<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,T14>
{
public:
	typedef CRecord_14<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> Base;
	BOOL Parse(Sql_Stmt_Ptr& stmt);
public:
	T15 m_15;
};





template<typename ...T>
class CRecordList : public std::list<CRecord_15<T...>>
{
public:
	typedef CRecord_15<T...> RECORD_ELEMENT;
};


#define RECORD_LIST_DEF(...) \
	class COONET(CRecord_List_ ,ARGS_NUM(__VA_ARGS__)) : public std::list< COONET(CRecord_ ,ARGS_NUM(__VA_ARGS__))<__VA_ARGS__> > \
	{ \
	public: \
		typedef COONET(CRecord_,ARGS_NUM(__VA_ARGS__))<__VA_ARGS__> RECORD_ELEMENT; \
	};



#include "DBRecord_impl.hpp"

