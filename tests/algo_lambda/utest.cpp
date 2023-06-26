#include "mu_test.h"
#include "algos.hpp"
#include <vector>
#include <tuple>

template<typename C>
void print(C const& c){
    for(auto e: c){
        std::cout << e << ' ';
    }
    std::cout << '\n';
}

BEGIN_TEST(test_evens_list_ints_into_vector_of_doubles)
	using namespace advcpp;
	std::list<int> list = {1, 2, 3, -2, -9, 4, 5, 6, 7, 8};
	std::vector<double> vector = evensIntoVectorOfDouble(list);

	ASSERT_EQUAL(vector.size(), 5);
	ASSERT_EQUAL(vector[0], 8);
	ASSERT_EQUAL(vector[1], -8);
	ASSERT_EQUAL(vector[2], 64);
	ASSERT_EQUAL(vector[3], 216);
	ASSERT_EQUAL(vector[4], 512);
END_TEST

BEGIN_TEST(test_quadratic_equation)
	using namespace advcpp;
	std::vector<std::tuple <double, double, double>> quadraticEq1 {
		std::make_tuple(1, -2, 1), std::make_tuple(1, -5, 6), std::make_tuple(1, 0, 1), std::make_tuple(5, 6, 1)};
	std::vector<QuadraticRoots> check = quadraticEquationSolutions(quadraticEq1);
	std::vector<QuadraticRoots> expected{std::make_pair(1 , false), std::make_pair(3 , 2), std::nullopt, std::make_pair(-0.2, -1)};
	ASSERT_THAT(check == expected);
	ASSERT_EQUAL(check[0].has_value(), true);
	ASSERT_EQUAL(check[2].has_value(), false);
END_TEST

BEGIN_TEST(test_sort_points_by_distance_exis)
	using namespace advcpp;
	std::vector<std::pair<int, int>> check{std::make_pair(5, 5), std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(4, 7) ,std::make_pair(0, 1)};
	std::vector<std::pair<int, int>> expected{std::make_pair(0, 1), std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(5, 5), std::make_pair(4, 7)};
	sortPointByDistanceFromAxis(check);
	ASSERT_THAT(check == expected);
END_TEST

BEGIN_TEST(test_partitaion_points_by_distance_range)
	using namespace advcpp;
	std::vector<std::pair<int, int>> check{std::make_pair(5, 5), std::make_pair(3, 4), std::make_pair(3, 3), std::make_pair(4, 7) ,std::make_pair(0, 1)};
	partitionPointsInRange(check, std::make_pair(1, 5));
	std::vector<std::pair<int, int>> expected{std::make_pair(3, 4), std::make_pair(3, 3), std::make_pair(0, 1), std::make_pair(5, 5), std::make_pair(4, 7)};
	ASSERT_THAT(check == expected);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	TEST(test_evens_list_ints_into_vector_of_doubles)
	TEST(test_quadratic_equation)
	TEST(test_sort_points_by_distance_exis)
	TEST(test_partitaion_points_by_distance_range)

END_SUITE
