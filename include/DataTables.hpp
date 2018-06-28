#pragma once
#ifndef DataTables_HPP_INCLUDED
#define DataTables_HPP_INCLUDED
#include <ResourceIdentifiers.hpp>
#include <vector>

struct Direction {
				Direction(float angle, float distance)
					: angle(angle), distance(distance) { }
	float		angle;
	float		distance;
};

struct AircraftData {
	int							hitpoints;
	float						speed;
	Textures::ID				texture;
	std::vector<Direction>		directions;
};

std::vector<AircraftData> initializeAircraftData();



#endif // DataTables_HPP_INCLUDED
