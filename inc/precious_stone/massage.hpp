#ifndef MASSAGE_HPP_0b779f57_6b0e_4ea4_9884_921ee196d5e6
#define MASSAGE_HPP_0b779f57_6b0e_4ea4_9884_921ee196d5e6

#include <string>

namespace precious_stone {

class Massage {
public:
    Massage() = default;
    explicit Massage(std::string a_text);
    Massage(const Massage &a_other);
    Massage& operator=(const Massage &a_other);
    ~Massage() = default;

    const char* text() const noexcept;
    int size() const noexcept;

    const char& operator[](const int a_index) const;
    char& operator[](const int a_index);

private:
    std::string m_text;
};

} //precious_stone

#endif //MASSAGE_HPP_0b779f57_6b0e_4ea4_9884_921ee196d5e6
