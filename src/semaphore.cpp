#include <mutex>
#include <condition_variable>
#include "semaphore.hpp"


namespace semaphore{


Semaphore::Semaphore(size_t a_count)
: m_count(a_count)
{}

void Semaphore::relese(size_t a_muchRelese)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_count += a_muchRelese;
    m_cv.notify_one();
}

void Semaphore::aquire(size_t a_muchAquire)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while (m_count < a_muchAquire) {
        m_cv.wait(lock);
    }
    m_count -= a_muchAquire;
}

}//semaphore
