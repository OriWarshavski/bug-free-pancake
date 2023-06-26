#include <iostream>
#include <thread>
#include <algorithm>
#include <random>

#include "mu_test.h"
#include "basic_threads.hpp"

using namespace advcpp;

constexpr size_t Size = 10000000;
constexpr size_t Range = 100;
constexpr double Epsilon = 1e-04;

static std::vector<double> initRandVector()
{
	std::vector<double> numbers;
    numbers.reserve(Size);
    std::generate_n(std::back_inserter(numbers), Size
                    , []() { return ((std::rand() % Range) + 1); });
    return numbers;
}

std::vector<double> gVector = initRandVector();
double checkedResult = computeExp(gVector, expCmp);

BEGIN_TEST(test_five_numbers)
	std::vector<double> v = {0.45, 3.1, 2.2, 1.9, 10.12};
    double result = computeExp(v, expCmp);
    double roundedResult = std::floor(result * std::pow(10, 4)) / std::pow(10, 4);
    ASSERT_EQUAL(roundedResult, 3.9326);
END_TEST

BEGIN_TEST(test_10million)
    double result = computeExp(gVector, expCmp);
    double roundedResult = std::floor((result / 1000000) * std::pow(10, 4)) / std::pow(10, 4);
    ASSERT_EQUAL(roundedResult, 5.1328);
END_TEST

BEGIN_TEST(test_10million_with_1thread)
    double test = computeWith1Thread(gVector, expCmp);
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    ASSERT_THAT(delta < Epsilon);
END_TEST

BEGIN_TEST(test_10million_with_threads_one)
    double test = parallelCompute(gVector, 1, expCmp);
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    TRACE(Epsilon);
    ASSERT_THAT(delta < Epsilon);
END_TEST

BEGIN_TEST(test_10million_with_2threads)
    double test = parallelCompute(gVector, 2, expCmp);
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    ASSERT_THAT(delta < Epsilon);
END_TEST

BEGIN_TEST(test_10million_with_4threads)
    double test = parallelCompute(gVector, 4, expCmp);
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    ASSERT_THAT(delta < Epsilon);
END_TEST

BEGIN_TEST(test_10million_with_8threads)
    double test = parallelCompute(gVector, 8, expCmp);
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    ASSERT_THAT(delta < Epsilon);
END_TEST

BEGIN_TEST(test_10million_with_16threads)
    double test = parallelCompute(gVector, 16, expCmp);
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    ASSERT_THAT(delta < Epsilon);
END_TEST

BEGIN_TEST(test_10million_with_lambda)
    double test = parallelCompute(gVector, 16, [](double const a_num) {
        if(a_num == 0) {
            throw "cant compute zero number\n";
        }
        double s = std::sin(a_num);
        double computeI = (s * s) + (s / a_num);
        return computeI;
    });
    double delta = std::abs(test - checkedResult);
    TRACE(delta);
    ASSERT_THAT(delta < Epsilon);
END_TEST

void openWindow(sf::Image const& a_image)
{
    sf::Texture texture;
    texture.loadFromImage(a_image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    auto const& [width, height] = a_image.getSize();
    sf::RenderWindow w{sf::VideoMode(width, height), "fixed image"};

    sf::Event event;
    while (w.isOpen()) {
        while(w.pollEvent(event)) {
            if(((event.type == sf::Event::KeyPressed)
            && (event.key.code == sf::Keyboard::Escape))) {
                w.close();
                break;
            }
            if(event.type == sf::Event::Closed) {
                w.close();
                break;
            }
        }
        w.clear();
        w.draw(sprite);
        w.display();
    }
}

BEGIN_TEST(image_turnGrey)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    convertImage(image, turnToGrey);
    openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_reduceBlue)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    convertImage(image, reduceBlue);
    openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_reduceColor)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    convertImage(image, reduceColor);
    openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_turnGrey_1thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 1, turnToGrey);
    //openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_turnGrey_2thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 2, turnToGrey);
    //openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_turnGrey_4thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 4, turnToGrey);
    //openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_turnGrey_8thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 8, turnToGrey);
    //openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_turnGrey_16thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 16, turnToGrey);
    openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_reduceBlue_16thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 16, reduceBlue);
    openWindow(image);
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(image_reduceColors_16thread)
    sf::Image image{};
    if (!image.loadFromFile("image/tiger.jpeg")) {
        std::cout << "open file error\n";
    }
    parallelConvertImage(image, 2, reduceColors);
    openWindow(image);
    ASSERT_THAT(true);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_five_numbers)
    TEST(test_10million)
    TEST(test_10million_with_1thread)
    TEST(test_10million_with_threads_one)
    TEST(test_10million_with_2threads)
    TEST(test_10million_with_4threads)
    TEST(test_10million_with_8threads)
    TEST(test_10million_with_16threads)
    TEST(test_10million_with_lambda)

    TEST(image_turnGrey)
    TEST(image_reduceBlue)
    TEST(image_reduceColor)
    TEST(image_turnGrey_1thread)
    TEST(image_turnGrey_2thread)
    TEST(image_turnGrey_4thread)
    TEST(image_turnGrey_8thread)
    TEST(image_turnGrey_16thread)
    TEST(image_reduceBlue_16thread)

    TEST(image_reduceColors_16thread)

END_SUITE
