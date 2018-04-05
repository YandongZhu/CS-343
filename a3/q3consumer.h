#ifndef __CONSUMER_H__
#define __CONSUMER_H__

template <typename BufferType> _Task Consumer {
		BufferType & buffer;
		int delay;
		int sentinel;
		int sum;
    void main();
  public:
    Consumer( BufferType &buffer, const int Delay, const int Sentinel, int &sum );
};

#endif