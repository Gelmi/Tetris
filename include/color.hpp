#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
    private:
        unsigned char r, g, b;

    public:
        Color(unsigned char r, unsigned char g, unsigned char b);
        unsigned char getRed();
        unsigned char getBlue();
        unsigned char getGreen();
};

#endif
