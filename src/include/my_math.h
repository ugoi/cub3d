#ifndef MY_MATH_H
#define MY_MATH_H

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct s_int_vector
{
	int	x;
	int	y;
}				t_int_vector;

typedef struct s_float_vector
{
	float	x;
	float	y;
}				t_float_vector;

#endif