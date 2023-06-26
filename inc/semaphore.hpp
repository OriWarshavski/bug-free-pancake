#pragma once
#include <mutex>
#include <condition_variable>

namespace semaphore{

class Semaphore {
public:
    Semaphore(size_t a_count = 0);

    void relese(size_t a_muchRelese = 1);
    void aquire(size_t a_muchAquire = 1);

private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    size_t m_count;
};


}//semaphore
