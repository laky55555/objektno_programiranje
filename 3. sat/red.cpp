#include <iostream>
#include "red.h"




Queue::Queue(int max )
{
    maxqueue = max;
    brojElemenata = 0;
    pocetak = 0;
    kraj = max-1;
    red.resize(max);
}

bool Queue::empty() const
{
    if(brojElemenata == 0)
        return true;
    else
        return false;
}

int Queue::size() const
{
    return brojElemenata;
}

Queue::ErrorCode Queue::push_back(QueueEntry const & znak)
{
    if(brojElemenata == maxqueue)
        return overflow;
    kraj = (++kraj)%maxqueue;
    brojElemenata++;
    red[kraj] = znak;
    return success;
}

Queue::ErrorCode Queue::pop_front()
{
    if(brojElemenata == 0)
        return underflow;
    pocetak = (++pocetak)%maxqueue;
    brojElemenata--;
    return success;
}

Queue::ErrorCode Queue::front(QueueEntry & znak) const
{
    if(brojElemenata == 0)
        return underflow;
    znak = red[pocetak];
    return success;
}
