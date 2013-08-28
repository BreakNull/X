/*
 * @(#)$Id: DataBaseOP.h 33241 2011-11-28 11:11:46Z chenyi $ 
 * @(#) Declaration file of class DataBaseOP
 *
 * (c)  JMsun 2009
 * 
 * All Rights Reserved.
 */
/** @file   
 * Declaration of DataBaseOP
 * 
 * TO DESC : FILE DETAIL DESCRIPTION, BUT DON'T DESCRIBE CLASS DETAIL HERE.
 */
#ifndef CXX_DataBaseOP_H
#define CXX_DataBaseOP_H

#include "sqlite3.h"

// Class definition
class DataBaseOP;

/*-----------------------------------------------------------------------*/
/**
 *  class DataBaseOP
 *
 * TO DESC : CLASS DETAIL DESCRIPTION
 * 
 * @author $Author: chenyi $
 * @version $Revision: 33241 $
 * @date $Date: 2011-11-28 19:11:46 +0800 (周一, 2011-11-28) $
 */
/*-----------------------------------------------------------------------*/
#ifndef MAX_PATH
#   define MAX_PATH 260
#endif

#ifndef NULL
#   define NULL 0
#endif

#ifndef BYTE
#   define BYTE unsigned char
#endif

class DataBaseOP
{
public:

	// Construction
	DataBaseOP();
	DataBaseOP(char* pFileName);
	
	// Initialize
	bool Initialize(char* pFileName);

	/*-----------------------------------------------------------------------*/
	/**
	 * Destructor
	 *
	 */
	/*-----------------------------------------------------------------------*/
	virtual ~DataBaseOP();

	// Get LastError
	virtual long LastError( void )const;

	// Basic operation
	bool	connect();
	void	close();
	bool	exec( char* strSQL );
	bool	query(char* strSql, sqlite3_callback pCallback, void* pArg = NULL, char** pszErrMsg = NULL);
	bool	begintrans();
	bool	commitTrans();
	bool	rollTrans();

	// Read Operation
	bool	openStmt( char* strSQL );
	void	closeStmt();
	bool	isEOF();
	int		getint( int iIndex );
	double	getdouble( int iIndex );
	const void*	getBinary( int iIndex );
	int		getDataSize( int iIndex );
	void	moveNext();
	bool	Prepare(char* strSQL);
	bool	BindBlob(int iIndex, BYTE* pbData, int iSize);
	bool	InsertRec();

	int		GetExecVal();
	int		GetUpdateVal();
#ifdef _FOR_IPHONE_
    int     GetCloseVal();
#endif
protected:
	char	m_strDBPath[MAX_PATH];
	sqlite3*		m_pDB;			// Database handle
	sqlite3_stmt*	m_pstmt;		// Operate handle
	int				m_iExecVal;		// Execute return value
	int				m_iUpdateVal;		// Execute return value
	mutable long	m_dwLastError;	// Error Log

	// Error Log Info
	virtual void LastError( long dwSetError ) const;
};


/*---------------------------------------------------------------------------*/
/*
 * $Log:$
 */ 
/*---------------------------------------------------------------------------*/
#endif // CXX_DataBaseOP_H
/* EOF */
