#pragma once

#include <stdlib.h>
#include <limits>

struct MapNode {
	MapNode()
		: bestParent(nullptr), g(0.0f), h(9999), isTraversable(true), isClosed(false)
	{}

	MapNode* bestParent;

	int x;
	int y;

	float cost;
	float g;
	float h;

	bool isTraversable;
	bool isClosed;

	float f() {
		return g + h;
	}

	void updateHeuristic(int destX, int destY) {
		h = abs(x - destX) + abs(y - destY);
	}
};