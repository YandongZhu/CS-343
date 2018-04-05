#ifndef __NOBUSYBOUNDEDBUFFER_H__
#define __NOBUSYBOUNDEDBUFFER_H__

#include <queue>

template<typename T> class NoBusyBoundedBuffer{
    std::queue<T> buffer;
    int capacity;
    bool nextSingle = true;
    uOwnerLock lock;
  	uCondLock consumer;
  	uCondLock producer;
  	uCondLock barging;
  	void checkValid();
  public:
    NoBusyBoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );
    T remove();
};

#endif