#include <algorithm>
#include "../../Common/Maths.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

CollisionVolume::CollisionVolume(Shape shape, float width, NCL::Maths::Vector2* pos, float xOffset, float yOffset)
    : shape(shape), width(width), position(pos), X_OFFSET(xOffset), Y_OFFSET(yOffset)
{
}


CollisionVolume::~CollisionVolume()
{
}

bool CollisionVolume::squareCircleCollision(const CollisionVolume& square, const CollisionVolume& circle) {
    float circleWidth = circle.getWidth();
    float circleR = circleWidth * 0.5f;
    float circleX = circle.getPosition()->x + circle.getXOffset() + circleR;
    float circleY = circle.getPosition()->y + circle.getYOffset() + circleR;

    float squareWidth = square.getWidth();
    float squareHalfWidth = squareWidth * 0.5f;
    float squareX = square.getPosition()->x + square.getXOffset() + squareHalfWidth;
    float squareY = square.getPosition()->y + square.getYOffset() + squareHalfWidth;

    float xDifference = std::abs(circleX - squareX);
    float yDifference = std::abs(circleY - squareY);

    float minDistance = squareHalfWidth + circleR;

    if (xDifference > minDistance || yDifference > minDistance) { return false; }
    if (xDifference <= squareHalfWidth || yDifference <= squareHalfWidth) {return true; }

    float xDistance = xDifference - squareHalfWidth;
    float yDistance = yDifference - squareHalfWidth;
    float cornerDistanceSquared = (xDistance * xDistance) + (yDistance * yDistance);

    return cornerDistanceSquared <= (circleR * circleR);
}

bool CollisionVolume::circleCircleCollision(const CollisionVolume& thisCircle, const CollisionVolume& otherCircle) {
    float thisCircleWidth = thisCircle.getWidth();
    float thisCircleR = thisCircleWidth * 0.5f;
    float thisCircleX = thisCircle.getPosition()->x + thisCircle.getXOffset() + thisCircleR;
    float thisCircleY = thisCircle.getPosition()->y + thisCircle.getYOffset() + thisCircleR;

    float otherCircleWidth = otherCircle.getWidth();
    float otherCircleR = otherCircleWidth * 0.5f;
    float otherCircleX = otherCircle.getPosition()->x + otherCircle.getXOffset() + otherCircleR;
    float otherCircleY = otherCircle.getPosition()->y + otherCircle.getYOffset() + otherCircleR;

    float distanceDiff = sqrt(
            pow(abs(otherCircleX - thisCircleX), 2) +
            pow(abs(otherCircleY - thisCircleY), 2));

    return distanceDiff < (otherCircleR + thisCircleR);
}

bool CollisionVolume::squareSquareCollision(const CollisionVolume& thisSquare, const CollisionVolume& otherSquare) {
    float otherSquareWidth = otherSquare.getWidth();
    float otherSquareHalfWidth = otherSquareWidth * 0.5f;
    float otherSquareX = otherSquare.getPosition()->x + otherSquare.getXOffset() + otherSquareHalfWidth;
    float otherSquareY = otherSquare.getPosition()->y + otherSquare.getYOffset() + otherSquareHalfWidth;

    float thisSquareWidth = thisSquare.getWidth();
    float thisSquareHalfWidth = thisSquareWidth * 0.5f;
    float thisSquareX = thisSquare.getPosition()->x + thisSquare.getXOffset() + thisSquareHalfWidth;
	float thisSquareY = thisSquare.getPosition()->y + thisSquare.getYOffset() + thisSquareHalfWidth;

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

const float CollisionVolume::getXOffset() const {
    return X_OFFSET;
}

const float CollisionVolume::getYOffset() const {
    return Y_OFFSET;
}
