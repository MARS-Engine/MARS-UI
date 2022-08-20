#include "Style.hpp"
#include "Debug/Debug.hpp"
#include "Math/Math.hpp"
#include "Graphics/Window.hpp"

Size::Size(string _value) {

    if (_value.size() < 3) {
        Debug::Alert("Size - Invalid value size " + _value);
        return;
    }

    int length = !isdigit(_value[_value.size() - 3]) ? 3 : !isdigit(_value[_value.size() - 2]) ? 2 : !isdigit(_value[_value.size() - 1]) ? 1 : 0;

    string newResult = _value.substr(0, _value.size() - length);

    if (!is_number(newResult)) {
        Debug::Alert("Size - Invalid value " + _value);
        return;
    }

    value = stoi(newResult);

    string _type = _value.substr(_value.size() - length);

    if (_type == "px")
        type = pixel;
    if (_type == "%")
        type = percentage;
    if (_type == "vh")
        type = viewport_height;
    if (_type == "vw")
        type = viewport_width;
}

float Size::Get(float parent, Window* window) const {
    switch (type) {
        case pixel:
            return value;
        case percentage:
            return value * parent / 100;
        case viewport_height:
            return value * (float)window->windowSize.height / 100;
        case viewport_width:
            return value * (float)window->windowSize.width / 100;
    }
}

Vector2 Style::GetPosition(Vector2 parent) {
    Vector2 pos = parent;

    pos.x += margin.w;
    pos.y += margin.x;

    return pos;
}

Vector2 Style::GetSize(Vector2 parent, Window* window) {
    Vector2 size = Vector2();
    size.x = width.Get(parent.x, window) + padding.w + padding.y - margin.w - margin.y;
    size.y = height.Get(parent.y, window) + padding.z + padding.x - margin.x - margin.z;
    return size;
}