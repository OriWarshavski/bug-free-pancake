#ifndef OUTPUT_STREAM_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6
#define OUTPUT_STREAM_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6

#include "massage.hpp"
#include "output_abstract.hpp"
#include "udp.hpp"

namespace precious_stone {

class StreamOutput : public OutputAbstract {
public:
    explicit StreamOutput(std::ostream& a_ostreamType);
    ~StreamOutput() override = default;

    void write(Massage const& a_text) override final;

protected:
    StreamOutput(const StreamOutput &a_other) = delete;
    StreamOutput& operator=(const StreamOutput &a_other) = delete;

private:
    std::ostream& m_ostreamType;
};

} //precious_stone

#endif //OUTPUT_STREAM_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6
