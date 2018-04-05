#include "q2mergesort.h"
#include <iostream>

using namespace std;

template class Mergesort<TYPE>; 

template<typename T> Mergesort<T>::Mergesort(
  T values [], 
	unsigned int low, 
	unsigned int high, 
	unsigned int depth ): list(values), low(low), high(high), depth(depth) {
	copyList = new T[high];
	parent = 1;
}

template<typename T> Mergesort<T>::Mergesort(
  T values [], 
	unsigned int low, 
	unsigned int high, 
	unsigned int depth,
	T copyList [] ): list(values), low(low), high(high), depth(depth), copyList(copyList) {
}

template<typename T> Mergesort<T>::~Mergesort(){
	if ( parent ) {
		delete [] copyList;
	}
}

template<typename T> void Mergesort<T>::mergeList( unsigned int curLow, unsigned int curHigh ) {
	unsigned int curMid = ( curHigh + curLow ) / 2;
	unsigned int curLeft = curLow;
	unsigned int curRight = curMid;
	unsigned int curIndex = curLow;

	memcpy( &copyList[curLow], &list[curLow], ( curHigh - curLow ) * sizeof( T ) );
	//cout << "curIndex = " << curIndex << endl;
	//cout << "curLow = " << curLow << endl;
	//cout << "curHigh = " << curHigh << endl;
	//cout << "right = " << copyList[curRight] << endl;
	//cout << "left = " << copyList[curLeft] << endl;

	while ( curLeft != curMid && curRight != curHigh ) {
		if ( copyList[curLeft] < copyList[curRight] ) {
			//cout << "curIndex = " << copyList[curLeft] << endl;
			list[curIndex] = copyList[curLeft];
			curLeft++;
		} else {
			//cout << "curIndex = " << copyList[curRight] << endl;
			list[curIndex] = copyList[curRight];
			curRight++;
		}	// if
		curIndex++;
	}	// while

	memcpy(&list[curIndex], &copyList[curLeft], ( curMid - curLeft ) * sizeof( T ));
  memcpy(&list[curIndex], &copyList[curRight], ( curHigh - curRight ) * sizeof( T ));

	// for (int i = 0; i < 2; ++i)
	// {
	// 	cout << "list " << i << " = " << list[i] << endl;
	// }
}

template<typename T> void Mergesort<T>::merge( unsigned int curLow, unsigned int curHigh ) {
	if ( curLow >= curHigh ) {
		return;
	}
	unsigned int curMid = ( curHigh + curLow ) / 2;
	merge( curLow, curMid );
	{
		Mergesort<T> right( list, curMid, curHigh, depth-1, copyList );
	}
	mergeList( curLow, curHigh );
}

template<typename T> void Mergesort<T>::sequentialSort( unsigned int curLow, unsigned int curHigh ) {
	verify();
	//cout << "start" << endl;
	if ( curLow >= curHigh - 1 ) {
		return;
	}	// if
	unsigned int curMid = ( curHigh + curLow ) / 2;
	sequentialSort( curLow,  curMid );
	sequentialSort( curMid, curHigh );
	//cout << "before " << endl;
	//cout << "cur Low = " << curLow << " curHigh = " << curHigh << endl;
	mergeList( curLow, curHigh );
	//cout << "abcd " << endl;
}	//Mergesort::sequentialSort

template<typename T> void Mergesort<T>::main() {
	verify();

	if ( low >= high ) {
		return;
	}	// if
	if ( depth < 1 ) {
		sequentialSort( low, high );
	}	// if
	else  {
		merge( low, high );
	}	
}