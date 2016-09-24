const float CNT_TIME_SPAWN			= 4.0;
const float CNT_TIME_UPDATE_SCENE	= 0.05;

const int CNT_SPEED_BULLET	= 8;

const int CNT_TAG_BULLET_NORMAL = 1000;
const int CNT_TAG_ENEMY_WOUNDED	= 1001;

const int CNT_COLS	=	5;
const int CNT_ROWS	=	6;
const int CNT_MAX_INDEX_POSITION = 29;

const std::string CNT_NAME_HERO_HELL		= "Hell";

const std::string CNT_NAME_ENEMY_ROCK_1	= "Rock1";
const std::string CNT_NAME_ENEMY_ROCK_2 = "Rock2";
const std::string CNT_NAME_ENEMY_ROCK_3 = "Rock3";
const std::string CNT_NAME_ENEMY_ROCK_4 = "Rock4";
const std::string CNT_NAME_ENEMY_ROCK_5 = "Rock5";
const std::string CNT_NAME_ENEMY_ROCK_6 = "Rock6";
const std::string CNT_NAME_ENEMY_ROCK_7 = "Rock7";
const std::string CNT_NAME_ENEMY_ROCK_8 = "Rock8";
const std::string CNT_NAME_ENEMY_ROCK_9 = "Rock9";

const std::string CNT_NAME_WEAPON_AK47					= "AK-47";
const std::string CNT_NAME_WEAPON_GUN					= "Gun";
const std::string CNT_NAME_WEAPON_MI71					= "MI-71";
const std::string CNT_NAME_WEAPON_MK15					= "MK-15";
const std::string CNT_NAME_WEAPON_REVOLVER_MONI_SHADE	= "Revolver_moni_shade";
const std::string CNT_NAME_WEAPON_STEN_GUN_SHADE_2		= "Sten_gun_shade_2";
const std::string CNT_NAME_WEAPON_TS23					= "TS-23";
const std::string CNT_NAME_WEAPON_UMG					= "UMG";

const std::string CNT_NAME_BULLET_DEFAULT	= "Bullet_normal";
const std::string CNT_NAME_BOMB				= "Bomd";

#define HERO_COLLISION_BITMASK		0x000001
#define ENEMY_COLLISION_BITMASK		0x000002
#define BULLET_COLLISION_BITMASK	0x000003
#define SCENE_COLLISION_BITMASK		0x000004
