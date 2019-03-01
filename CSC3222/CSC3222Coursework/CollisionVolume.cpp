#include <algorithm>
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

CollisionVolume::CollisionVolume(Shape shape, float width, NCL::Maths::Vector2* pos)
    : shape(shape), width(width), position(pos)
{
}


CollisionVolume::~CollisionVolume()
{
}

bool CollisionVolume::squareCircleCollision(const CollisionVolume& square, const CollisionVolume& circle) {
    float circleWidth = circle.getWidth();
    float circleR = circleWidth * 0.5f;
    float circleX = circle.getPosition()->x + circleR;
    float circleY = circle.getPosition()->y + circleR;

    float squareWidth = square.getWidth();
    float squareHalfWidth = squareWidth * 0.5f;
    float squareX = square.getPosition()->x + squareHalfWidth;
    float squareY = square.getPosition()->y + squareHalfWidth;
    float squareLeftEdge =  squareX - squareHalfWidth;
    float squareRightEdge = squareX + squareHalfWidth;
    float squareLowerEdge = squareY + squareHalfWidth;
    float squareUpperEdge = squareY - squareHalfWidth;

    float xDiff = circleX - std::max(squareLeftEdge, std::min(circleX, squareRightEdge));
    float yDiff = circleY - std::max(squareLowerEdge, std::min(circleY, squareUpperEdge));

    return (xDiff * xDiff + yDiff * yDiff) < (circleR * circleR);
}

bool CollisionVolume::circleCircleCollision(const CollisionVolume& thisCircle, const CollisionVolume& otherCircle) {
    float thisCircleWidth = thisCircle.getWidth();
    float thisCircleR = thisCircleWidth * 0.5f;
    float thisCircleX = thisCircle.getPosition()->x + thisCircleR;
    float thisCircleY = thisCircle.getPosition()->y + thisCircleR;

    float otherCircleWidth = otherCircle.getWidth();
    float otherCircleR = otherCircleWidth * 0.5f;
    float otherCircleX = otherCircle.getPosition()->x + otherCircleR;
    float otherCircleY = otherCircle.getPosition()->y + otherCircleR;

    float distanceDiff = sqrt(
            pow(abs(otherCircleX - thisCircleX), 2) +
            pow(abs(otherCircleY - thisCircleY), 2));

    return distanceDiff < (otherCircleR + thisCircleR);
}

bool CollisionVolume::squareSquareCollision(const CollisionVolume& thisSquare, const CollisionVolume& otherSquare) {
    float otherSquareWidth = otherSquare.getWidth();
    float otherSquareHalfWidth = otherSquareWidth * 0.5f;
    float otherSquareX = otherSquare.getPosition()->x + otherSquareHalfWidth;
    float otherSquareY = otherSquare.getPosition()->y + otherSquareHalfWidth;

    float thisSquareWidth = thisSquare.getWidth();
    float thisSquareHalfWidth = thisSquareWidth * 0.5f;
    float thisSquareX = thisSquare.getPosition()->x + thisSquareHalfWidth;
	float thisSquareY = thisSquare.getPosition()->y + thisSquareHalfWidth;

    return (abs(otherSquareX - thisSquareX) * 2 < (otherSquareWidth + thisSquareWidth)) &&
           (abs(otherSquareY - thisSquareY) * 2 < (otherSquareWidth + thisSquareWidth));
}

bool CollisionVolume::collidesWith(const CollisionVolume* other) {
    Shape otherShape = other->getShape();
    if (shape == Shape::Square && otherShape == Shape::Square) {
        return squareSquareCollision(*this, *other);
    } else if (shape == Shape::Circle && otherShape == Shape::Circle) {
        return circleCircleCollision(*this, *other);
    } else if (shape == Shape::Circle && otherShape == Shape::Square) {
        return squareCircleCollision(*other, *this);
    } else if (shape == Shape::Square && otherShape == Shape::Circle) {
        return squareCircleCollision(*this, *other);
    }

	return false;
}

const Shape CollisionVolume::getShape() const {
    return shape;
}

const float CollisionVolume::getWidth() const {
    return width;
}

const NCL::Maths::Vector2* CollisionVolume::getPosition() const {
    return position;
}