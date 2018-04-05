_Coroutine Filter {
  protected:
    _Event Eof {};                    // no more characters
    Filter * next;                    // next filter in chain
    unsigned char ch;                 // communication variable
  public:
    void put( unsigned char c ) {
        ch = c;
        resume();
    }
};

_Coroutine Reader : public Filter {
    // YOU MAY ADD PRIVATE MEMBERS
    void main();
  public:
    Reader( Filter * f, istream * i );
};

_Coroutine Writer : public Filter {
    // YOU MAY ADD PRIVATE MEMBERS
    void main();
  public:
    Writer( ostream * o );
};

_Coroutine filter-name : public Filter {
    // YOU MAY ADD PRIVATE MEMBERS
    void main();
  public:
    filter-name( Filter * f, ... );
};
