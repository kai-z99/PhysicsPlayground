#include "../include/helpers.h"


b2Vec2 RotatePoint(b2Vec2& point, b2Vec2 center, float angle) //helper
{
    float tc = cosf(angle);
    float ts = sinf(angle);
    float x_rotated = ((point.x - center.x) * tc) - ((center.y - point.y) * ts) + center.x;
    float y_rotated = -center.y + ((center.y - point.y) * tc) + ((point.x - center.x) * ts);

    return { x_rotated , -y_rotated };


}