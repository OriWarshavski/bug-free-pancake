#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace advcpp {

//computing:

//specific computing
//(sin(x))^2 + sin(x)/x :
const double expCmp(const double a_num);

using Iterator = std::vector<double>::const_iterator;
template <typename UnaryFunc>
void compute(Iterator a_start, Iterator a_end, double* a_sum, UnaryFunc a_func);

using Iterator = std::vector<double>::const_iterator;
template <typename UnaryFunc>
double computeExp(std::vector<double> const& a_numbers, UnaryFunc a_func);

template <typename UnaryFunc>
double computeWith1Thread(std::vector<double> const& a_numbers, UnaryFunc a_func);

template <typename UnaryFunc>
double parallelCompute(std::vector<double> const& a_numbers, int a_threadNum, UnaryFunc a_func);

//image fillters:

template <typename Mfunc>
void convertImage(sf::Image& a_image, Mfunc a_func);

//specific changes
sf::Color turnToGrey(sf::Color const& a_pixel);
sf::Color reduceBlue(sf::Color const& a_pixel);
sf::Color reduceColor(sf::Color const& a_pixel);
sf::Color reduceColors(sf::Color const& a_pixel);

template <typename Mfunc>
void parallelConvertImage(sf::Image& a_image, int a_threadNum, Mfunc a_func);

using Kernel = std::vector<float>;
sf::Image parallelImageFilter(sf::Image const& a_image, int a_threadNum
                            , Kernel a_kernel);

} //namespace advcpp

#include "inl/basic_threads.hxx"
