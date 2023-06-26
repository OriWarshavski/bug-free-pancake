#pragma once

#include <vector>
#include <list>
#include <optional>

namespace advcpp {

void sortPointByDistanceFromAxis(std::vector<std::pair<int, int>>& a_pointsVector);

void partitionPointsInRange(std::vector<std::pair<int, int>> & a_points, std::pair<double, double> const& a_distanceRange);

std::vector<double> evensIntoVectorOfDouble(std::list<int> const& a_list);

using QuadraticRoots = std::optional<std::pair<std::optional<double>, std::optional<double>>>;
using QuadraticCoefficients = std::tuple <double, double, double>;
const std::vector<QuadraticRoots> quadraticEquationSolutions(std::vector<QuadraticCoefficients> const& a_quadraticEq);

} // namespace advcpp
