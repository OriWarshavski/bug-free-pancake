#include "input_file.hpp"
#include <fstream>
#include <iostream>
#include <exception>

namespace precious_stone {

static std::ifstream create_reader(std::string a_fileName) 
{
    std::ifstream reader(a_fileName);
    reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    return reader;
}

FileInput::FileInput(std::string a_fileName) 
: StreamInput(m_reader)
, m_reader(create_reader(a_fileName))
, m_fileNotYetFinished(true)
{
}

bool FileInput::continueReading()
{
    if(m_reader.eof()) {
        m_fileNotYetFinished = false;
    }
    return m_fileNotYetFinished;
}

} //precious_stone
