template<typename T> class BoundedBuffer {
    T * buffer;
    int size;
    int capcity;
    int head;
  public:
    BoundedBuffer( const unsigned int size = 10 );
    void insert( T elem );
    T remove();
};
