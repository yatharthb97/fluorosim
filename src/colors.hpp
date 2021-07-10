#pragma once

// Header file defining colors

enum class color_t
{
	colorless = 0,
	all = colorless,
	red,
	green,
	yellow

};


namespace color
{
	static const char* Color_names[] = {"colorless/all", "red", "green", "yellow"};

	std::string color_str(color_t color)
	{
		return color::Color_names[static_cast<unsigned int>(color)];
	}
};
