_Coroutine Money {
    // YOU ADD MEMBERS HERE
    void main();                        // coroutine main
  public:
    _Event Match {};                    // last character match
    _Event Error {};                    // last character invalid
    void next( char c ) {
        ch = c;                         // communication input
        resume();                       // activate
    }
};

Assignment example input.

$1.00
E1,00
$-1.00
E1.234,00
$-12,345.67
E123.456,78
$1,222,333,444,555.45

$1.0
E,00
$+1.00
E1,234,00
$1234.56
E123.456,7
E-1.222.333.444.555.666,45
