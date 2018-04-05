#ifndef __BUSYBOUNDEDBUFFER_H__
#define __BUSYBOUNDEDBUFFER_H__

#include <queue>

template<typename T> class BusyBoundedBuffer{
    std::queue<T> buffer;
    int capacity;
    uOwnerLock lock;
  	uCondLock consumer;
  	uCondLock producer;
  public:
    BusyBoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );
    T remove();
};

#endif