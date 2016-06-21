#ifndef __OPHD_COMMON__
#define __OPHD_COMMON__



enum Direction
{
	DIR_UP,
	DIR_DOWN,
	DIR_EAST,
	DIR_WEST,
	DIR_NORTH,
	DIR_SOUTH
};


enum TerrainType
{
	TERRAIN_DOZED,
	TERRAIN_CLEAR,
	TERRAIN_ROUGH,
	TERRAIN_DIFFICULT,
	TERRAIN_IMPASSABLE
};


/**
* Connector Direction.
*/
enum ConnectorDir
{
	CONNECTOR_NONE,
	CONNECTOR_INTERSECTION,
	CONNECTOR_RIGHT,
	CONNECTOR_LEFT,
	CONNECTOR_VERTICAL			// Functions as an intersection
};


enum StructureID
{
	SID_NONE,
	SID_AGRIDOME,
	SID_AIR_SHAFT,
	SID_CHAP,
	SID_COMMAND_CENTER,
	SID_MINE_FACILITY,
	SID_SEED_FACTORY,
	SID_SEED_LANDER,
	SID_SEED_POWER,
	SID_SEED_SMELTER,
	SID_STORAGE_TANKS,
	SID_TUBE_INTERSECTION,
	SID_TUBE_RIGHT,
	SID_TUBE_LEFT
};


enum RobotType
{
	ROBOT_NONE,
	ROBOT_DIGGER,
	ROBOT_DOZER,
	ROBOT_MINER
};

#endif