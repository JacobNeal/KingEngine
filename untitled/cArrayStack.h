/***********************************************************
* class: cArrayStack
*
* Constructors:
*		cArrayStack( int size )
*				Intialize the stack array to the size passed
*				as well as intialize the top of the stack.
*		cArrayStack( const cArrayStack & copy )
*				Initialize the stack array to the passed
*				copy.
*
* Methods:
*		cArrayStack & operator= ( const cArrayStack & rhs )
*				Set the values of the stack array to the
*				passed value.
*		void Push( const T & obj )
*				Push an object onto the stack.
*		T Pop()
*				Removes and returns an object off of the top
*				of the stack.
*		T Peek()
*				Returns the object off of the top of the
*				stack.
*		int Size()
*				Returns the number of objects currently on
*				the stack.
*		bool isEmpty()
*				Returns true if the stack is empty.
*		bool isFull()
*				Returns true if the stack is full.
***********************************************************/

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "cArray.h"

template <typename T>
class cArrayStack
{
	public:
		cArrayStack( int size );
		cArrayStack( const cArrayStack & copy );
		~cArrayStack();
		cArrayStack & operator= ( const cArrayStack & rhs );

		void Push( const T & obj );
		T Pop();
		T Peek();
		int Size();
		bool isEmpty();
		bool isFull();

	private:
		cArray<T> m_stack;
		int m_size;
		int m_top;
};


/***********************************************************
* Entry:	The size to set the stack array to.
* Exit:		The stack array set to the length passed.
* Purpose:	Initialize the stack array to the passed size
*			and the element number size and number to 0.
***********************************************************/
template <typename T>
cArrayStack<T>::cArrayStack( int size )
	: m_size( 0 ), m_top( 0 )
{ 
	if ( size <= 0 )
		throw "ERROR: Can't have stack of no size.";
	
	m_stack.setLength( size );
}


/***********************************************************
* Entry:	A copy of a stack array.
* Exit:		The stack array set to the passed copy.
* Purpose:	Initialize the stack array to the passed copy.
***********************************************************/
template <typename T>
cArrayStack<T>::cArrayStack( const cArrayStack<T> & copy )
	: m_stack( copy.m_stack ), m_size( copy.m_size ), m_top( copy.m_top )
{ }


/***********************************************************
* Entry:	None
* Exit:		The stack array deallocated.
* Purpose:	Deallocate the stack array.
***********************************************************/
template <typename T>
cArrayStack<T>::~cArrayStack()
{ }


/***********************************************************
* Entry:	A stack array.
* Exit:		The stack array set to the passed stack array.
* Purpose:	Set the stack array to the passed stack array.
***********************************************************/
template <typename T>
cArrayStack<T> & cArrayStack<T>::operator= ( const cArrayStack<T> & rhs )
{
	m_stack = rhs.m_stack;
	m_size = rhs.m_size;
	m_top = rhs.m_top;
	
	return *this;
}


/***********************************************************
* Entry:	An object to be added to the stack.
* Exit:		The stack array with the newly pushed object.
* Purpose:	Push an object onto the stack array.
***********************************************************/
template <typename T>
void cArrayStack<T>::Push( const T & obj )
{
	if ( isFull() )
		throw "ERROR: Can't push item onto full stack.";

	m_size++;
	m_stack[ m_top++ ] = obj;
}


/***********************************************************
* Entry:	None
* Exit:		Remove and return an object off the top of the
*			stack array.
* Purpose:	Pop an object off the top of the stack.
***********************************************************/
template <typename T>
T cArrayStack<T>::Pop()
{
	if ( isEmpty() )
		throw "ERROR: Can't pop item off empty stack.";

	m_size--;
	return m_stack[ --m_top ];
}


/***********************************************************
* Entry:	None
* Exit:		The object on the top of the stack array.
* Purpose:	Return an bject off the top of the stack.
***********************************************************/
template <typename T>
T cArrayStack<T>::Peek()
{
	return m_stack[ m_top - 1 ];
}


/***********************************************************
* Entry:	None
* Exit:		Number of objects on stack.
* Purpose:	Return the number of objects on the stack.
***********************************************************/
template <typename T>
int cArrayStack<T>::Size()
{
	return m_size;
}


/***********************************************************
* Entry:	None
* Exit:		Whether the stack array is empty or not.
* Purpose:	Return true if the stack array is empty.
***********************************************************/
template <typename T>
bool cArrayStack<T>::isEmpty()
{
	return m_size == 0 ? true : false;
}


/***********************************************************
* Entry:	None
* Exit:		Whether the stack array is full or not.
* Purpose:	Return true if the stack array is full.
***********************************************************/
template <typename T>
bool cArrayStack<T>::isFull()
{
	return m_size == m_stack.getLength() ? true : false;
}

#endif