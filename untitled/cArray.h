/************************************************************
* Class: cArray
*
* Constructors:
*		cArray()
*				Initialize the array to nullptr, the length
*				to 0, and the starting index to 0.
*		cArray( int length, int start_index )
*				Set the length and starting index to the
*				passed values and allocate room for the array.
*		cArray( const cArray & copy )
*				Copy the passed array if it's length is
*				greater than 0.
*
* Mutators:
*		void setStartIndex( int start_index )
*				Set the starting index to the passed value.
*		void setLength( int length )
*				Set the length of the array to the value.
*
* Methods:
*		cArray & operator= ( const cArray & rhs )
*				Allocate and copy the passed array if it's
*				length is greater than 0.
*		T & operator[] ( int index )
*				Returns the element at the index specified
*				if it's within the bounds of the array.
*		int getStartIndex()
*				Returns the starting index of the array.
*		int getLength()
*				Returns the length of the array.
*		void insert( T new_element )
*				Appends a new element to the array.
*		void remove( int index )
*				Removes an element from the array at the
*				index specified if it's within the bounds of
*				the array.
************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
class cArray
{
	public:
		cArray();
		cArray( int length, int start_index = 0 );
		cArray( const cArray & copy );
		~cArray();
		cArray & operator= ( const cArray & rhs );
		T & operator[] ( int index );
		void setStartIndex( int start_index );
		void setLength( int length );
		int getStartIndex();
		int getLength();
		void insert( T new_element );
		void remove( int index );

	private:
		T * m_array;
		int m_length;
		int m_start_index;
};


/*******************************************************************
* Entry:	None
* Exit:		The array initialized to null, and length and starting 
*			index to 0.
* Purpose:	Initialize the data members of the cArray.
*******************************************************************/
template <typename T>
cArray<T>::cArray() : m_array( nullptr ), m_length( 0 ), m_start_index( 0 )
{ }


/*******************************************************************
* Entry:	The length of the array and the starting index.
* Exit:		The array initialized to null, and length and starting 
*			index to the passed values.
* Purpose:	Initialize the data members of the cArray.
*******************************************************************/
template <typename T>
cArray<T>::cArray( int length, int start_index ) : m_array( nullptr ), m_start_index( start_index )
{
	m_length = length >= 0 ? length : 0;

	if ( length > 0 )
		m_array = new T [ m_length ];
}


/*******************************************************************
* Entry:	A cArray object for copying.
* Exit:		The array, length and starting index initialized to the
*			passed copy.
* Purpose:	Initialize the data members of the cArray.
*******************************************************************/
template <typename T>
cArray<T>::cArray( const cArray<T> & copy ) : m_array( nullptr ), m_length( copy.m_length ), m_start_index( copy.m_start_index )
{
	if ( this != &copy && copy.m_length > 0 )
	{
		T * temp = new T [ m_length ];

		for ( int count = 0; count < m_length; count++ )
			temp[ count ] = copy.m_array[ count ];

		delete [] m_array;
		m_array = temp;
	}
}


/*******************************************************************
* Entry:	None
* Exit:		Deallocated array.
* Purpose:	Deallocate the array.
*******************************************************************/
template <typename T>
cArray<T>::~cArray()
{
	if ( m_length > 0 )
		delete [] m_array;
}


/*******************************************************************
* Entry:	A cArray object for copying.
* Exit:		The array, length and starting index initialized to the
*			passed copy.
* Purpose:	Deep copy the data members of the passed copy.
*******************************************************************/
template <typename T>
cArray<T> & cArray<T>::operator= ( const cArray & rhs )
{
	delete [] m_array;
	m_start_index = rhs.m_start_index;

	if ( this != &rhs && rhs.m_length > 0 )
	{
		m_array = new T [ rhs.m_length ];

		for ( int count = 0; count < rhs.m_length; count++ )
			m_array[ count ] = rhs.m_array[ count ];

		m_length = rhs.m_length;
	}
	else
	{
		m_array = nullptr;
		m_length = 0;
	}

	return *this;
}


/*******************************************************************
* Entry:	The index of the element in the array.
* Exit:		The element of the array, based on the passed index.
* Purpose:	Return the desired element of the array.
*******************************************************************/
template <typename T>
T & cArray<T>::operator[] ( int index )
{
	if ( m_length == 0 )
		throw "Error: Cannot access array of 0 length.";
	else if ( index < m_start_index )
		throw "Error: Index smaller than the lower bounds.";
	else if ( index >= ( m_start_index + m_length ) )
		throw "Error: Index larger than the upper bounds.";
	else
		return m_array[ index - m_start_index ];
}


/*******************************************************************
* Entry:	None
* Exit:		The starting index of the array.
* Purpose:	Return the starting index of array to the user.
*******************************************************************/
template <typename T>
int cArray<T>::getStartIndex()
{
	return m_start_index;
}


/*******************************************************************
* Entry:	The starting index of the array.
* Exit:		None
* Purpose:	Set the starting index of the array.
*******************************************************************/
template <typename T>
void cArray<T>::setStartIndex( int start_index )
{
	m_start_index = start_index;
}


/*******************************************************************
* Entry:	None
* Exit:		Get the length of the array.
* Purpose:	Return the length of the array to the user.
*******************************************************************/
template <typename T>
int cArray<T>::getLength()
{
	return m_length;
}


/*******************************************************************
* Entry:	The length of the array.
* Exit:		None
* Purpose:	Set the length of the array.
*******************************************************************/
template <typename T>
void cArray<T>::setLength( int length )
{
	if ( length > 0 )
	{
		T * temp = new T [ length ];

		for ( int count = 0; count < ( length > m_length ? m_length : length ); count++ )
			temp[ count ] = m_array[ count ];

		delete [] m_array;
		m_array = temp;
		m_length = length;
	}
	else
		m_length = 0;
}


/*******************************************************************
* Entry:	The new element to be added to the array.
* Exit:		None
* Purpose:	Insert a new element to the array.
*******************************************************************/
template <typename T>
void cArray<T>::insert( T new_element )
{
	T * temp = new T [ m_length + 1 ];

	for ( int count = 0; count < m_length; count++ )
		temp[ count ] = m_array[ count ];

	temp[ m_length ] = new_element;
	delete [] m_array;
	m_array = temp;

	m_length++;
}


/*******************************************************************
* Entry:	The index of the element to be removed.
* Exit:		None
* Purpose:	Remove an element from the array.
*******************************************************************/
template <typename T>
void cArray<T>::remove( int index )
{
	if ( m_length == 0 )
		throw "Error: Cannot delete array of 0 length.";
	else if ( index < m_start_index )
		throw "Error: Index smaller than lower bounds.";
	else if ( index >= ( m_start_index + m_length ) )
		throw "Error: Index larger than upper bounds.";
	else
	{
		T * temp = new T [ m_length - 1 ];

		for ( int count = 0; count < m_length; count++ )
			if ( count < ( index - m_start_index ) )
				temp[ count ] = m_array[ count ];
			else
				temp[ count ] = m_array[ count + 1 ];

		delete [] m_array;
		m_array = temp;

		m_length--;
	}
}

#endif