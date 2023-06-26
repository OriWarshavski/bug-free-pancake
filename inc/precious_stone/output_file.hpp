#ifndef OUTPUT_FILE_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6
#define OUTPUT_FILE_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6

#include "massage.hpp"
#include "output_stream.hpp"
#include "udp.hpp"
#include <iostream>
#include <fstream>

namespace precious_stone {

class FileOutput : public StreamOutput {
public:
    FileOutput(std::string const& a_fileName);
    FileOutput(const FileOutput &a_other) = delete;
    FileOutput& operator=(const FileOutput &a_other) = delete;
    ~FileOutput() override = default;

private:
    std::ofstream m_writer;
};

} //precious_stone

#endif //OUTPUT_FILE_HPP_499826f7_0f03_4dd2_9b18_a084d81735f6
