#include <iterator>
#include <cstddef>

namespace advcpp {

template <typename BidIterator>
typename std::enable_if<
        std::is_base_of<
        std::bidirectional_iterator_tag,
        typename std::iterator_traits<BidIterator>::iterator_category>::value,
        void>::type
reverse(BidIterator a_p, BidIterator a_q) 
{
    --a_q;
    while(a_p != a_q) {
        std::iter_swap(a_p, a_q);
        ++a_p;
        if(a_p == a_q) {
            break;
        }
        --a_q;
    }
}

template<typename ForwardIter, typename BinaryOp, typename T>  
typename std::iterator_traits<ForwardIter>::value_type
reduce(ForwardIter a_first, ForwardIter const a_last , T a_initial, BinaryOp a_binaryOp)
{
    while(a_first != a_last) {
        a_initial = a_binaryOp(a_initial, *a_first);
        ++a_first;
    }
    return a_initial;
}

} //advcpp


