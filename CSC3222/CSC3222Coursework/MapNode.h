struct MapNode {
	MapNode* bestParent;

	int posX;
	int posY;

	float cost;
	float heuristic;

	bool traversable;
};