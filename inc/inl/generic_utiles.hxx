#include <iostream>
#include <iterator>
#include <map>
namespace advcpp {

template<typename T, typename U>
std::ostream& operator<<(std::ostream& a_stream, std::pair<T,U> const& a_pair)
{
    return a_stream << '[' << a_pair.first << ", " << a_pair.second << ']';
}
/*.....................................................................................*/
template<typename Iter>
void print(Iter it, Iter end)
{
    while(it != end) {
        std::cout << *it;
        ++it;
        if(it != end) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';   
}

template<class C, class T, typename Container>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& a_stream, Container const& a_container)
{
    typename Container::const_iterator itr = a_container.begin();
    typename Container::const_iterator end = a_container.end();
    print(itr, end);
    return a_stream;
}

/*.....................................................................................*/
template<typename Iter>
typename std::iterator_traits<Iter>::value_type Minimal (Iter a_it, Iter const a_end)
{
    typename std::iterator_traits<Iter>::value_type minItem = *a_it; 
    ++a_it;
    while(a_it != a_end) {
        if(*a_it < minItem) {
            minItem = *a_it;
        }
        ++a_it;
    }
    return minItem;
}

template<class C, class T, typename Iter>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& a_stream, std::pair<Iter,Iter> const& a_pair)
{
    Minimal(a_pair.first, a_pair.second);
    return a_stream;
}
/*.....................................................................................*/
template<typename Iter>
typename std::iterator_traits<Iter>::value_type Sum(Iter a_it, Iter const a_end)
{
    typename std::iterator_traits<Iter>::value_type sum{};
    while(a_it != a_end){            
        sum += *a_it;
        ++a_it;       
    }
    return sum;
}
/*.....................................................................................*/
template<typename ForwordIter>
std::map<typename ForwordIter::value_type, size_t> CalcFrequency(ForwordIter a_it, ForwordIter const a_end) 
{
    std::map<typename ForwordIter::value_type, size_t> freqency{};
    while(a_it != a_end) {
        if(!freqency.count(*a_it)) {
            freqency[*a_it] = 1;
        }
        else {
            ++freqency[*a_it];
        }
        ++a_it;
    }
    return freqency;
}

template<typename ForwordIter>
ForwordIter FirstUnique(ForwordIter a_it, ForwordIter const a_end)
{
    std::map<typename ForwordIter::value_type, size_t> freqency = CalcFrequency(a_it, a_end);
    while(a_it != a_end) {
        
        if(freqency[*a_it] == 1) {
            break;
        }
        ++a_it;
    }
    return a_it;
}

} //advcpp