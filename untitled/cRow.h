/************************************************************
* Class: cRow
*
* Constructors:
*		cRow( cArray2D <T> & ra, int row )
*				Initialize the 2D array and the row count
*				to the passed values.
*
* Methods:
*		T & operator[] ( int column )
*				Selects and returns an element of the 2D
*				array given that is within the bounds of
*				the array.
*		T operator[] ( int column ) const
*				Selects and returns a constant element of the
*				2D array given that is within the bounds of
*				the array.
*		cRow<T> & operator= ( char * str )
*				Copies the characters of the passed string
*				into a row of the 2D array.
************************************************************/

#ifndef ROW_H
#define ROW_H

#include "cArray2D.h"

// Forward Declaration
template <typename T>
class cArray2D;

template <typename T>
class cRow
{
	public:
		cRow( cArray2D <T> & ra, int row );
		T & operator[] ( int column );
		T operator[] ( int column ) const;
		cRow<T> & operator= ( char * str );

	private:
		cArray2D <T> & m_array2D;
		int m_row;
};

template <typename T>
cRow<T>::cRow( cArray2D<T> & ra, int row ) : m_array2D( ra ), m_row( row )
{ }

template <typename T>
T & cRow<T>::operator[] ( int column )
{
	if ( column < 0 )
		throw "Error: Column index is smaller than lower bounds.";
	else if ( column > m_array2D.getColumn() )
		throw "Error: Column index is larger than upper bounds.";
	else if ( column == m_array2D.getColumn() )
		throw "Error: Column index doesn't exist.";

	return m_array2D.Select( m_row, column );
}

template <typename T>
T cRow<T>::operator[] ( int column ) const
{
	if ( column < 0 )
		throw "Error: Column index is smaller than lower bounds.";
	else if ( column > m_array2D.getColumn() )
		throw "Error: Column index is larger than upper bounds.";
	else if ( column == m_array2D.getColumn() )
		throw "Error: Column index doesn't exist.";

	return m_array2D.Select( m_row, column );
}

template <typename T>
cRow<T> & cRow<T>::operator= ( char * str )
{
	for ( unsigned int count = 0; count < strlen( str ); count++ )
		m_array2D.Select( m_row, count ) = str[ count ];

	return *this;
}

#endif