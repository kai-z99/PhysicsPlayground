#include "../include/helpers.h"
#include <sstream>

b2Vec2 RotatePoint(b2Vec2& point, b2Vec2 center, float angle) //helper
{
    float tc = cosf(angle);
    float ts = sinf(angle);
    float x_rotated = ((point.x - center.x) * tc) - ((center.y - point.y) * ts) + center.x;
    float y_rotated = -center.y + ((center.y - point.y) * tc) + ((point.x - center.x) * ts);

    return { x_rotated , -y_rotated };


}

bool CheckCollisionCirclePoint(const sf::CircleShape& circle, const sf::Vector2i& point)
{
    float radius = circle.getRadius();
    sf::Vector2f center = circle.getPosition();


    float distanceSquared = (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y);

    return distanceSquared <= radius * radius;

}

std::string FloatToRoundedString(float f, int decimals)
{
    std::ostringstream oss;
    oss.precision(decimals);
    oss << std::fixed << f;
    return oss.str();


}

float RADTODEG = 180.0f / Constants::PI;
//bool CheckCollisionRecPoint(const sf::RectangleShape& rec, const sf::Vector2i& point)
//{
//   //
//}
