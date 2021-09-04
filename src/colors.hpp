#pragma once

// Header file defining colors

enum class color_t : uint8_t
{
	colorless = 0,
	all = colorless,
	red = 1,
	green = 2,
	yellow = 3

};


namespace color
{
	static const char* Color_names[] = {"colorless/all", "red", "green", "yellow"};

	std::string color_str(color_t color)
	{
		return color::Color_names[static_cast<unsigned int>(color)];
	}
};






//constexpr MaxSig = static_cast<unsigned int>(signal::Max);


