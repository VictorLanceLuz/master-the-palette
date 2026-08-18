#pragma once
#include <iostream>
#include <vector>
#include "ColorUtility.hpp"

class Color {
public:
	Color();
	Color(int red, int green, int blue);
	
	static Color fromPackedRgb(unsigned int packedRgb);
	static Color fromHexLiteral(const char* hexString);
	
	int red() const { return redChannel; }
	int green() const { return greenChannel; }
	int blue() const { return blueChannel; }

	// version for reading and modifying elements
	int& operator[](int index);

	// version for read-only access when object itself is `const`
	const int& operator[](int index) const;

private:
	int redChannel;
	int greenChannel;
	int blueChannel;
};

std::ostream& operator<<(std::ostream& os, const Color& color);
std::istream& operator>>(std::istream& is, Color& color);