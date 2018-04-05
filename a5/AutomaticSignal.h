#ifndef __AUTOMATICSIGNAL_H__
#define __AUTOMATICSIGNAL_H__
#define AUTOMATIC SIGNAL	\
	uCondition waitQueue


#define WAITUNTIL( pred, before, after ) \
	if ( !(pred) ) {	\
		before;	\
		while ( !waitQueue.empty() ) {	\
			waitQueue.signal();	\
		}	\
		while ( !(pred) ) {	\
			waitQueue.wait();	\
		}	\
		after;	\
	}

#define RETURN( expr... ) 	\// gcc variable number of parameters
	while ( !waitQueue.empty() ){	\
		waitQueue.signal();	\
	}	\
	return ( expr )

#endif