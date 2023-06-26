#include "strong_types.hpp"

namespace mt::implementation_details {

Capacity::Capacity(size_t a_value) 
: m_value(a_value)
{
}

Capacity::operator size_t() const
{
    return m_value;
}

Threads::Threads(size_t a_value) 
: m_value(a_value)
{
}

Threads::operator size_t() const
{
    return m_value;
}

} // namespace mt::implementation_details