#include "mu_test.h"
#include "color_image.hpp"
#include "color_rgb.hpp"
#include "color_image.hpp"
#include "draw_primitives.hpp"

#include <string>

BEGIN_TEST(image_ctor)
	advcpp::ColorImage test(10, 14);
	ASSERT_EQUAL(sizeof(test), 48);
END_TEST

BEGIN_TEST(copy_image)
	advcpp::ColorImage test(10, 14);
	test.WritePixel({0, 0}, {15, 11, 200});
	advcpp::ColorImage test2(test);
	ASSERT_EQUAL(test2.ReadPixel({0, 0}).m_red, 15);
	ASSERT_EQUAL(test2.ReadPixel({0, 0}).m_green, 11);
	ASSERT_EQUAL(test2.ReadPixel({0, 0}).m_blue, 200);
END_TEST

BEGIN_TEST(read_index_out_of_range)
	try {
		advcpp::ColorImage test(10, 14);
		ASSERT_EQUAL(test.ReadPixel({11, 0}).m_red, 15);
	}catch(std::exception const& x){
        ASSERT_THAT(!strcmp(x.what(), "index out of range"));
	}
END_TEST

BEGIN_TEST(write_index_out_of_range)
	try {
		advcpp::ColorImage test(10, 14);
		test.WritePixel({11, 0}, {15, 16, 17});
		ASSERT_THAT(false);
	}catch(std::exception const& x){
        ASSERT_THAT(!strcmp(x.what(), "index out of range"));
	}
END_TEST

BEGIN_TEST(load)
	advcpp::ColorImage test = advcpp::LoadColorImage("parrot.ppm");
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_red, 145);
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_green, 201);
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_blue, 248);
END_TEST

BEGIN_TEST(load_file_not_found)
	try {
		advcpp::ColorImage test = advcpp::LoadColorImage("parrot1.ppm");
		ASSERT_EQUAL(test.ReadPixel({0, 0}).m_red, 145);
	}catch(std::exception const& x){
		std::cout << ">>>> w caught :" << x.what() << '\n';
        ASSERT_THAT(!strcmp(x.what(), "basic_ios::clear: iostream error")); 
	}
END_TEST

BEGIN_TEST(save)
	advcpp::ColorImage test = advcpp::LoadColorImage("parrot.ppm");
	advcpp::SaveColorImage(test, "test3.ppm");
	advcpp::ColorImage test3 = advcpp::LoadColorImage("test3.ppm");
	ASSERT_EQUAL(test3.ReadPixel({0, 0}).m_red, 145);
END_TEST

BEGIN_TEST(reduce_color_depth)
	advcpp::ColorImage test = advcpp::LoadColorImage("parrot.ppm");
	unsigned int oldRed = test.ReadPixel({0, 0}).m_red;
	test.ReduceColorDepth(5);
	unsigned int newRed = test.ReadPixel({0, 0}).m_red;
	advcpp::SaveColorImage(test, "test3.ppm");
	ASSERT_EQUAL(newRed, oldRed * 5 / 255);
END_TEST

BEGIN_TEST(scale_down_size)
	advcpp::ColorImage test(1000, 1000);
	test.ScaleDownSize(2);
	advcpp::SaveColorImage(test, "small.ppm");
	ASSERT_EQUAL(1, 1);
END_TEST

BEGIN_TEST(draw_horizontal_line)
	advcpp::ColorImage test(20, 20);
	advcpp::DrawHorizontalLine(test, {0, 19}, 5, {100, 100, 100});
	advcpp::SaveColorImage(test, "horizontalLine.ppm");
	for(size_t i = 0; i < 20; ++i) {
		ASSERT_EQUAL(test.ReadPixel({0, 5}).m_red, 100);
		ASSERT_EQUAL(test.ReadPixel({0, 5}).m_green, 100);
		ASSERT_EQUAL(test.ReadPixel({0, 5}).m_blue, 100);
	}

END_TEST

BEGIN_TEST(draw_vertical_line)
	advcpp::ColorImage test = advcpp::LoadColorImage("parrot.ppm");
	advcpp::DrawVerticalLine(test, {0, 599}, 50, {0, 0, 255});
	for(size_t i = 0; i < 600; ++i) {
		ASSERT_EQUAL(test.ReadPixel({50, i}).m_red, 0);
		ASSERT_EQUAL(test.ReadPixel({50, i}).m_green, 0);
		ASSERT_EQUAL(test.ReadPixel({50, i}).m_blue, 255);
	}
END_TEST

BEGIN_TEST(white_image)
	advcpp::ColorImage test = advcpp::LoadColorImage("parrot.ppm");
	test.Clear();
	advcpp::SaveColorImage(test, "blank.ppm");
	for(size_t col = 0; col < test.Width(); ++col) {
		for(size_t row = 0; row < test.Height(); ++row) {
			ASSERT_EQUAL(test.ReadPixel({col, row}).m_red, 255);
			ASSERT_EQUAL(test.ReadPixel({col, row}).m_green, 255);
			ASSERT_EQUAL(test.ReadPixel({col, row}).m_blue, 255);
		}
	}
END_TEST

BEGIN_TEST(draw_line_in_range)
	advcpp::ColorImage test(1000, 1000);
	advcpp::DrawLine(test, {0, 0}, {999, 999}, {10, 10, 10});
	advcpp::SaveColorImage(test, "line.ppm");
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_red, 10);
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_green, 10);
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_blue, 10);
	ASSERT_EQUAL(test.ReadPixel({999, 999}).m_red, 10);
	ASSERT_EQUAL(test.ReadPixel({999, 999}).m_green, 10);
	ASSERT_EQUAL(test.ReadPixel({999, 999}).m_blue, 10);
END_TEST

BEGIN_TEST(draw_line_out_of_range)
	advcpp::ColorImage test(1000, 1000);
	advcpp::DrawLine(test, {-10, -10}, {5000, 5000}, {10, 10, 10});
	advcpp::SaveColorImage(test, "line.ppm");
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_red, 10);
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_green, 10);
	ASSERT_EQUAL(test.ReadPixel({0, 0}).m_blue, 10);
	ASSERT_EQUAL(test.ReadPixel({999, 999}).m_red, 10);
	ASSERT_EQUAL(test.ReadPixel({999, 999}).m_green, 10);
	ASSERT_EQUAL(test.ReadPixel({999, 999}).m_blue, 10);
END_TEST

BEGIN_TEST(draw_circle)
	advcpp::ColorImage test(1000, 1000);
	advcpp::DrawCircle(test, 500, 500, 100, {100, 100, 100});
	advcpp::SaveColorImage(test, "circle.ppm");
	ASSERT_EQUAL(test.ReadPixel({400, 500}).m_red, 100);
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])	
	TEST(image_ctor)
	TEST(copy_image)
	TEST(read_index_out_of_range)
	TEST(write_index_out_of_range)
	TEST(load)
	TEST(load_file_not_found)
	TEST(save) 
	TEST(reduce_color_depth)
	TEST(scale_down_size)
	TEST(draw_horizontal_line)
	TEST(draw_vertical_line)
	TEST(white_image)
	TEST(draw_line_in_range)
	TEST(draw_line_out_of_range)
	TEST(draw_circle)

END_SUITE
