#include "../include/RayTracerLib/Canvas.h"
#include "../include/RayTracerLib/RayMath.h"

#include <sstream>

Canvas::Canvas(const uint32_t w, const uint32_t h): width(w), height(h)
{
	const auto pixelCount = width * height;
	pixels.reserve(pixelCount);
	const Color color(0.0f, 0.0f, 0.0f);
	for (uint64_t i = 0; i < pixelCount; ++i)
	{
		pixels.push_back(color);
	};
}

void Canvas::WritePixel(const uint32_t x, const uint32_t y, const Color& color)
{
	const auto subscript = TwoDimensionToOne(width, x, y);
	pixels[subscript] = color;
}

Color Canvas::PixelAt(const uint32_t x, const uint32_t y) const
{
	const auto subscript = TwoDimensionToOne(width, x, y);
	return pixels[subscript];
}

void Canvas::Fill(const Color& color)
{
	const auto pixelCount = width * height;
	for (auto& pixel : pixels)
	{
		pixel = color;
	}
}

std::string Canvas::ToPpm() const
{
	auto addToLine = [] (std::stringstream &ppmSs, std::string& lineString, const std::string& color, const size_t maxLineLength)
	{
		const auto newLine = '\n';
		const auto colorString = lineString.empty() ? color : std::string(" ") + color;
		const auto newLineBeforeColor = lineString.length() >= (maxLineLength - colorString.length());
		if (newLineBeforeColor)
		{
			ppmSs << lineString << newLine;
			lineString.clear();
			lineString += color;
		}
		else
		{
			lineString += colorString;
		}	
	};
	std::stringstream ppmSs;
	std::string lineString;
	const auto newLine = '\n';
	ppmSs << "P3" << newLine
		<< width << " " << height << newLine
		<< 255 << newLine
	;
	//PPM file lines should not be longer than 70 chars. If we reach 70 chars before the next canvas line then break. Also break on new canvas line
	// The max single color length is 3 (for example for 255)
	const auto maxLineLength = static_cast<uint32_t>(70);
	for (uint32_t y = 0; y < height; ++y)
	{
		for (uint32_t x = 0; x < width; ++x)
		{
			const auto color = PixelAt(x, y);
			addToLine(ppmSs, lineString, std::to_string(ColorFloatToUint8(color.r)), maxLineLength);
			addToLine(ppmSs, lineString, std::to_string(ColorFloatToUint8(color.g)), maxLineLength);
			addToLine(ppmSs, lineString, std::to_string(ColorFloatToUint8(color.b)), maxLineLength);	
		}

		if (!lineString.empty())
		{
			ppmSs << lineString << newLine;
			lineString.clear();
		}
	}

	if (!lineString.empty())
	{
		ppmSs << lineString << newLine;
		lineString.clear();
	}

	return ppmSs.str();
}
