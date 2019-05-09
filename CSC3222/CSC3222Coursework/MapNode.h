#pragma once

#include <stdlib.h>
#include <limits>

struct MapNode {
	MapNode()
		: bestParent(nullptr), cost(1.0f), h(std::numeric_limits<float>::infinity()), isTraversable(true), isClosed(false)
	{}

	MapNode* bestParent;

	int x;
	int y;

	float cost;
	float h;

	bool isTraversable;
	bool isClosed;

	float getCumulativeCost() {
		if (bestParent == nullptr) {
			return cost;
		}

		return cost + bestParent->getCumulativeCost();
	}

	float f() {
		if (h = std::numeric_limits<float>::infinity()) {
			return h;
		}

		if (bestParent == nullptr) {
			return cost + h;
		}

		float f = getCumulativeCost() + h;
	}

	void updateHeuristic(int destX, int destY) {
		h = abs(x - destX) + abs(y - destY);
	}
};