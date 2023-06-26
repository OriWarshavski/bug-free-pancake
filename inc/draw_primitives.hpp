#ifndef DRAW_PRIMITIVES_HPP_fef7ac94_a0f2_47f5_b79e_21893febd016
#define DRAW_PRIMITIVES_HPP_fef7ac94_a0f2_47f5_b79e_21893febd016

#include "color_image.hpp"

namespace advcpp {

void DrawVerticalLine(ColorImage& a_image, const std::pair<size_t, size_t>& a_edges
                                    , size_t a_lineNumber
                                    , const std::tuple<size_t, size_t, size_t>& a_rgb);

void DrawHorizontalLine(ColorImage& a_image, const std::pair<size_t, size_t>& a_edges
                                    , size_t a_lineNumber
                                    , const std::tuple<size_t, size_t, size_t>& a_rgb);

void DrawLine(ColorImage& a_image, const std::pair<int, int>& a_origin
                                    , const std::pair<int, int>& a_dest
                                    , const std::tuple<size_t, size_t, size_t>& a_rgb) noexcept;


void DrawCircle(ColorImage& a_image, int a_centerX, int a_centerY, double a_radius, const std::tuple<size_t, size_t, size_t>& a_rgb);
}
#endif // DRAW_PRIMITIVES_HPP_fef7ac94_a0f2_47f5_b79e_21893febd016
