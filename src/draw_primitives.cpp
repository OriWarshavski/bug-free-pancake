#include "draw_primitives.hpp"

namespace advcpp {

// static void FindFirstPointAtImage(int& a_x0, int& a_y0, const std::pair<int, int>& a_dest , int a_dx, int a_dy, size_t a_height, size_t a_width);
void DrawVerticalLine(ColorImage& a_image, const std::pair<size_t, size_t>& a_edges
                                    , size_t a_lineNumber
                                    , const std::tuple<size_t, size_t, size_t>& a_rgb) { 
    if(a_edges.first >= a_edges.second) {
        throw std::invalid_argument("left edge bigger or equal to right edge");
    }
    for(size_t i = 0; i <= a_edges.second;  ++i) {
            a_image.WritePixel({a_lineNumber, i}, a_rgb);
        }
     }


void DrawHorizontalLine(ColorImage& a_image, const std::pair<size_t, size_t>& a_edges
                                    , size_t a_colNumber
                                    , const std::tuple<size_t, size_t, size_t>& a_rgb) { 
    if(a_edges.first >= a_edges.second) {
        throw std::invalid_argument("left edge bigger or equal to right edge");
    }
    for(size_t i = 0; i <= a_edges.second;  ++i) {
            a_image.WritePixel({i, a_colNumber}, a_rgb);
        }
}

void DrawLine(ColorImage& a_image, const std::pair<int, int>& a_origin
                                    , const std::pair<int, int>& a_dest
                                    , const std::tuple<size_t, size_t, size_t>& a_rgb) noexcept {
    int x0 = a_origin.first;
    int y0 = a_origin.second;
    int x1 = a_dest.first;
    int y1 = a_dest.second;                                     
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    int matrixWidth = static_cast<int>(a_image.Width());
    int matrixHeight = static_cast<int>(a_image.Height());
    //FindFirstPointAtImage(x0, y0, a_dest , dx, dy, matrixHeight, matrixWidth);
    while (true) {
        if(x0 >= matrixWidth || y0 >= matrixHeight) {
            break;
        }
        if(x0 >= 0 || y0 >= 0) {
            a_image.WritePixel({x0, y0}, a_rgb);
        }
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * error;
        if (e2 >= dy) {
            if (x0 == x1) {
                break;
            }
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx) {
            if (y0 == y1) {
                break;
            }
            error = error + dx;
            y0 = y0 + sy;
        }
    }
}

void DrawCircle(ColorImage& a_image, int a_centerX, int a_centerY, double a_radius, const std::tuple<size_t, size_t, size_t>& a_rgb) {
    int dx = int(a_radius);
    a_image.WritePixel({a_centerX + dx, a_centerY}, a_rgb);
    if (a_radius > 0.0) {
        a_image.WritePixel({a_centerX - dx, a_centerY}, a_rgb);
        a_image.WritePixel({a_centerX, a_centerY + dx}, a_rgb);
        a_image.WritePixel({a_centerX, a_centerY - dx}, a_rgb);
    }
    double P = 1 - a_radius;
    for (int dy = 1 ; dx > dy ; ++dy) { 
        if (P <= 0) {
            P = P + 2 * dy + 1;
        }
        else { 
            --dx;
            if (dx < dy) {
                break;
            }
            P = P + 2 * dy - 2 * dx + 1;
        }
        a_image.WritePixel({a_centerX + dx, a_centerY + dy}, a_rgb);
        a_image.WritePixel({a_centerX - dx, a_centerY + dy}, a_rgb);
        a_image.WritePixel({a_centerX + dx, a_centerY - dy}, a_rgb);
        a_image.WritePixel({a_centerX - dx, a_centerY - dy}, a_rgb);
        if (dx != dy) {
            a_image.WritePixel({a_centerX + dy, a_centerY + dx}, a_rgb);
            a_image.WritePixel({a_centerX - dy, a_centerY + dx}, a_rgb);
            a_image.WritePixel({a_centerX + dy, a_centerY - dx}, a_rgb);
            a_image.WritePixel({a_centerX - dy, a_centerY - dx}, a_rgb);
        }
    }
}

// static void FindFirstPointAtImage(int& a_x0, int& a_y0, const std::pair<int, int>& a_dest , int a_dx, int a_dy, size_t a_height, size_t a_width) {
//     if (a_x0 < 0) {
//         a_y0 += static_cast<int>((-a_x0) * static_cast<double>(a_dy) / a_dx);
//         a_x0 = 0;
//     } else if (a_x0 >= static_cast<int>(a_width)) {
//         a_y0 += static_cast<int>((a_width - 1 - a_x0) * static_cast<double>(a_dy) / a_dx);
//         a_x0 = a_width - 1;
//     }
//     if (a_y0 < 0) {
//         a_x0 += static_cast<int>((-a_y0) * static_cast<double>(a_dx) / a_dy);
//         a_y0= 0;
//     } else if (a_y0 >= static_cast<int>(a_height)) {
//         a_x0 += static_cast<int>((a_height - 1 - a_y0) * static_cast<double>(a_dx) / a_dy);
//         a_y0 = a_height - 1;
//     }
//      std::cout << a_x0 << ", " << a_y0 << '\n';
// }

}