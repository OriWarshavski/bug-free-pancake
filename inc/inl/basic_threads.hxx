#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

namespace advcpp {

using Iterator = std::vector<double>::const_iterator;
template <typename UnaryFunc>
void compute(Iterator a_start, Iterator a_end, double* a_sum, UnaryFunc a_func)
{
    double sum = 0;
    while(a_start != a_end) {
        try {
            sum += a_func(*a_start);
        }
        catch(...) {
            std::cout << "computing error\n";
        }
        ++a_start;
    }
    *a_sum = sum;
}

template <typename UnaryFunc>
double computeExp(std::vector<double> const& a_numbers, UnaryFunc a_func)
{
    double sum = 0;
    compute(a_numbers.begin(), a_numbers.end(), &sum, a_func);
    return sum;
}

template <typename UnaryFunc>
double computeWith1Thread(std::vector<double>const& a_numbers, UnaryFunc a_func)
{
    double sum = 0;
    Iterator it = a_numbers.cbegin();
    Iterator end = a_numbers.cend();
    std::thread th(compute<UnaryFunc>, it, end, &sum, a_func);
    th.join();
    return sum;
}

static inline void joinAll(std::vector<std::thread>& a_tasks)
{
    for(auto& t : a_tasks) {
        t.join();
    }
}

template <typename UnaryFunc>
double parallelCompute(std::vector<double>const& a_numbers, int a_threadNum, UnaryFunc a_func)
{
    std::vector<std::thread> tasks;
    tasks.reserve(a_threadNum);

    std::vector<double> segmentSums(a_threadNum);
    size_t segmentSize = (a_numbers.size() / a_threadNum);

    Iterator iterator = a_numbers.begin();
    int i = 0;
    std::generate_n(std::back_inserter(tasks), a_threadNum
                , [&iterator, &segmentSize, &segmentSums, &i, a_func]() {
                    std::thread th{compute<UnaryFunc>, iterator, iterator + segmentSize, &(segmentSums[i]), a_func};
                    ++i;
                    iterator += segmentSize;
                    return th;
                });

    joinAll(tasks);

    return std::accumulate(segmentSums.begin(), segmentSums.end(), 0.0);
}

template <typename Mfunc>
void convertImage(sf::Image& a_image, Mfunc a_func)
{
    auto const& [width, height] = a_image.getSize();
    for(unsigned int col = 0; col < width; ++col) {
        for(unsigned int row = 0; row < height; ++row){
            sf::Color pixel = a_image.getPixel(col, row);
            a_image.setPixel(col, row, a_func(pixel));
        }
    }
}

template <typename Mfunc>
void parallelConvertImage(sf::Image& a_image, int a_threadNum, Mfunc a_func)
{
    auto const& [width, height] = a_image.getSize();
    size_t segment = height / a_threadNum;
    //define lambda
    auto f = [&a_image, a_func](unsigned int a_start, unsigned int a_end, unsigned int a_width) {
        for(unsigned int row = a_start; row < a_end; ++row) {
            for(unsigned int col = 0; col < a_width; ++col) {
                sf::Color pixel = a_image.getPixel(col, row);
                a_image.setPixel(col, row, a_func(pixel));
            }
        }
    };
    std::vector<std::thread> tasks;
    tasks.reserve(a_threadNum);
    unsigned int i = 0;
    for(; a_threadNum > 1; i += segment, --a_threadNum) {
        tasks.emplace_back(f, i, i + segment, width);
    }
    f(i, i + segment, width);
    joinAll(tasks);
}

} //namespace advcpp
