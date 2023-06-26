#pragma once

#include <cstddef>

namespace mt::implementation_details {

class Capacity {
public:
    explicit Capacity(size_t a_value);
    Capacity(const Capacity &a_other) = default;
    Capacity& operator=(const Capacity &a_other) = default;
    ~Capacity() = default;

    operator size_t() const;

private:
    size_t m_value;
};

class Threads {
public:
    explicit Threads(size_t a_value);
    Threads(const Threads &a_other) = default;
    Threads& operator=(const Threads &a_other) = default;
    ~Threads() = default;

    operator size_t() const;

private:
    size_t m_value;
};

} //namespace mt::implementation_details
