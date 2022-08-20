#ifndef __STYLE__
#define __STYLE__

#include "Math/Vector4.hpp"
#include "Math/Vector3.hpp"

#include <string>

using namespace std;

class Window;

enum StyleValueType {
    pixel,
    percentage,
    viewport_height,
    viewport_width
};

struct Size {
    float value = 0;
    StyleValueType type = pixel;

    explicit Size(string _value);
    float Get(float parent, Window* window) const;
};

struct Style {
    Vector4 background_color;
    Vector4 color;
    //Top Right Bottom Left
    Vector4 margin;
    //Top Right Bottom Left
    Vector4 padding;
    Size width = Size("0px");
    Size height = Size("0px");
    int z = 1;

    Vector2 GetPosition(Vector2 parent);
    Vector2 GetSize(Vector2 parent, Window* window);
};

#endif