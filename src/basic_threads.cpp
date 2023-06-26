
#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <thread>
#include <algorithm>
#include <numeric>

#include "basic_threads.hpp"

namespace advcpp {

//(sin(x))^2 + sin(x)/x
const double expCmp(const double a_num)
{
    if(a_num == 0) {
        throw "cant compute zero number\n";
    }
    double s = std::sin(a_num);
    double computeI = (s * s) + (s / a_num);
    return computeI;
}

sf::Color turnToGrey(sf::Color const& a_pixel)
{
    sf::Uint8 avg = (a_pixel.r + a_pixel.g + a_pixel.b) / 3;
    return sf::Color{avg, avg, avg};
}

sf::Color reduceBlue(sf::Color const& a_pixel)
{
    return sf::Color{a_pixel.r, a_pixel.g, static_cast<sf::Uint8>(a_pixel.b / 2)};
}

sf::Color reduceColor(sf::Color const& a_pixel)
{
    return sf::Color{static_cast<sf::Uint8>(a_pixel.r / 2)
                    , static_cast<sf::Uint8>(a_pixel.g / 2)
                    , static_cast<sf::Uint8>(a_pixel.b / 2)};
}

sf::Color reduceColors(sf::Color const& a_pixel)
{
    return sf::Color{static_cast<sf::Uint8>((a_pixel.r / 128) * 128)
                    , static_cast<sf::Uint8>((a_pixel.g / 128) * 128)
                    , static_cast<sf::Uint8>((a_pixel.b / 128) * 128)};
}


//how much steps from the matrix left-up point
static int offsetLeftCorner(int a_matrixDimention)
{
    //steps of 2 - to get bigger matrix
    int const numOfSteps = (a_matrixDimention - 1) / 2;
    return numOfSteps;
}

static sf::Color useFillter(sf::Image const& a_original, int a_col, int a_row
                            , std::vector<float> a_kernel)
{
    int matrixDimention = std::sqrt(a_kernel.size());
    int newPosRow = a_row - offsetLeftCorner(matrixDimention);
    int newPosCol = a_col - offsetLeftCorner(matrixDimention);
    float sumRed = 0.;
    float sumGreen = 0.;
    float sumBlue = 0.;
    auto itr = a_kernel.begin();
    for(int row = newPosRow; row < matrixDimention + newPosRow; ++row) {
        for(int col = newPosCol; col < matrixDimention + newPosCol; ++col) {
            auto [r, g, b, x] = a_original.getPixel(col, row);
            float mask = *itr;
            sumRed += r * mask;
            sumGreen += g * mask;
            sumBlue += b * mask;
            ++itr;
        }
    }
    const unsigned int r = sumRed < 0 ? 0 : sumRed > 255 ? 255 : sumRed;
    const unsigned int g = sumGreen < 0 ? 0 : sumGreen > 255 ? 255 : sumGreen;
    const unsigned int b = sumBlue < 0 ? 0 : sumBlue > 255 ? 255 : sumBlue;
    return sf::Color(r, g, b);
}

sf::Image parallelImageFilter(sf::Image const& a_image, int a_threadNum
                            , Kernel a_kernel)
{
    auto const& [width, height] = a_image.getSize();
    sf::Image converted;
    converted.create(width, height);

    //define lambda
    auto f = [&a_image, &converted, a_kernel](unsigned int a_startRow, unsigned int a_endRow
                                            ,unsigned int a_startCol , unsigned int a_endCol) {
        for(unsigned int row = a_startRow; row < a_endRow; ++row) {
            for(unsigned int col = a_startCol; col < a_endCol; ++col) {
                sf::Color color = useFillter(a_image, col, row, a_kernel);
                converted.setPixel(col, row, color);
            }
        }
    };

    std::vector<std::thread> tasks;
    tasks.reserve(a_threadNum);

    //delete offset
    int matrixDimention = std::sqrt(a_kernel.size());
    int offset = offsetLeftCorner(matrixDimention);
    size_t segment = height / a_threadNum;

    unsigned int i = offset;
    for(; a_threadNum > 1; i += segment, --a_threadNum) {
        tasks.emplace_back(f, i, i + segment, offset, width - offset);
    }
    //last segment
    f(i, i + segment, offset, width - offset);

    joinAll(tasks);

    return converted;
}

} //namespace advcpp
