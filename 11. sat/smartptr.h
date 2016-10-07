#include <iostream>
#include <utility>



template <typename T>
class SmartPtr
{
public:
    template <typename T2>
    friend class SmartPtr;

    SmartPtr() : ptr(nullptr), brojac(nullptr) {}
    SmartPtr(T *p): ptr(p), brojac(new int(1)) {}

    SmartPtr(const SmartPtr& orig): ptr(orig.ptr), brojac(orig.brojac) { if(brojac!=nullptr) ++*brojac; }
    SmartPtr(SmartPtr&& orig) noexcept: ptr(orig.ptr), brojac(orig.brojac) { orig.ptr = nullptr; orig.brojac = nullptr; }

    SmartPtr& operator=(const SmartPtr& rhs);
    SmartPtr& operator=(SmartPtr&& rhs) noexcept;


    template <typename U>
    SmartPtr(const SmartPtr<U>  &s): ptr(s.ptr), brojac(s.brojac){{ if(brojac!=nullptr) ++*brojac; }}

    template <typename U>
    SmartPtr& operator=(const SmartPtr<U>& rhs)
    {
        if(brojac == nullptr || --*brojac == 0)  { delete ptr; delete brojac; }
        ptr = rhs.ptr;
        brojac = rhs.brojac;
        if(brojac!=nullptr)++*brojac;
        return *this;
    }

    ~SmartPtr(){ if(brojac!=nullptr || --*brojac == 0) { delete ptr; delete brojac; } }

    const T& operator*() const {return *ptr;}
    T& operator*() {return *ptr;}

    const T* operator->() const {return ptr;}
    T*  operator->() {return ptr;}


    // Pomoæne funkcije
    const T * get() const { return ptr; }
    const T * get() { return ptr; }
    int use_count() const { return *brojac; }
    int use_count() { return *brojac; }

private:
    T *ptr;
    int  *brojac;
};


template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& rhs)
{
    if(this != &rhs)
    {
        if(brojac == nullptr || --*brojac == 0)  { delete ptr; delete brojac; }
        ptr = rhs.ptr;
        brojac = rhs.brojac;
    }
    if(brojac!=nullptr)++*brojac;
    return *this;
}



template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr&& rhs) noexcept
{
    if(this != &rhs)
    {
        if(brojac == nullptr || --*brojac == 0)  { delete ptr; delete brojac; }
        ptr = rhs.ptr;
        brojac = rhs.brojac;
        rhs.ptr = nullptr;  rhs.ptr = nullptr;
    }
    return *this;
}


template <typename T, typename... Args>
SmartPtr<T> makeSmartPtr(Args&&... ostatak)
{
    SmartPtr<T> n(new T(std::forward<Args>(ostatak)...));
    return n;
}


template <typename T1>
class SmartPtr<T1[]>
{
public:
    template <typename T2>
    friend class SmartPtr;
    SmartPtr() : ptr(nullptr), brojac(nullptr) {}
    SmartPtr(T1 *p): ptr(p), brojac(new int(1)) {}

    SmartPtr(const SmartPtr& orig): ptr(orig.ptr), brojac(orig.brojac) { if(brojac!=nullptr) ++*brojac; }
    SmartPtr(SmartPtr&& orig) noexcept: ptr(orig.ptr), brojac(orig.brojac) { orig.ptr = nullptr; orig.brojac = nullptr; }

    SmartPtr& operator=(const SmartPtr& rhs);
    SmartPtr& operator=(SmartPtr&& rhs) noexcept;


    template <typename U>
    SmartPtr(const SmartPtr<U[]>  &s): ptr(s.ptr), brojac(s.brojac){{ if(brojac!=nullptr) ++*brojac; }}

    template <typename U>
    SmartPtr& operator=(const SmartPtr<U>& rhs)
    {
        if(brojac == nullptr || --*brojac == 0)  { delete ptr; delete brojac; }
        ptr = rhs.ptr;
        brojac = rhs.brojac;
        if(brojac!=nullptr)++*brojac;
        return *this;
    }

    ~SmartPtr(){ if(brojac!=nullptr || --*brojac == 0) { delete ptr; delete brojac; } }

    const T1& operator*() const {return *ptr;}
    T1& operator*() {return *ptr;}

    const T1* operator->() const {return ptr;}
    T1*  operator->() {return ptr;}

    T1& operator[](int i){return *(ptr+i);}
    const T1& operator[](int i) const {return *(ptr+i);}


    // Pomoæne funkcije

    const T1 * get() const { return ptr; }
    const T1 * get() { return ptr; }
    int use_count() const { return *brojac; }
    int use_count() { return *brojac; }

private:
    T1 *ptr;
    int  *brojac;
};


template <typename T>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(const SmartPtr& rhs)
{
    if(this != &rhs)
    {
        if(brojac == nullptr || --*brojac == 0)  { delete ptr; delete brojac; }
        ptr = rhs.ptr;
        brojac = rhs.brojac;
    }
    if(brojac!=nullptr)++*brojac;
    return *this;
}



template <typename T>
SmartPtr<T[]>& SmartPtr<T[]>::operator=(SmartPtr&& rhs) noexcept
{
    if(this != &rhs)
    {
        if(brojac == nullptr || --*brojac == 0)  { delete ptr; delete brojac; }
        ptr = rhs.ptr;
        brojac = rhs.brojac;
        rhs.ptr = nullptr;  rhs.ptr = nullptr;
    }
   // if(brojac!=nullptr)++*brojac;
    return *this;
}


