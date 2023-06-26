#include "output_file.hpp"
#include <fstream>

namespace precious_stone {

static std::ofstream createWriter(std::string a_fileName) 
{
    std::ofstream writer(a_fileName);
    writer.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    return writer;
}

FileOutput::FileOutput(std::string const& a_fileName) 
: StreamOutput(m_writer)
, m_writer(createWriter(a_fileName))
{
}

} //precious_stone
