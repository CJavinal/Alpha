#include <DataTables.hpp>
#include <Aircraft.hpp>
#include <Projectile.hpp>
#include <ResourceIdentifiers.hpp>

std::vector<AircraftData> initializeAircraftData() {
	std::vector<AircraftData> data(Aircraft::TypeCount);
	
	data[Aircraft::Eagle].hitpoints = 100;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].texture = Textures::Eagle;

	data[Aircraft::Raptor].hitpoints = 20;
	data[Aircraft::Raptor].speed = 80.f;
	data[Aircraft::Raptor].texture = Textures::Raptor;
	data[Aircraft::Raptor].directions.push_back(Direction( 45,  80));
	data[Aircraft::Raptor].directions.push_back(Direction(-45, 160));
	data[Aircraft::Raptor].directions.push_back(Direction( 45,  80));

	data[Aircraft::Avenger].hitpoints = 10;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].directions.push_back(Direction(+45,  50));
	data[Aircraft::Avenger].directions.push_back(Direction(  0,  50));
	data[Aircraft::Avenger].directions.push_back(Direction(-45, 100));
	data[Aircraft::Avenger].directions.push_back(Direction(  0,  50));
	data[Aircraft::Avenger].directions.push_back(Direction(+45,  50));

	return data;
}


std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Bullet;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::Bullet;

	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Textures::Missile;

	return data;
}

