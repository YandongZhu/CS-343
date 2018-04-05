#include <iostream>
#include "q3noBusyBoundedBuffer.h"

using namespace std;

template class NoBusyBoundedBuffer<TYPE>;

template <typename T> NoBusyBoundedBuffer<T>::NoBusyBoundedBuffer( const unsigned int size ): 
	capacity(size),
	lock(),
	consumer(),
	producer(),
	barging(){}

template <typename T> void NoBusyBoundedBuffer<T>::checkValid() {
	lock.acquire();
  if ( nextSingle ) {
    barging.wait( lock );
    nextSingle = false;
  }
}

template <typename T> void NoBusyBoundedBuffer<T>::insert( T elem ){
	checkValid();

	if ( buffer.size() == capacity ){
		if ( !barging.empty() ){
			nextSingle = true;
			consumer.signal();
		}

		consumer.wait( lock );
		nextSingle = false;
	}

	buffer.push( elem );

	if ( !consumer.empty() ) {
		nextSingle = true;
		consumer.signal();
	} else if ( !barging.empty() ) {
		nextSingle = true;
		barging.signal();
	}

	lock.release();

}


template <typename T> T NoBusyBoundedBuffer<T>::remove() {
	checkValid();

	if ( buffer.size() == 0 ) {
		if ( !barging.empty() ) {
			nextSingle = true;
			barging.signal();
		}
    consumer.wait( lock );
    nextSingle = false;
  }

  T result = buffer.front();

  buffer.pop();

  if ( !producer.empty() ) {
    nextSingle = true;
    producer.signal();
  } else if ( !barging.empty() ) {
    nextSingle = true;
    barging.signal();
  }
  lock.release();

  return result;
}

