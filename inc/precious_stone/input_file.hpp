#ifndef INPUT_FILE_HPP_a530a97f_338a_40a2_8239_6b04f79c9894
#define INPUT_FILE_HPP_a530a97f_338a_40a2_8239_6b04f79c9894

#include "massage.hpp"
#include "input_stream.hpp"
#include <fstream>

namespace precious_stone {

class FileInput : public StreamInput{
public:
    explicit FileInput(std::string a_fileName);
    FileInput(FileInput& a_udp);
    FileInput(const FileInput &a_other) = delete;
    FileInput& operator=(const FileInput &a_other) = delete;
    ~FileInput() = default;

    bool continueReading() override;

private:
    std::ifstream m_reader;
    bool m_fileNotYetFinished;
};

} //precious_stone

#endif //INPUT_FILE_HPP_a530a97f_338a_40a2_8239_6b04f79c9894
