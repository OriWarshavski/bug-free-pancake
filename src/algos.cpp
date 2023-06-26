#include "algos.hpp"
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cassert>

namespace advcpp {

auto diastanceFromAxis = [] (std::pair<int, int> const a_point) -> double
{
   return std::sqrt(a_point.first * a_point.first + a_point.second * a_point.second);
};

void sortPointByDistanceFromAxis(std::vector<std::pair<int, int>>& a_pointsVector)
{
    using Pair = std::pair<int, int>;
    std::sort(a_pointsVector.begin(), a_pointsVector.end(), [](Pair const a_p1, Pair const a_p2) {
        return diastanceFromAxis(a_p1) < diastanceFromAxis(a_p2);
    });
}

void partitionPointsInRange(std::vector<std::pair<int, int>> &a_points, std::pair<double, double> const& a_distanceRange)
{
    assert(a_distanceRange.first < a_distanceRange.second);
    std::stable_partition(a_points.begin(), a_points.end(), [a_distanceRange](std::pair<int, int> const a_point) {
        double distancePoint = diastanceFromAxis(a_point);
        return a_distanceRange.first <= distancePoint && distancePoint <= a_distanceRange.second;
    });
}

std::vector<double> evensIntoVectorOfDouble(std::list<int> const& a_list)
{
    std::vector<double> result;
	result.reserve(a_list.size());

    std::copy_if(a_list.begin(), a_list.end(),
		std::back_inserter(result),
        [](int a_element) {
            return a_element % 2 == 0;
        });

	std::transform(result.begin(), result.end(), result.begin(),
					[](double a_num) -> double {
	 					return a_num * a_num * a_num;
	 				});

	if(result.size() > 1024*4 &&  (result.capacity() - result.size() > result.capacity() / 4)){
		result.shrink_to_fit();
	}

	return result;
}

namespace{

static const QuadraticRoots quadraticSolution(std::tuple <double, double, double> const& a_equation)
{
    double a = std::get<0>(a_equation);
    double b = std::get<1>(a_equation);
    double c = std::get<2>(a_equation);
    double descriminanta = pow(b, 2) - 4 * a * c;
    if(descriminanta == 0.0) {
        double solution = ((-b) / (2 * a));
        return std::make_pair(solution, false);
    }

    if(descriminanta > 0) {
        double sqrtDescriminanta = sqrt(descriminanta);
        double solution1 = (-b + sqrtDescriminanta) / (2 * a);
        double solution2 = (-b - sqrtDescriminanta) / (2 * a);
        return std::make_pair(solution1, solution2);
    }
    return QuadraticRoots{};
}

} //namespace

const std::vector<QuadraticRoots> quadraticEquationSolutions(std::vector<QuadraticCoefficients> const& a_quadraticEq)
{
    std::vector<QuadraticRoots> rootsVector;
    rootsVector.reserve(a_quadraticEq.size());

    std::transform(a_quadraticEq.begin(), a_quadraticEq.end(), std::back_inserter(rootsVector), 
    [](std::tuple <double, double, double> a_element) {
        return quadraticSolution(a_element);
    });
    return rootsVector;
}

} // namespace advcpp
