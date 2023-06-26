#ifndef INPUT_STREAM_HPP_a530a97f_338a_40a2_8239_6b04f79c9894
#define INPUT_STREAM_HPP_a530a97f_338a_40a2_8239_6b04f79c9894

#include "massage.hpp"
#include "input_abstract.hpp"

namespace precious_stone {

class StreamInput : public InputAbstract{
public:
    explicit StreamInput(std::istream& a_streamType, bool a_oneMassage = false);

    ~StreamInput() = default;

    const Massage read() override final;
    bool continueReading() override;

protected:
    StreamInput(const StreamInput &a_other) = delete;
    StreamInput& operator=(const StreamInput &a_other) = delete;

    std::string m_lastLine;

private:
    std::istream& m_istreamType;
    bool m_continueReading;
    bool m_oneMassage;
    int m_msgCounter = 0;

};

} //precious_stone

#endif //INPUT_STREAM_HPP_a530a97f_338a_40a2_8239_6b04f79c9894
