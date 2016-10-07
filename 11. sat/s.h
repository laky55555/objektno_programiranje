#include <iostream>
#include <utility>
template <typename T>
class SmartPtr
{
public:
    template <typename T2>
    friend class SmartPtr;

    //konstruktori
    SmartPtr(): m_brojac(nullptr), m_ptr(nullptr){}
    SmartPtr(T* ptr) : m_brojac(new int(1)), m_ptr(ptr){}

    //kontrola kopiranja
    SmartPtr(const SmartPtr& s);
    SmartPtr(SmartPtr && s) noexcept;
    SmartPtr& operator=(const SmartPtr& s);
    SmartPtr& operator=(SmartPtr && s) noexcept;

    template <typename T1>
    SmartPtr(const SmartPtr<T1>& s)
    {
        m_ptr=s.m_ptr;
        m_brojac=s.m_brojac;
        if(m_brojac!=nullptr)++*(m_brojac);
    }

    template <typename T1>
    SmartPtr& operator=(const SmartPtr<T1>& s)
    {
        if(m_brojac!=nullptr)
        {
            if(*m_brojac==1){delete m_brojac; delete m_ptr;}
            else --*(m_brojac);
        }
        m_brojac=s.m_brojac;
        m_ptr=s.m_ptr;
                cout<< *s.m_brojac << "   ovdje\n";

        if(m_brojac!=nullptr)++*(m_brojac);

                    cout<< *m_brojac << "   ovdje\n";

        return *this;
    }

    T* get(){return m_ptr;}
    T* get() const {return m_ptr;}
    /*int* getBrojac(){return m_brojac;}
    int* getBrojac() const {return m_brojac;}*/

    T& operator*(){return *m_ptr;}
    const T& operator*() const {return *m_ptr;}

    int use_count(){return *m_brojac;}
    int use_count() const {return *m_brojac;}

    T* operator->(){return m_ptr;}
    const T* operator->() const {return m_ptr;}

    //destruktor
    ~SmartPtr();

private:
    int* m_brojac;
    T* m_ptr;
};


template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& s)
{
    m_ptr=s.m_ptr;
    m_brojac=s.m_brojac;
    if(m_brojac!=nullptr) ++*(m_brojac);
}
template <typename T>
SmartPtr<T>::SmartPtr(SmartPtr && s) noexcept
{
    m_ptr=s.m_ptr;
    m_brojac=s.m_brojac;
    if(m_brojac!=nullptr) ++*(m_brojac);
}
template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& s)
{
    if(this!=&s)
    {
        if(m_brojac!=nullptr)
        {
            if(*m_brojac==1){delete m_brojac; delete m_ptr;}
            else --*(m_brojac);
        }
        m_ptr=s.m_ptr;
        m_brojac=s.m_brojac;
        if(m_brojac!=nullptr) ++*(m_brojac);
    }
    return *this;
}
template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr && s) noexcept
{
    if(this!=&s)
    {
        if(m_brojac!=nullptr)
        {
            if(*m_brojac==1){delete m_brojac; delete m_ptr;}
            else --*(m_brojac);
        }
        m_ptr=s.m_ptr;
        m_brojac=s.m_brojac;
        if(m_brojac!=nullptr)++*(m_brojac);
    }
    return *this;
}

template<typename T>
SmartPtr<T>::~SmartPtr()
{
    if(m_brojac!=nullptr)
    {
        --*(m_brojac);
        if(*m_brojac==0){delete m_ptr; delete m_brojac;}
    }
}
template <typename T, typename... Args>
SmartPtr<T> makeSmartPtr(Args && ... ostatak)
{
    SmartPtr<T> novi(new T(std::forward<Args>(ostatak)...));
    return novi;
}

template <typename T1>
class SmartPtr<T1[]>
{
public:
    template <typename T>
    friend class SmartPtr;
    SmartPtr(): m_brojac(nullptr), m_ptr(nullptr){}
    SmartPtr(T1* ptr) : m_brojac(new int(1)), m_ptr(ptr){}

    SmartPtr(const SmartPtr& s);
    SmartPtr(SmartPtr && s) noexcept;
    SmartPtr& operator=(const SmartPtr& s);
    SmartPtr& operator=(SmartPtr && s) noexcept;

    template <typename T2>
    SmartPtr(const SmartPtr<T2[]>& s)
    {
        m_ptr=s.get();
        m_brojac=s.getBrojac();
        if(m_brojac!=nullptr)++*(m_brojac);
    }
    template <typename T2>
    SmartPtr& operator=(const SmartPtr<T2[]>& s)
    {
        if(m_brojac!=nullptr)
        {
            if(*m_brojac==1){delete m_brojac; delete [] m_ptr;}
            else --*(m_brojac);
        }
        m_ptr=s.m_ptr;
        m_brojac=s.m_brojac;
        if(m_brojac!=nullptr)++*(m_brojac);
        return *this;
    }

    T1& operator[](int i){return *(m_ptr+i);}
    const T1& operator[](int i) const {return *(m_ptr+i);}

    ~SmartPtr()
    {
        if(m_brojac!=nullptr)
        {
            --*(m_brojac);
            if(*m_brojac==0){delete [] m_ptr; delete m_brojac;}
        }
    }

    /*T1* get(){return m_ptr;}
    T1* get() const {return m_ptr;}

    int* getBrojac(){return m_brojac;}
    int* getBrojac() const {return m_brojac;}

    T1& operator*(){return *m_ptr;}
    const& T1 operator*() const {return *m_ptr;}

    int use_count(){return *m_brojac;}
    int use_count() const {return *m_brojac;}

    T1* operator->(){return m_ptr;}
    const T1* operator->() const {return m_ptr;}*/

private:
    int* m_brojac;
    T1* m_ptr;
};
template <typename T>
SmartPtr<T[]>::SmartPtr(const SmartPtr& s)
{
    m_ptr=s.m_ptr;
    m_brojac=s.m_brojac;
    if(m_brojac!=nullptr) ++*(m_brojac);
}
template <typename T>
SmartPtr<T[]>::SmartPtr(SmartPtr && s) noexcept
{
    m_ptr=s.m_ptr;
    m_brojac=s.m_brojac;
    if(m_brojac!=nullptr) ++*(m_brojac);
}
template <typename T>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(const SmartPtr& s)
{
    if(this!=&s)
    {
        if(m_brojac!=nullptr)
        {
            if(*m_brojac==1){delete m_brojac; delete m_ptr;}
            else --*(m_brojac);
        }
        m_ptr=s.m_ptr;
        m_brojac=s.m_brojac;
        if(m_brojac!=nullptr)++*(m_brojac);
    }
    return *this;
}
template <typename T>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(SmartPtr && s) noexcept
{
    if(this!=&s)
    {
        if(m_brojac!=nullptr)
        {
            if(*m_brojac==1){delete m_brojac; delete m_ptr;}
            else --*(m_brojac);
        }
        m_ptr=s.m_ptr;
        m_brojac=s.m_brojac;
        if(m_brojac!=nullptr)++*(m_brojac);
    }
    return *this;
}

