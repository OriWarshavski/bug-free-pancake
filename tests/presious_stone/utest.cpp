#include "mu_test.h"
#include "link_box.hpp"
#include "hard_coded_input.hpp"
#include "simple_convert.hpp"
#include "simple_output.hpp"
#include "input_udp.hpp"
#include "output_udp.hpp"
//#include "input_stream.hpp"
//#include "output_stream.hpp"
#include "caesar_convert.hpp"
#include "input_file.hpp"
#include "output_file.hpp"
#include "capitalize_convert.hpp"
#include "vowel_censor_convert.hpp"
#include "output_terminal.hpp"
#include "input_terminal.hpp"

#include <sstream>  
#include <fstream>

using namespace precious_stone;

static std::string returnFileContent(std::string a_fileName)
{
    std::ifstream reader(a_fileName);
    reader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string line;
	std::string result;
    while(!reader.eof()) {
		try {
        	std::getline(reader, line);
			result += line;
		} catch(...) {
		}
	}
	return result;
}


BEGIN_TEST(simple)
	HardCodedInput input{};
	SimpleConvert convert{};
	SimpleOutput output{};
	LinkBox	simpleLinking(input, convert, output);
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "Hello World"));
END_TEST


BEGIN_TEST(udp_output)
	HardCodedInput input{};
	SimpleConvert convert{};
	UdpOutput output{"127.0.0.1", 7777};
	LinkBox	udpLinking(input, convert, output);

	udpLinking.linking();

	ASSERT_PASS();
END_TEST

BEGIN_TEST(udp_input)
	UdpInput input{7777};
	SimpleConvert convert{};
	SimpleOutput output{};
	LinkBox	udpLinking(input, convert, output);

	udpLinking.linking();
	std::string result{output.m_result.text()};
	ASSERT_EQUAL(result, "ori");
END_TEST

BEGIN_TEST(udp)
	UdpInput out_test{7777};
	UdpOutput in_test{"127.0.1.1", 4242};

	UdpInput input{4242};
	SimpleConvert convert{};
	UdpOutput output{"127.0.0.1", 7777};
	LinkBox	udpLinking(input, convert, output);
	Massage msg{"hey i am ori warshavski !"};
	in_test.write(msg);

	udpLinking.linking();

	std::string check{out_test.read().text()};
	ASSERT_EQUAL(check, "hey i am ori warshavski !");
END_TEST

BEGIN_TEST(input_stream_output_simple)
	std::string stringvalues = "ori";
	std::istringstream iss (stringvalues);
	StreamInput input{iss, true};
	SimpleConvert convert{};
	SimpleOutput output{};
	LinkBox	simpleLinking(input, convert, output);
	simpleLinking.linking();
	std::string result{output.m_result.text()};
	ASSERT_EQUAL(result, "ori");
END_TEST

BEGIN_TEST(input_stream_output_stream_to_string)
	std::string stringvalues = "ori";
	std::istringstream iss (stringvalues);
	StreamInput input{iss, true};
	SimpleConvert convert{};
	std::ostringstream foo;
	StreamOutput output{foo};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_EQUAL(foo.str(), "ori\n");
END_TEST

BEGIN_TEST(simple_caesar)
	HardCodedInput input{};
	CaesarConvert convert{3};
	SimpleOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "Khoor Zruog"));
END_TEST

BEGIN_TEST(input_OneLinefile_output_simple_caesar)
	FileInput input("one_line.txt");
	CaesarConvert convert{3};
	SimpleOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "Khoor Zruog"));
END_TEST

BEGIN_TEST(input_TwoLinesfile_output_simple_caesar)
	FileInput input("two_lines.txt");
	CaesarConvert convert{3};
	SimpleOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "Zruog"));
END_TEST

BEGIN_TEST(input_TwoLinesfile_output_file_caesar)
	{
		FileInput input{"two_lines.txt"};
		CaesarConvert convert{3};
		FileOutput output{"test_out.txt"};
		LinkBox	simpleLinking(input, convert, output);
		simpleLinking.linking();
	}
	 ASSERT_EQUAL(returnFileContent("test_out.txt"), "Khoor Zruog");
END_TEST

BEGIN_TEST(input_file_output_simple_capital)
	FileInput input{"lower_case.txt"};
	CapitalizeConvert convert{};
	SimpleOutput output{};
	LinkBox	simpleLinking(input, convert, output);
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "  , Hello .World - Hi 123a"));
END_TEST

BEGIN_TEST(simple_vowel_censor)
	HardCodedInput input{};
	VowelCensorConvert convert{};
	SimpleOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "H*ll* W*rld"));
END_TEST

BEGIN_TEST(input_terminal_output_terminal_interactive)
	TerminalInput input{};
	SimpleConvert convert{};
	TerminalOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_THAT(true);
END_TEST

BEGIN_TEST(input_stream_output_simple_interactive)
	StreamInput input{std::cin, true};
	SimpleConvert convert{};
	SimpleOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	std::string result{output.m_result.text()};
	ASSERT_EQUAL(result, "q");
END_TEST

BEGIN_TEST(vowel_censor_consecutive)
	std::string stringvalues = "oriii ooksEEfUU";
	std::istringstream iss (stringvalues);
	StreamInput input{iss, true};
	VowelCensorConvert convert{};
	std::ostringstream foo;
	StreamOutput output{foo};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_EQUAL(foo.str(), "*r*** **ks**f**\n");
END_TEST

BEGIN_TEST(input_FiveLinesfile_output_simple)
	FileInput input{"five_rows.txt"};
	SimpleConvert convert{};
	SimpleOutput output{};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_THAT(!strcmp(output.m_result.text(), "row 5 hello"));
END_TEST

BEGIN_TEST(caesar_shift_bigger_then_26)
	std::string stringvalues = "ABCd";
	std::istringstream iss (stringvalues);
	StreamInput input{iss, true};
	CaesarConvert convert{27};
	std::ostringstream foo;
	StreamOutput output{foo};
	LinkBox	simpleLinking{input, convert, output};
	simpleLinking.linking();
	ASSERT_EQUAL(foo.str(), "BCDe\n");
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])	
	TEST(simple)
	IGNORE_TEST(udp)
	TEST(udp_output)
	IGNORE_TEST(udp_input)
	TEST(input_stream_output_simple)
	TEST(input_stream_output_stream_to_string)
	TEST(simple_caesar)
	TEST(input_OneLinefile_output_simple_caesar)
	TEST(input_TwoLinesfile_output_simple_caesar)
	TEST(input_TwoLinesfile_output_file_caesar)
	TEST(input_file_output_simple_capital)
	TEST(simple_vowel_censor)
	//interactive tests
	TEST(input_terminal_output_terminal_interactive)
	TEST(input_stream_output_simple_interactive)
	TEST(vowel_censor_consecutive)
	TEST(input_FiveLinesfile_output_simple)
	TEST(caesar_shift_bigger_then_26)
END_SUITE