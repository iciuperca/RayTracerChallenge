#ifndef CANVAS_H_
#define CANVAS_H_

#include <cstdint>
#include <vector>

#include "Color.h"

constexpr uint32_t TwoDimensionToOne(const uint32_t width, const uint32_t x, const uint32_t y)
{
	return width * y + x;
}

struct Canvas
{
	Canvas(const uint32_t w, const uint32_t h);

	void WritePixel(uint32_t x, uint32_t y, const Color& color);
	[[ nodiscard ]] Color PixelAt(uint32_t x, uint32_t y) const;
	void Fill(const Color& color);
	[[ nodiscard ]] std::string ToPpm() const;
	
	uint32_t width;
	uint32_t height;

	std::vector<Color> pixels;
};

#endif // !CANVAS_H_