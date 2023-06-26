#pragma once 

#include <queue>
#include <mutex>
#include <condition_variable>
#include <type_traits>

namespace advcpp {

template<typename T, typename Q = std::queue<T>>
class WaitableQueue {
public:
    explicit WaitableQueue(size_t a_capacity);
    WaitableQueue(const WaitableQueue &a_other) = delete;
    WaitableQueue& operator=(const WaitableQueue &a_other) = delete;
    ~WaitableQueue() = default;

    void enqueue(T const& a_element);
    void dequeue(T& a_extracted);
    
    bool empty() const;
    bool full() const;
    size_t size() const;

private:
    template<typename U = Q>
    std::enable_if_t<std::is_same_v<U, std::queue<T>>, void> 
    firstElement(U& a_queue, T& a_extracted);

    template<typename U = Q>
    std::enable_if_t<std::is_same_v<U, std::priority_queue<T>>, void> 
    firstElement(U& a_queue, T& a_extracted);

    bool emptyInner() const noexcept;
    bool fullInner() const noexcept;

private:
    Q m_queue;
    size_t m_capacity;

    std::mutex mutable m_mtx;
    std::condition_variable m_cvNotFull;
    std::condition_variable m_cvNotEmpty;
};

} //namespace advcpp

#include "inl/waitable_queue.hxx"
