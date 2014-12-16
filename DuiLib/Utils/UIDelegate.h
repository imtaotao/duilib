#ifndef __UIDELEGATE_H__
#define __UIDELEGATE_H__

#pragma once
#include <functional>
namespace DuiLib {    
    typedef std::function<bool(void*)> Func_Delegate;
    class CEventSource;
class UILIB_API CDelegateBase	 
{
public:
    CDelegateBase(void* pObject, void* pFn);
    CDelegateBase(const CDelegateBase& rhs);
    virtual ~CDelegateBase();
    virtual bool Equals(const CDelegateBase* rhs) const;
    bool operator() (void* param);
    virtual CDelegateBase* Copy() const = 0; // add const for gcc

protected:
    void* GetFn();
    void* GetObject();
    virtual bool Invoke(void* param) = 0;

private:
    void* m_pObject;
    void* m_pFn;
};

class CDelegateStatic: public CDelegateBase
{
    typedef bool (*Fn)(void*);
public:
    CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn) { } 
    CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) { } 
    virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

protected:
    virtual bool Invoke(void* param)
    {
        Fn pFn = (Fn)GetFn();
        return (*pFn)(param); 
    }
};

template <class O, class T>
class CDelegate : public CDelegateBase
{
    typedef bool (T::* Fn)(void*);
public:
    CDelegate(O* pObj, Fn pFn) : CDelegateBase(pObj, &pFn), m_pFn(pFn) { }
    CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) { m_pFn = rhs.m_pFn; } 
    virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

protected:
    virtual bool Invoke(void* param)
    {
        O* pObject = (O*) GetObject();
        return (pObject->*m_pFn)(param); 
    }  

private:
    Fn m_pFn;
};

class CDelegateFunc : public CDelegateBase
{    
    friend class CEventSource;
public:
    CDelegateFunc(Func_Delegate func, int nId) 
        : CDelegateBase(NULL, NULL)
        , m_pFn(func)
        , m_nId(nId)
    {

    }
    CDelegateFunc(const CDelegateFunc& rhs)
        : CDelegateBase(NULL, NULL)
    {
        m_pFn = rhs.m_pFn; 
        m_nId = rhs.m_nId;
    } 
    virtual CDelegateBase* Copy() const
    {
        return new CDelegateFunc(*this);
    }
    virtual bool Equals(const CDelegateBase* rhs) const
    {
        const CDelegateFunc*pR = dynamic_cast<const CDelegateFunc*>(rhs);
        if(!pR) return false;
        return m_nId == pR->m_nId;
    }
protected:
    virtual bool Invoke(void* param)
    {
        if(!m_pFn) return true;
        return m_pFn(param); 
    }  

private:
    Func_Delegate m_pFn;
    int m_nId;
};

template <class O, class T>
CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pFn)(void*))
{
    return CDelegate<O, T>(pObject, pFn);
}

inline CDelegateStatic MakeDelegate(bool (*pFn)(void*))
{
    return CDelegateStatic(pFn); 
}

inline CDelegateFunc MakeDelegate(Func_Delegate func, int nId)
{
    return CDelegateFunc(func, nId); 
}

class UILIB_API CEventSource
{
    typedef bool (*FnType)(void*);
public:
    ~CEventSource();
    operator bool();
    void operator+= (const CDelegateBase& d); // add const for gcc
    void operator+= (FnType pFn);
    void operator+= (CDelegateFunc pFn);
    void operator-= (const CDelegateBase& d);
    void operator-= (FnType pFn);
    void operator-= (CDelegateFunc pFn);
    void RemoveById(int);
    bool operator() (void* param);
protected:
    void Add(const CDelegateBase* d);
    void Remove(const CDelegateBase* d);

protected:
    CStdPtrArray m_aDelegates;
};

} // namespace DuiLib

#endif // __UIDELEGATE_H__