#pragma once

#include <map>
#include <mutex>
#include <utility>      // std::pair, std::make_pair

namespace containers {

enum class InsertResult {SUCCESS, DUPLICATE};
template <typename I, typename V>
class Dictionary {
public:
    class Iterator {
    public:
        Iterator() = default;
        Iterator(typename std::map<I, V>::const_iterator a_itr);
        Iterator(const Iterator& a_other) = default;
        Iterator& operator=(const Iterator& a_other) = default;
        bool operator!=(const Iterator& a_other);
		bool operator==(const Iterator& a_other);
        void operator++();
        std::pair<I, V> const& operator*();
        ~Iterator() = default;

    private:
        typename std::map<I, V>::const_iterator m_itr;
        std::pair<I, V> m_currentPair;
		typename std::map<I, V>::const_iterator m_saveEnd;
    };

    Dictionary() = default;
    Dictionary(const Dictionary &a_other) = delete;
    Dictionary& operator=(const Dictionary &a_other) = delete;
    ~Dictionary() = default;

    InsertResult insert(I const& a_index, V const& a_value);
    bool isExist(I const& a_index) const;
    V const& getValue(I const& a_index) const;
    void setValue(I const& a_index, V const& a_newValue);
    typename Dictionary<I, V>::Iterator remove(I const& a_index);
    size_t size() const;
    Iterator begin() const;   //dereferance will be the pair of index and value
    Iterator end() const;
    V& operator[](I const& a_index);

private:
    std::map<I, V> m_map;
    mutable std::mutex m_mtx;

};

} // namespace containers

#include "inl/dictionary.hxx"
