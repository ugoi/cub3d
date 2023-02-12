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

void test_get_fscaling_factor(void) {
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

   map.raw_map_dimensions = get_map_dimesnions(map.raw_map);
    TEST_ASSERT_EQUAL_INT(2, get_fscaling_factor(map.raw_map_dimensions, (t_int_vector){10, 10}));
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

    map.raw_map_dimensions = get_map_dimesnions(map.raw_map);
	// scaling_factor = get_fscaling_factor(8, 8, &map);
    scaling_factor = get_fscaling_factor(map.raw_map_dimensions, (t_int_vector){8, 8});

    scaled_map = scale_map(map.raw_map, scaling_factor);
	TEST_ASSERT_EQUAL_INT(scaling_factor, 2);
    TEST_ASSERT_EQUAL_STRING(scaled_map[0], "11111111");
    TEST_ASSERT_EQUAL_STRING(scaled_map[1], "11111111");
    TEST_ASSERT_EQUAL_STRING(scaled_map[2], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[3], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[4], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[5], "11000011");
    TEST_ASSERT_EQUAL_STRING(scaled_map[6], NULL);
}

void test_add_radians(void)
{
// Player pos: 4.400000, 1.900001
// Ray0 pos: (3.048681, 4.000000) angle: 2.142578
// Ray1 pos: (2.996259, 4.000000) angle: 2.160031
// Ray2 pos: (2.942599, 4.000000) angle: 2.177485 1
// Ray5 pos: (2.773382, 4.000000) angle: 2.229844 2
// Ray6 pos: (2.713930, 4.000000) angle: 2.247297
// Ray7 pos: (2.652789, 4.000000) angle: 2.264750
// Ray8 pos: (2.589845, 4.000000) angle: 2.282204
// Ray9 pos: (2.524979, 4.000000) angle: 2.299657

	float radians = 2.177485;
	float increment = DEG_TO_RAD * RESOLUTION;
	float expected;
	// float radians_to_add = 0.0;

	for (int i = 0; i < 10; i++)
	{
		expected = radians + increment;
		// if (i == 2)
		// 	expected = 0;
		radians = add_radians(radians, DEG_TO_RAD * RESOLUTION);
		printf("radians: %f\n", radians);
		// radians = add_radians(radians, increment);
		TEST_ASSERT_EQUAL_FLOAT(expected, radians);
	}


}

void test_init_texture()
{
	char **map;
	char *map_path = "textures/south_texture.txt";
	char expected[] = "00100";


	map = init_texture(map_path);
	TEST_ASSERT_EQUAL_STRING(expected, map[0]);
}

void test_texture(void)
{
	t_vars		vars;
	t_float_vector ray_pos;
	t_texture texture;
	t_ray ray;

	ray_pos = (t_float_vector){1.1, 1};
	ray.origin = (t_float_vector){0, 0};
	ray.ray_vector = (t_float_vector){1.1, 1};

	texture.texture = init_texture("textures/south_texture.txt");
	texture.dimensions = get_map_dimesnions(texture.texture);

	vars.mlx = mlx_init(WIDTH, HEIGHT, "Test", false);
	if (!vars.mlx)
		error();
	vars.main_img = mlx_new_image(vars.mlx, vars.mlx->width, vars.mlx->height);
	if (!vars.main_img)
		error();
	draw_main(vars.main_img, 1, 1);
	draw_columns_with_texture(vars.main_img, (t_texdim){0, 100, 200, 400}, ray, texture);
	if (mlx_image_to_window(vars.mlx, vars.main_img, 0, 0) < 0)
		error();
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.map_img);
	mlx_delete_image(vars.mlx, vars.main_img);
	mlx_terminate(vars.mlx);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_fscaling_factor);
    RUN_TEST(test_scale_map);
	RUN_TEST(test_add_radians);
	RUN_TEST(test_init_texture);
	RUN_TEST(test_init_texture);
	RUN_TEST(test_texture);
    return UNITY_END();
}
