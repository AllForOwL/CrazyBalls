const float CNT_TIME_SPAWN			= 5.0;
const float CNT_TIME_UPDATE_SCENE	= 0.05;
const float CNT_TIME_SPAWN_BONUS	= 15.0;

const int CNT_NUMBER_COINS_ONE_LEVEL = 50;

const int CNT_SPEED_BULLET	= 50;
const int CNT_SPEED_STONE	= 8;

const int CNT_TAG_BULLET_NORMAL = 1000;
const int CNT_TAG_ENEMY_WOUNDED	= 1001;

const int CNT_NUMBER_SPRITE_IN_DIZZY = 3;

const int CNT_COLS	=	2;
const int CNT_ROWS	=	4;
const int CNT_MAX_INDEX_POSITION = 29;

const int CNT_TIME_SHOT_STONE_ROCK_1	= 20;
const int CNT_TIME_SHOT_STONE_ROCK_2	= 19;
const int CNT_TIME_SHOT_STONE_ROCK_3	= 18;
const int CNT_TIME_SHOT_STONE_ROCK_4	= 17;
const int CNT_TIME_SHOT_STONE_ROCK_5	= 16;
const int CNT_TIME_SHOT_STONE_ROCK_6	= 15;
const int CNT_TIME_SHOT_STONE_ROCK_7	= 14;
const int CNT_TIME_SHOT_STONE_ROCK_8	= 13;
const int CNT_TIME_SHOT_STONE_ROCK_9	= 12;

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

const int CNT_TYPE_OBJECT_RANDOM						= 0;
const int CNT_TYPE_OBJECT_CASKET_COINS					= 1;
const int CNT_TYPE_OBJECT_CASKET_POWER					= 2;
const int CNT_TYPE_OBJECT_WEAPON_AK47					= 3;
const int CNT_TYPE_OBJECT_WEAPON_GUN					= 4;
const int CNT_TYPE_OBJECT_WEAPON_MI71					= 5;
const int CNT_TYPE_OBJECT_WEAPON_MK15					= 6;
const int CNT_TYPE_OBJECT_WEAPON_REVOLVER_MONI_SHADE	= 7;
const int CNT_TYPE_OBJECT_WEAPON_STEN_GUN_SHADE_2		= 8;
const int CNT_TYPE_OBJECT_WEAPON_TS23					= 9;
const int CNT_TYPE_OBJECT_WEAPON_UMG					= 10;
const int CNT_TYPE_OBJECT_BULLET_NORMAL					= 11;
const int CNT_TYPE_OBJECT_BULLET_BOMB					= 12;


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

const std::string CNT_NAME_COINS			= "Coins";
const std::string CNT_NAME_CASKET_COINS		= "Casket_coins";
const std::string CNT_NAME_CASKET_POWERS	= "Casket_clothes";

#define HERO_COLLISION_BITMASK		0x000001
#define ENEMY_COLLISION_BITMASK		0x000002
#define BULLET_COLLISION_BITMASK	0x000003
#define SCENE_COLLISION_BITMASK		0x000004
#define BONUS_COLLISION_BITMASK		0x000005