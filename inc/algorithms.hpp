#ifndef ALGORITHMS_H_e54f5521_9a2e_44ff_ad14_587274c5bf3f
#define ALGORITHMS_H_e54f5521_9a2e_44ff_ad14_587274c5bf3f


#include <iterator>
#include <type_traits>

namespace advcpp {

template <typename BidIterator>
typename std::enable_if<
        std::is_base_of<
        std::bidirectional_iterator_tag,
        typename std::iterator_traits<BidIterator>::iterator_category>::value,
        void>::type
reverse(BidIterator a_p, BidIterator a_q);

template<typename ForwardIter, typename BinaryOp, typename T>  
typename std::iterator_traits<ForwardIter>::value_type
reduce(ForwardIter a_first, ForwardIter const a_last , T a_initial, BinaryOp a_binaryOp);

} //advcpp

#include "inl/algorithms.hxx"

#endif //ALGORITHMS_H_e54f5521_9a2e_44ff_ad14_587274c5bf3f