#ifndef GENERIC_UTILS_HPP_9b2ce8b8_d02a_4742_b13c_46c6c49e2e39
#define GENERIC_UTILS_HPP_9b2ce8b8_d02a_4742_b13c_46c6c49e2e39


namespace advcpp {

template<typename T, typename U>
std::ostream& operator<<(std::ostream& a_stream, std::pair<T,U> const& a_pair);

template<class C, class T, typename Container>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& a_stream, Container const& a_container);

template<typename Iter>
typename std::iterator_traits<Iter>::value_type Minimal(Iter a_it, Iter const a_end);

template<class C, class T, typename Iter>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& a_stream, std::pair<Iter,Iter> const& a_pair);

template<typename Iter>
typename std::iterator_traits<Iter>::value_type Sum(Iter a_it, Iter const a_end);

template<typename ForwordIter>
ForwordIter FirstUnique(ForwordIter a_it, ForwordIter const a_end);

} //advcpp

#include "inl/generic_utiles.hxx"


#endif //GENERIC_UTILS_HPP_9b2ce8b8_d02a_4742_b13c_46c6c49e2e39
