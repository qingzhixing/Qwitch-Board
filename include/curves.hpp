#pragma once
#ifndef CURVES_HPP
#define CURVES_HPP

#include <math.h>

// lambda from 0 to 1
float lerp(float from, float to, float lambda)
{
	return (1 - lambda) * from + lambda * to;
}

// lambda from 0 to 1
float easeOutQuint(float lambda)
{
	return 1 - pow(1 - lambda, 5);
}

#endif //! CURVES_HPP