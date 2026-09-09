#include "Color.hpp"
#include <iomanip>

Color::Color() : redChannel(0), greenChannel(0), blueChannel(0) {}

Color::Color(int red, int green, int blue)
{
    redChannel = CLIP(red);
    greenChannel = CLIP(green);
    blueChannel = CLIP(blue);
}

Color Color::fromPackedRgb(unsigned int packedRgb)
{
    return Color(int((packedRgb >> 16) & 0xffu),
                 int((packedRgb >> 8) & 0xffu),
                 int(packedRgb & 0xffu));
}

Color Color::fromHexLiteral(const char *hexString)
{
    if (!hexString || hexString[0] != '#')
    {
        throw std::invalid_argument("hex literal must start with #");
    }
    int digits[6];
    for (int i = 0; i < 6; ++i)
    {
        int val = ColorUtility::fromHexDigit(hexString[i + 1]);
        if (val < 0)
        {
            throw std::invalid_argument("invalid hex digit");
        }
        digits[i] = val;
    }
    return Color(digits[0] * 16 + digits[1],
                 digits[2] * 16 + digits[3],
                 digits[4] * 16 + digits[5]);
}

int &Color::operator[](int index)
{
    switch (index)
    {
    case 0:
        return redChannel;
    case 1:
        return greenChannel;
    case 2:
        return blueChannel;
    default:
        throw std::out_of_range("Color index");
    }
}

const int &Color::operator[](int index) const
{
    switch (index)
    {
    case 0:
        return redChannel;
    case 1:
        return greenChannel;
    case 2:
        return blueChannel;
    default:
        throw std::out_of_range("Color index");
    }
}

Color Color::operator+(const Color &other) const
{
    const auto newRedChannel = (redChannel + other.redChannel) / 2;
    const auto newGreenChannel = (greenChannel + other.greenChannel) / 2;
    const auto newBlueChannel = (blueChannel + other.blueChannel) / 2;
    return {newRedChannel, newGreenChannel, newBlueChannel};
}

Color Color::operator+(const std::vector<int> adjustments) const
{
    int r = redChannel + (adjustments.size() > 0 ? adjustments[0] : 0); // if not empty, use value, else use '0'. 
    int g = greenChannel + (adjustments.size() > 1 ? adjustments[1] : 0); // if 2nd pos empty, use value, etc.
    int b = blueChannel + (adjustments.size() > 2 ? adjustments[2] : 0); 
    r = CLIP(r); // these will push high values to valid values: 0-255
    g = CLIP(g);
    b = CLIP(b);

    return Color(r, g, b);
}

Color& Color::operator++()
{
    redChannel = CLIP(++redChannel);
    greenChannel = CLIP(++greenChannel);
    blueChannel = CLIP(++blueChannel);
    return *this;
}

Color &Color::operator--()
{
    redChannel = CLIP(--redChannel);
    greenChannel = CLIP(--greenChannel);
    blueChannel = CLIP(--blueChannel);
    return *this;
}

Color Color::operator*(int scale) const
{
    const int r = CLIP(redChannel * scale); 
    const int g = CLIP(greenChannel * scale); 
    const int b = CLIP(blueChannel * scale);

    return Color(r, g, b); 
}

Color Color::operator()(int (*transform)(int)) const
{
    const int r = CLIP(transform(redChannel));
    const int g = CLIP(transform(greenChannel)); 
    const int b = CLIP(transform(blueChannel));
    
    return Color(r, g, b);
}

bool Color::operator==(const Color& other) const
{
    return redChannel == other.redChannel && 
            greenChannel == other.greenChannel &&    
            blueChannel == other.blueChannel;
}

std::ostream &operator<<(std::ostream &os, const Color &color)
{
    os << '#' << std::hex << std::setfill('0') << std::setw(2) << color.red()
       << std::setw(2) << color.green()
       << std::setw(2) << color.blue() << std::dec;
    return os;
}

std::istream &operator>>(std::istream &is, Color &color)
{
    std::string token;
    is >> token;
    color = Color::fromHexLiteral(token.c_str());
    return is;
}
