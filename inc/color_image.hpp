#ifndef COLOR_IMAGE_H__40157b8a_84b4_480e_8866_39f974131c88
#define COLOR_IMAGE_H__40157b8a_84b4_480e_8866_39f974131c88

#include "matrix.hpp"
#include "color_rgb.hpp"
#include <string>
#include <tuple>

namespace advcpp {

class ColorImage{
public:
    explicit ColorImage(size_t a_width, size_t a_height, unsigned int a_maxColor = 255);

    ColorImage(const ColorImage &a_other);
    ColorImage& operator=(const ColorImage &a_other) = delete;
    ~ColorImage() = default;

    void Clear();

    Color ReadPixel(const std::pair<size_t, size_t>& a_coordinates) const;
    void WritePixel(const std::pair<size_t, size_t>& a_coordinates, const std::tuple<size_t, size_t, size_t>& a_rgb);
    void ReduceColorDepth(unsigned int a_newMax);
    void ScaleDownSize(size_t a_factor);
    size_t Width() const noexcept;
    size_t Height() const noexcept;
    unsigned int MaxColor() const noexcept;

private:
    Matrix<Color> m_image;
    unsigned int m_maxColor;
    size_t m_width;
    size_t m_height;
};

    ColorImage LoadColorImage(std::string a_fileName);
    void SaveColorImage(ColorImage const &a_imageToSave, std::string a_fileName);

}

#endif //COLOR_IMAGE_H__40157b8a_84b4_480e_8866_39f974131c88
