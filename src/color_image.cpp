#include "color_image.hpp"
#include <fstream>
#include <iostream>
#include <exception>
#include <string>
#include <cassert>
#include <cmath>

namespace advcpp {

Matrix<Color> CreatesSubMatrix(const Matrix<Color> & a_originMat, const std::pair<size_t, size_t>& a_coordinates, size_t a_w, size_t a_h);
Color MatrixAvg(Matrix<Color> const &a_mat, const std::pair<size_t, size_t>& a_coordinates, size_t a_factor);

ColorImage::ColorImage(size_t a_width, size_t a_height, unsigned int a_maxColor)
: m_image(a_width, a_height) 
, m_maxColor(a_maxColor)
, m_width(a_width)
, m_height(a_height)
{
}

ColorImage::ColorImage(const ColorImage &a_other) 
: m_image(a_other.m_image)
, m_maxColor(a_other.m_maxColor)
, m_width(a_other.m_width)
, m_height(a_other.m_height)
{
}

void ColorImage::Clear() {
    for(size_t col = 0; col < m_width; ++col) {
        Color whitePixel(m_maxColor, m_maxColor, m_maxColor);
        for(size_t row = 0; row < m_height; ++row) {
            m_image.at(col, row) = whitePixel;
        }
    } 
}

ColorImage LoadColorImage(std::string a_fileName) 
{
    std::ifstream reader(a_fileName);
    reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string imageType;
    size_t width = 0, height = 0, maxColor = 0;
    reader >> imageType >> width >> height >> maxColor;
    assert(imageType == "P3");
    ColorImage loadedImage(width, height);
    for(size_t row = 0; row < height; ++row) {
         for(size_t col = 0; col < width; ++col){
            unsigned int red, green, blue;
            reader >> red >> green >> blue;
            if(reader.good()) {
                loadedImage.WritePixel({col, row}, {red, green, blue});
            }   
            else {
                std::cerr << "fail\n";
                break;
            } 
        }
    }  
    return loadedImage;
}

void SaveColorImage(ColorImage const &a_imageToSave, std::string a_fileName) {
    std::ofstream writer(a_fileName);
    writer.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    writer << "P3" << "\n";
    writer << a_imageToSave.Width() << " " << a_imageToSave.Height() <<"\n";
    writer << a_imageToSave.MaxColor() << "\n";
    for(size_t row = 0; row < a_imageToSave.Height(); ++row) {
        for(size_t col = 0; col < a_imageToSave.Width(); ++col) {
            writer << a_imageToSave.ReadPixel({col, row}).m_red << " " << a_imageToSave.ReadPixel({col, row}).m_green << " " << a_imageToSave.ReadPixel({col, row}).m_blue << " ";
        }
        writer <<"\n";
    }
}

Color ColorImage::ReadPixel(const std::pair<size_t, size_t>& a_coordinates) const {
    try {
        return m_image.at(a_coordinates.first, a_coordinates.second);
    }catch(std::exception const& x){
        throw; //rethrow
    }
}

void ColorImage::WritePixel(const std::pair<size_t, size_t>& a_coordinates, const std::tuple<size_t, size_t, size_t>& a_rgb) {
    try {
        Color pixel(std::get<0>(a_rgb), std::get<1>(a_rgb),std::get<2>(a_rgb));
        m_image.at(a_coordinates.first, a_coordinates.second) = pixel;
    }catch(std::exception const& x){
        throw;
    }
}

size_t ColorImage::Width() const noexcept {
    return m_width;
}
size_t ColorImage::Height() const noexcept{
    return m_height;
}

unsigned int ColorImage::MaxColor() const noexcept {
    return m_maxColor;
}

void ColorImage::ReduceColorDepth(unsigned int a_newMax) {
    double factor = float(a_newMax) / m_maxColor;
    m_maxColor *= factor;
    for(size_t i = 0; i < Width(); ++i) {
        for(size_t j = 0; j < Height(); ++j) {
            m_image.at(i, j).m_red *= factor;
            m_image.at(i, j).m_green *= factor;
            m_image.at(i, j).m_blue *= factor;
        }
    }
}

void ColorImage::ScaleDownSize(size_t a_factor) {
    size_t newW = round(double(m_width) / a_factor);
    size_t newH = round(double(m_height) / a_factor);
    Matrix<Color> newMatrix(newW, newH);
    for(size_t i = 0, newI = 0; newI < newW; i += a_factor, ++newI) {
        for(size_t j = 0, newJ = 0; newJ < newH; j += a_factor, ++newJ) {
            //Matrix subMatrix = CreatesSubMatrix(m_image, {i, j}, a_factor, a_factor);
            newMatrix.at(newI, newJ) = MatrixAvg(m_image, {i, j}, a_factor);
        }
    }
    m_height = newH;
    m_width = newW;
    m_image = newMatrix;
}
/*................................................................................*/
Matrix<Color> CreatesSubMatrix(const Matrix<Color> &a_originMat, const std::pair<size_t, size_t>& a_coordinates, size_t a_w, size_t a_h) {
    Matrix<Color> subMatrix(a_w, a_h);
    for(size_t col = 0; col < a_w; ++col) {
        for(size_t row = 0; row < a_h; ++row) {
            subMatrix.at(col, row) = a_originMat.at(a_coordinates.first + col, a_coordinates.second + row);
        }
 
    }
    return subMatrix;
}

Color MatrixAvg(Matrix<Color> const &a_mat, const std::pair<size_t, size_t>& a_coordinates, size_t a_factor) {
    Color sum(0, 0, 0);
    for(size_t i = a_coordinates.first; i < a_factor; ++i) {
        for(size_t j = a_coordinates.second; j < a_factor; ++j) {
            sum.m_red += a_mat(i, j).m_red;
            sum.m_green += a_mat(i, j).m_green;
            sum.m_blue += a_mat(i, j).m_blue;
        }
    }
    sum.m_red /= (a_factor * a_factor);
    sum.m_green /= (a_factor * a_factor);
    sum.m_blue /= (a_factor * a_factor);
    return sum;
}
}