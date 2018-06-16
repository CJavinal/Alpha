#ifndef Category_HPP_INCLUDED
#define Category_HPP_INCLUDED

namespace Category {
	enum Type {
		None			= 0,
		Scene			= 1 << 0,
		PlayerAircraft	= 1 << 1,
		AlliedAircraft	= 1 << 2,
		EnemyAircraft	= 1 << 3,
	};
}



#endif // Category_HPP_INCLUDED
