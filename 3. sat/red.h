#include <vector>

#ifndef __RED_HH_IS_INCLUDED__
#define __RED_HH_IS_INCLUDED__


typedef char QueueEntry;

class Queue{
  public:
    enum ErrorCode {success, underflow, overflow};
    Queue(int max = 8);
    // je li red prazan ili nije
    bool empty() const;
    // broj elemenata reda
    int size() const;
    // ubaci element na kraj reda
    ErrorCode push_back(QueueEntry const &);
    // eliminaraj element s pocetka reda
    ErrorCode pop_front();
    // vrati element s pocetka reda
    ErrorCode front(QueueEntry &) const;
 private:
    // maksimalni broj elemenata reda
    int maxqueue, brojElemenata, pocetak, kraj;
    std::vector<char> red;
};

#endif
