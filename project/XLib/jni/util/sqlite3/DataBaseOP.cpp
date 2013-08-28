/*
 * @(#)$Id: DataBaseOP.cpp 33848 2011-12-23 05:05:52Z chenyi $ 
 * @(#) Implementation file of class DataBaseOP
 *
 * (c)  JMsun 2009
 * 
 * All Rights Reserved.
 */ 

#ifndef CXX_DataBaseOP_H
#	include "DataBaseOP.h"
#endif 

#include <string.h>

DataBaseOP::DataBaseOP()
{
	memset(m_strDBPath, 0, MAX_PATH);
	m_pDB = NULL;
	m_pstmt = NULL;
	m_iExecVal = SQLITE_ERROR;
}

DataBaseOP::DataBaseOP(char* pFileName)
{
	strcpy(m_strDBPath, pFileName );
	m_pDB = NULL;
	m_pstmt = NULL;
	m_iExecVal = SQLITE_ERROR;
}

DataBaseOP::~DataBaseOP()
{
}

bool
DataBaseOP::Initialize(char* pFileName)
{
	if (NULL == pFileName){
		return false;
	}
	 
	strcpy(m_strDBPath, pFileName );

	return true;
}

// Connect DataBase
bool
DataBaseOP::connect()
{
	int iRetCode;
	iRetCode = sqlite3_open( m_strDBPath, &m_pDB );
	//iRetCode = sqlite3_open16(m_strDBPath, &m_pDB );
	
	if( NULL == m_pDB || SQLITE_OK != iRetCode ){
		LastError(iRetCode);
		return false;
	}

	return true;
}

// Close the DataBase
void	
DataBaseOP::close()
{
	sqlite3_close( m_pDB );
	m_pDB =	NULL;
}

// execute the sql
bool	
DataBaseOP::exec( char* strSQL )
{
	int iRetCode;
	iRetCode = sqlite3_exec( m_pDB, strSQL, 0, 0, 0 );
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;
}

bool
DataBaseOP::query(char* strSql, sqlite3_callback pCallback, void* pArg, char** pszErrMsg)
{
	int iRetCode;
	iRetCode = sqlite3_exec( m_pDB, strSql, pCallback, pArg, pszErrMsg);
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;
}	

// SQL "BEGIN"
bool	
DataBaseOP::begintrans()
{
	int iRetCode;
	iRetCode = sqlite3_exec( m_pDB, "begin;", 0, 0, 0 );
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;	
}

bool
DataBaseOP::commitTrans()
{
	int iRetCode;
	iRetCode = sqlite3_exec( m_pDB, "commit;", 0, 0, 0 );
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;	
}

bool
DataBaseOP::rollTrans()
{
	int iRetCode;
	iRetCode = sqlite3_exec( m_pDB, "rollback;", 0, 0, 0 );
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;	
}

bool	
DataBaseOP::openStmt(char* strSQL)
{
	int iRetCode;
	iRetCode = sqlite3_prepare( m_pDB, strSQL, -1, &m_pstmt, 0 );
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	m_iExecVal = sqlite3_step( m_pstmt ); 

	return true;
}

bool
DataBaseOP::Prepare(char* strSQL)
{
	int iRetCode;
	iRetCode = sqlite3_prepare( m_pDB, strSQL, -1, &m_pstmt, 0 );
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;
}

bool
DataBaseOP::BindBlob(int iIndex, BYTE* pbData, int iSize)
{
	int iRetCode;
	iRetCode = sqlite3_bind_blob(m_pstmt, iIndex, pbData, iSize, NULL);
	if( SQLITE_OK != iRetCode ){ 
		LastError(iRetCode);
		return false;
	}
	return true;
}


bool
DataBaseOP::InsertRec()
{
	int iRetCode;
	iRetCode = sqlite3_step(m_pstmt);
	m_iUpdateVal = iRetCode;
	if (SQLITE_DONE != iRetCode){ 
		return false;
	}

	return true;
}


bool	
DataBaseOP::isEOF()
{ 
	return m_iExecVal != SQLITE_ROW;
}

int
DataBaseOP::GetExecVal()
{
	return m_iExecVal;
}

int
DataBaseOP::GetUpdateVal()
{
	return m_iUpdateVal;
}

int		
DataBaseOP::getint( int iIndex )
{
	return sqlite3_column_int( m_pstmt, iIndex );
}

double	
DataBaseOP::getdouble( int iIndex )
{
	return sqlite3_column_double( m_pstmt, iIndex );
}

void	
DataBaseOP::moveNext()
{
	m_iExecVal = sqlite3_step( m_pstmt );
}

void	
DataBaseOP::closeStmt()
{
	sqlite3_finalize( m_pstmt );
}

const void*	
DataBaseOP::getBinary( int iIndex )
{
	return sqlite3_column_blob(m_pstmt, iIndex);
}

int
DataBaseOP::getDataSize(int iIndex)
{
	return sqlite3_column_bytes(m_pstmt, iIndex);
}

void 
DataBaseOP::LastError( long dwSetError ) const
{
	m_dwLastError = dwSetError;
}

long 
DataBaseOP::LastError( void ) const
{
	return m_dwLastError;
}

#ifdef _FOR_IPHONE_

int
DataBaseOP::GetCloseVal()
{
    return sqlite3_close( m_pDB );
}
#endif

/*---------------------------------------------------------------------------*/
/*
 * $Log:$
 */ 
/*---------------------------------------------------------------------------*/
/* EOF */
