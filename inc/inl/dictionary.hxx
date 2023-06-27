#include <stdexcept>
#include <exception>

#include "dictionary.hpp"

namespace containers {

template <typename I, typename V>
InsertResult Dictionary<I, V>::insert(I const& a_index, V const& a_value)
{
    std::unique_lock<std::mutex> lk(m_mtx);
    std::pair result =  m_map.emplace(std::make_pair(a_index, a_value));
    if(result.second) {
        return InsertResult::SUCCESS;
    }
    return InsertResult::DUPLICATE;
}

template <typename I, typename V>
bool Dictionary<I, V>::isExist(I const& a_index) const
{
    std::unique_lock<std::mutex> lk(m_mtx);
    if(m_map.find(a_index) != m_map.end()) {
        return true;
    }
    return false;
}

template <typename I, typename V>
V const& Dictionary<I, V>::getValue(I const& a_index) const
{
    if(!isExist(a_index)) {
        throw(std::out_of_range("key not found"));
    }
    std::unique_lock<std::mutex> lk(m_mtx);
    return m_map.at(a_index);
}

template <typename I, typename V>
void Dictionary<I, V>::setValue(I const& a_index, V const& a_newValue)
{
    if(!isExist(a_index)) {
        throw(std::out_of_range("key not found"));
    }
    std::unique_lock<std::mutex> lk(m_mtx);
    m_map[a_index] = a_newValue;
}

template <typename I, typename V>
typename Dictionary<I, V>::Iterator Dictionary<I, V>::remove(I const& a_index)
{
    if(!isExist(a_index)) {
        throw(std::out_of_range("key not found"));
    }
    std::unique_lock<std::mutex> lk(m_mtx);
	typename std::map<I, V>::const_iterator itr = m_map.find(a_index);

    auto nextItr = itr;
	++nextItr;

	if(nextItr == typename std::map<I, V>::const_iterator(m_map.end())) {
		m_map.erase(itr);
		return Iterator(itr);
	}
    m_map.erase(itr);

    return Iterator(nextItr);
}

template <typename I, typename V>
size_t Dictionary<I, V>::size() const
{
    std::unique_lock<std::mutex> lk(m_mtx);
    return m_map.size();
}

template <typename I, typename V>
typename Dictionary<I, V>::Iterator Dictionary<I, V>::begin() const
{
    return m_map.begin();
}

template <typename I, typename V>
typename Dictionary<I, V>::Iterator Dictionary<I, V>::end() const
{
    return m_map.end();
}

template <typename I, typename V>
V& Dictionary<I, V>::operator[](I const& a_index) {
    return m_map[a_index];
}

template <typename I, typename V>
Dictionary<I, V>::Iterator::Iterator(typename std::map<I, V>::const_iterator a_itr)
: m_itr(a_itr)
, m_currentPair(*m_itr)
{
}

template <typename I, typename V>
bool Dictionary<I, V>::Iterator::operator!=(const Iterator& a_other) {
    return m_itr != a_other.m_itr;
}

template <typename I, typename V>
bool Dictionary<I, V>::Iterator::operator==(const Iterator& a_other) {
    return m_itr == a_other.m_itr;
}

template <typename I, typename V>
void Dictionary<I, V>::Iterator::operator++() {
    ++m_itr;
}

template <typename I, typename V>
std::pair<I, V> const& Dictionary<I, V>::Iterator::operator*() {
    m_currentPair = *m_itr;
    return m_currentPair;
}

} //namespace containers
