#pragma once
#ifndef CURVES_HPP
#define CURVES_HPP

#include <cmath>

// lambda from 0 to 1
inline float lerp(const float from, const float to, const float lambda) {
	return (1 - lambda) * from + lambda * to;
}

// lambda from 0 to 1
inline float easeOutQuint(const float lambda) {
	return 1 - pow(1 - lambda, 5);
}

// lambda from 0 to 1
inline float easeInOutBack(const float lambda) {
	constexpr float c1 = 1.70158;
	constexpr float c2 = c1 * 1.525;

	return lambda < 0.5
		       ? (pow(2 * lambda, 2) * ((c2 + 1) * 2 * lambda - c2)) / 2
		       : (pow(2 * lambda - 2, 2) * ((c2 + 1) * (lambda * 2 - 2) + c2) + 2) / 2;
}

inline float easeOutCirc(const float lambda) {
	return static_cast<float>(sqrt(1 - pow(lambda - 1, 2)));
}

inline float easeInOutQuad(const float lambda) {
	return static_cast<float>(lambda < 0.5 ? 2 * lambda * lambda : 1 - pow(-2 * lambda + 2, 2) / 2);
}
#endif //! CURVES_HPP
