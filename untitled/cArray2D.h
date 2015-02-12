/************************************************************
* Class: cArray2D
*
* Constructors:
*		cArray2D()
*				Initialize the rows and columns to 0.
*		cArray2D( int row, int col )
*				Intialize the rows and columns of the array
*				to the passed values.
*		cArray2D( const cArray2D & copy )
*				Copy the array, rows and columns of the 
*				passed value.
*
* Mutators:
*		void setRow( int row )
*				Set the number of rows in the array.
*		void setColumn( int columns )
*				Set the number of columns in the array.
*
* Methods:
*		cArray2D & operator= ( const cArray2D & rhs )
*				If not self assigned copy the array, rows and 
*				columns of the passed value.
*		cRow operator[] ( int index )
*				Returns a row of the array, assuming the
*				index passed is a valid row of the array.
*		const cRow operator[] ( int index ) const
*				Returns a const row of the array, assuming
*				the index passed is a valid row of the array.
*		int getRow() const
*				Returns the number of rows in the array.
*		int getColumn() const
*				Returns the number of columns in the array.
*		T & Select( int row, int column )
*				Returns the appropriate element in the 1D
*				array given the passed values.
************************************************************/

#ifndef ARRAY_2D_H
#define ARRAY_2D_H

#include "cArray.h"
#include "cRow.h"

template <typename T>
class cArray2D
{
	public:
		cArray2D();
		cArray2D( int row, int col = 0 );
		cArray2D( const cArray2D & copy );
		~cArray2D();
		cArray2D & operator= ( const cArray2D & rhs );
		cRow<T> operator[] ( int index );
		const cRow<T> operator[] ( int index ) const;
		int getRow() const;
		int getColumn() const;
		void setRow( int row );
		void setColumn( int columns );
		T & Select( int row, int column );

	private:
		cArray<T> m_array;
		int m_row;
		int m_col;
};

template <typename T>
cArray2D<T>::cArray2D() : m_row( 0 ), m_col( 0 )
{ }

template <typename T>
cArray2D<T>::cArray2D( int row, int column ) : m_row( row ), m_col( column )
{
	m_array.setLength( row * column );
}

template <typename T>
cArray2D<T>::cArray2D( const cArray2D & copy ) : m_array( copy.m_array ), m_row( copy.m_row ), m_col( copy.m_col )
{ }

template <typename T>
cArray2D<T>::~cArray2D()
{ }

template <typename T>
cArray2D<T> & cArray2D<T>::operator= ( const cArray2D & rhs )
{
	if ( this != &rhs )
	{
		m_array = rhs.m_array;
		m_row = rhs.m_row;
		m_col = rhs.m_col;
	}

	return *this;
}

template <typename T>
cRow<T> cArray2D<T>::operator[] ( int index )
{
	if ( index < 0 )
		throw "Error: Row index smaller than lower bounds.";
	else if ( index > m_row )
		throw "Error: Row index larger than upper bounds.";
	else if ( index == m_row )
		throw "Error: Row index doesn't exist.";

	return cRow<T>( *this, index );
}

template <typename T>
const cRow<T> cArray2D<T>::operator[] ( int index ) const
{
	const cRow<T> temp( const_cast<cArray2D &>( *this ), index );

	if ( index < 0 )
		throw "Error: Row index smaller than lower bounds.";
	else if ( index > m_row )
		throw "Error: Row index larger than upper bounds.";
	else if ( index == m_row )
		throw "Error: Row index doesn't exist.";

	return temp;
}

template <typename T>
int cArray2D<T>::getColumn() const
{
	return m_col;
}

template <typename T>
int cArray2D<T>::getRow() const
{
	return m_row;
}

template <typename T>
void cArray2D<T>::setRow( int row )
{
	if ( row > 0 )
	{
		m_row = row;
		m_array.setLength( m_row * m_col );
	}
	else
		throw "Error: Can't set to 0 or negative rows.";
}

template <typename T>
void cArray2D<T>::setColumn( int columns )
{
	if ( columns < m_col )
		for ( int row = m_row - 1; row >= 0; --row )
			m_array.remove( row * m_col + columns );
	else
		m_array.setLength( m_row * columns );

	m_col = columns;
}

template <typename T>
T & cArray2D<T>::Select( int row, int column )
{
	return m_array[ row * m_col + column ];
}

#endif