
#include "thread_pack.hpp"

namespace mt::implementation_details {

ThreadPack::ThreadPack(TaskType a_task) 
: m_askForTerminate(false)
, m_readyToExit(false)
, m_thread(a_task, std::ref(m_askForTerminate), std::ref(m_readyToExit))
{
}

ThreadPack::~ThreadPack()
{
    m_thread.join();
}

} //namespace mt::implementation_details
