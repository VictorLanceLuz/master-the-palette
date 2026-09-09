#include <iostream>
#include <vector>
#include "Color.hpp"

int main() {
	std::cout << std::boolalpha;  // print bools as true/false
	
	// You can give this color in two equivalent ways:
	//
	// 1. Hex (base-16): 0x50C878
	// 2. Decimal RGB (base-10): 80, 200, 120
	//
	// Each pair of hex digits converts to its decimal RGB value:
	// 0x50 → 80, 0xC8 → 200, 0x78 → 120
	Color emerald = Color::fromHexLiteral("#50c878");
	Color sunset = Color::fromHexLiteral("#ff4500");
	Color ocean  = Color::fromHexLiteral("#1e90ff");

	std::cout << emerald[0] << ", " << emerald[1] << ", " << emerald[2] << std::endl;
	
	// blending colors
	Color dusk = sunset + ocean;
	std::cout << "Dusk: " << dusk << std::endl;

	// using adjustments
	std::vector<int> warmUp = {30, -10, -10};
	dusk = dusk + warmUp;
	std::cout << "Dusk after adjustments: " << dusk << std::endl;

	// using prefix increment.
	++dusk;
	std::cout << "Dusk after prefix increment: " << dusk << std::endl;

	// using prefix decrement.
	--sunset;
	std::cout << "Sunset after prefix decrement: " << sunset << std::endl;

	// using scale.
	Color duskBoost = dusk * 2;
	std::cout << "Duskboost after scaling dusk * 2: " << duskBoost << std::endl;
	
	// using functor.
	std::cout << "Dusk after invert: " << dusk(ColorUtility::invert) << std::endl;

	// using comparison
	bool res = dusk == duskBoost; 
	std::cout << "Comparison between dusk and duskBoost: " << res << std::endl;
}
	