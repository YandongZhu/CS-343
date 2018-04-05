#ifndef __PRODUCER_H__
#define __PRODUCER_H__

template <typename BufferType> _Task Producer {
		BufferType &buffer;
		int produce;
		unsigned int delay;
    void main();
  public:
    Producer( BufferType &buffer, const int Produce, const int Delay );
};

#endif