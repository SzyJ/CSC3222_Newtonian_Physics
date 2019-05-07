#include <algorithm>
#include "../../Common/Maths.h"
#include "CollisionVolume.h"
#include "Math.h"

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

CollisionResolution  CollisionVolume::testCCCol(const CollisionVolume& thisCircle, const CollisionVolume& otherCircle) {
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

	bool colides = distanceDiff < (otherCircleR + thisCircleR);

	float pen = (thisCircleR + otherCircleR) - distanceDiff;
	NCL::Maths::Vector2 normal(thisCircleX - otherCircleX, thisCircleY - otherCircleY);
	normal.normalize();

	return CollisionResolution(pen, normal);

}

CollisionResolution CollisionVolume::testSCCol(const CollisionVolume& shape1, const CollisionVolume& shape2) {
	const CollisionVolume* square = nullptr;
	const CollisionVolume* circle = nullptr;

	bool isSquareFirst;

	if (shape1.getShape() == Shape::Square && shape2.getShape() == Shape::Circle) {
		square = &shape1;
		circle = &shape2;
		isSquareFirst = true;
	} else if (shape1.getShape() == Shape::Circle && shape2.getShape() == Shape::Square) {
		square = &shape2;
		circle = &shape1;
		isSquareFirst = false;
	} else {
		return CollisionResolution::noCollision();
	}

	float squareWidth = square->getWidth();
	float squareHalfWdth = squareWidth * 0.5;
	float squareLeftX = square->getPosition()->x + square->getXOffset();
	float squareRightX = squareLeftX + squareWidth;
	float squareUpperY = square->getPosition()->y + square->getYOffset();
	float squareLowerY = squareUpperY + squareWidth;

	float circleWidth = circle->getWidth();
	float circleR = circleWidth * 0.5;
	float circleX = circle->getPosition()->x + circle->getXOffset() + circleR;
	float circleY = circle->getPosition()->y + circle->getYOffset() + circleR;

	float closestSquareEdgeX = clamp(circleX, squareLeftX, squareRightX);
	float closestSquareEdgeY = clamp(circleY, squareUpperY, squareLowerY);

	// TODO: edge case of circle centre inside of square will not work.
	if (squareLeftX < circleX && squareRightX > circleX &&
		squareUpperY < circleY && squareLowerY > circleY) {
		return CollisionResolution::noCollision();
	}
	
	float edgeXDelta = closestSquareEdgeX - circleX;
	float edgeYDelta = closestSquareEdgeY - circleY;

	float distToEdge = sqrt((edgeXDelta * edgeXDelta) + (edgeYDelta * edgeYDelta));

	if (distToEdge >= circleR) {
		return CollisionResolution::noCollision();
	}

	NCL::Maths::Vector2 normal(circleX - closestSquareEdgeX, circleY - closestSquareEdgeY);
	normal.normalize();

	if (!isSquareFirst) {
		normal *= -1;
	}
	return CollisionResolution(circleR - distToEdge, normal);
}

CollisionResolution CollisionVolume::testSSCol(const CollisionVolume& thisSquare, const CollisionVolume& otherSquare) {
	float thisSquareWidth = thisSquare.getWidth();
	float thisSquareLeftX = thisSquare.getPosition()->x + thisSquare.getXOffset();
	float thisSquareRightX = thisSquareLeftX + thisSquareWidth;
	float thisSquareUpperY = thisSquare.getPosition()->y + thisSquare.getYOffset();
	float thisSquareLowerY = thisSquareUpperY + thisSquareWidth;

	float otherSquareWidth = otherSquare.getWidth();
	float otherSquareLeftX = otherSquare.getPosition()->x + otherSquare.getXOffset();
	float otherSquareRightX = otherSquareLeftX + otherSquareWidth;
	float otherSquareUpperY = otherSquare.getPosition()->y + otherSquare.getYOffset();
	float otherSquareLowerY = otherSquareUpperY + otherSquareWidth;
 
	float xOverlap = (std::min)(
		std::abs(thisSquareLeftX - otherSquareRightX),
		std::abs(thisSquareRightX - otherSquareLeftX)
		);
	float yOverlap = (std::min)(
		std::abs(thisSquareUpperY - otherSquareLowerY),
		std::abs(thisSquareLowerY - otherSquareUpperY)
		);

	return CollisionResolution::noCollision();
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

CollisionResolution CollisionVolume::collidesWithTest(const CollisionVolume* other) {
	Shape otherShape = other->getShape();

	if (shape == Shape::Square && otherShape == Shape::Square) {
		//return squareSquareCollision(*this, *other);
	}
	else if (shape == Shape::Circle && otherShape == Shape::Circle) {
		return testCCCol(*this, *other);
	}
	else if (shape == Shape::Circle && otherShape == Shape::Square) {
		return testSCCol(*other, *this);
	}
	else if (shape == Shape::Square && otherShape == Shape::Circle) {
		return testSCCol(*this, *other);
	}

	return CollisionResolution::noCollision();
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