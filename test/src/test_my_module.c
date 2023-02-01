#include "graphics_module.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void print_string(const char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        UNITY_OUTPUT_CHAR(str[i]);
        i++;
    }
}

void print_map(char **map)
{
	int i = 0;
	while (map[i])
	{
		print_string(map[i]);
		print_string("\n");
		i++;
	}
}

void test_get_scale_factor(void) {
    t_map map;
    char **mini_map;

    mini_map = (char **)malloc(sizeof(char *) * 4);

   mini_map[0] = (char *)malloc(sizeof(char) * 5);
   mini_map[0][0] = '1';
   mini_map[0][1] = '1';
   mini_map[0][2] = '1';
   mini_map[0][3] = '1';
   mini_map[0][4] = '\0';
   mini_map[1] = (char *)malloc(sizeof(char) * 5);
   mini_map[1][0] = '1';
   mini_map[1][1] = '0';
   mini_map[1][2] = '0';
   mini_map[1][3] = '1';
   mini_map[1][4] = '\0';
   mini_map[2] = (char *)malloc(sizeof(char) * 5);
   mini_map[2][0] = '1';
   mini_map[2][1] = '0';
   mini_map[2][2] = '0';
   mini_map[2][3] = '1';
   mini_map[2][4] = '\0';
   mini_map[3] = NULL;
    TEST_ASSERT_EQUAL_INT(get_scaling_factor(8, 8, &map), 2);
}

void test_scale_map(void) {
	int scaling_factor;
	char **scaled_map;
    t_map map;
    map.raw_map = (char **)malloc(sizeof(char *) * 4);

    map.raw_map[0] = (char *)malloc(sizeof(char) * 5);
    map.raw_map[0][0] = '1';
    map.raw_map[0][1] = '1';
    map.raw_map[0][2] = '1';
    map.raw_map[0][3] = '1';
    map.raw_map[0][4] = '\0';
    map.raw_map[1] = (char *)malloc(sizeof(char) * 5);
    map.raw_map[1][0] = '1';
    map.raw_map[1][1] = '0';
    map.raw_map[1][2] = '0';
    map.raw_map[1][3] = '1';
    map.raw_map[1][4] = '\0';
    map.raw_map[2] = (char *)malloc(sizeof(char) * 5);
    map.raw_map[2][0] = '1';
    map.raw_map[2][1] = '0';
    map.raw_map[2][2] = '0';
    map.raw_map[2][3] = '1';
    map.raw_map[2][4] = '\0';
    map.raw_map[3] = NULL;

    scaling_factor = get_scaling_factor(8, 8, &map);
    scaled_map = scale_map(map.raw_map, scaling_factor);
    print_map(map.raw_map);
	print_map(scaled_map);
	TEST_ASSERT_EQUAL_INT(scaling_factor, 2);
    TEST_ASSERT_EQUAL_STRING(scaled_map[0], "11111111");
    TEST_ASSERT_EQUAL_STRING(scaled_map[1], "11111111");
    TEST_ASSERT_EQUAL_STRING(scaled_map[2], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[3], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[4], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[5], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[6], NULL);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_scale_factor);
    RUN_TEST(test_scale_map);
    return UNITY_END();
}