#include <cassert> //assert


#include "waitable_queue.hpp"

namespace advcpp {

template<typename T, typename Q>
WaitableQueue<T, Q>::WaitableQueue(size_t a_capacity)
: m_capacity(a_capacity)
{
    assert(a_capacity > 0);
}

template<typename T, typename Q>
void WaitableQueue<T, Q>::enqueue(T const& a_element)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    m_cvNotFull.wait(lk, [this]{return !(this->fullInner());});

    assert(!(this->fullInner()));
    m_queue.push(a_element);
    m_cvNotEmpty.notify_all();
}

template<typename T, typename Q>
template<typename U>
std::enable_if_t<std::is_same_v<U, std::queue<T>>, void> 
WaitableQueue<T, Q>::firstElement(U& a_queue, T& a_extracted)
{
    a_extracted = a_queue.front();
}

template<typename T, typename Q>
template<typename U>
std::enable_if_t<std::is_same_v<U, std::priority_queue<T>>, void> 
WaitableQueue<T, Q>::firstElement(U& a_queue, T& a_extracted)
{
    a_extracted = a_queue.top();
}

template<typename T, typename Q> 
void WaitableQueue<T, Q>::dequeue(T& a_extracted)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    m_cvNotEmpty.wait(lk, [this]{return !(this->emptyInner());});
    //the queue is not empty
    assert(!(this->emptyInner()));
    firstElement(m_queue, a_extracted);
    m_queue.pop();

    m_cvNotFull.notify_all(); 
}

template<typename T, typename Q>
bool WaitableQueue<T, Q>::empty() const
{
    std::unique_lock lk(m_mtx);
    return m_queue.empty();
}

template<typename T, typename Q>
bool WaitableQueue<T, Q>::full() const
{
    std::lock_guard lk(m_mtx);
    return m_queue.size() >= m_capacity;
}

template<typename T, typename Q>
size_t WaitableQueue<T, Q>::size() const
{
    std::lock_guard lk(m_mtx);
    return m_queue.size();
}

template<typename T, typename Q>
bool WaitableQueue<T, Q>::emptyInner() const noexcept
{
    //already locked
    return m_queue.empty();
}

template<typename T, typename Q>
bool WaitableQueue<T, Q>::fullInner() const noexcept
{
    //already locked
    return m_queue.size() >= m_capacity;
}

} //namespace advcpp
