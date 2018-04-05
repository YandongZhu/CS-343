template<typename T> _Task Mergesort {
		T * list;
		unsigned int low;
		unsigned int high;
		unsigned int depth;
		bool parent = 0;
		T * copyList;
		void sequentialSort( unsigned int curLow, unsigned int curHigh );
		void mergeList( unsigned int curLow, unsigned int curHigh );
		void merge( unsigned int curLow, unsigned int curHigh );
		Mergesort( T values[], unsigned int low, unsigned int high, unsigned int depth, T copyList[] );
		void main();
public:
    Mergesort( T values[], unsigned int low, unsigned int high, unsigned int depth );
    ~Mergesort();
};



