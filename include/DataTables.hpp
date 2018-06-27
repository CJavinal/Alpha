#pragma once
#ifndef DataTables_HPP_INCLUDED
#define DataTables_HPP_INCLUDED
#include <ResourceIdentifiers.hpp>
#include <vector>


struct AircraftData {
	int					hitpoints;
	float				speed;
	Textures::ID		texture;
};

std::vector<AircraftData> initializeAircraftData();



#endif // DataTables_HPP_INCLUDED
