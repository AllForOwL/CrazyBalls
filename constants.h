const float CNT_TIME_SPAWN_ENEMY_METEOR		= 3.0;
const float CNT_TIME_SPAWN_ENEMY_AIRPLANE	= 3.0;
const float CNT_TIME_UPDATE_SCENE	= 0.05;
const float CNT_TIME_SPAWN_BONUS	= 5.0;

const int CNT_NUMBER_COINS_ONE_LEVEL = 50;

const int CNT_SPEED_BULLET	= 20;
const int CNT_SPEED_STONE	= 8;

const int CNT_QUENTITY_LEVELS = 8;

const int CNT_TAG_BULLET_NORMAL = 1000;
const int CNT_TAG_ENEMY_WOUNDED	= 1001;

const int CNT_NUMBER_SPRITE_IN_DIZZY = 3;

const int CNT_COLS	=	2;
const int CNT_ROWS	=	4;
const int CNT_MAX_INDEX_POSITION = 29;

const int CNT_TIME_SHOT_STONE_ROCK_1	= 15;
const int CNT_TIME_SHOT_STONE_ROCK_2	= 14;
const int CNT_TIME_SHOT_STONE_ROCK_3	= 13;
const int CNT_TIME_SHOT_STONE_ROCK_4	= 12;
const int CNT_TIME_SHOT_STONE_ROCK_5	= 11;
const int CNT_TIME_SHOT_STONE_ROCK_6	= 10;
const int CNT_TIME_SHOT_STONE_ROCK_7	= 9;
const int CNT_TIME_SHOT_STONE_ROCK_8	= 8;
const int CNT_TIME_SHOT_STONE_ROCK_9	= 7;

const int CNT_TAG_BONUS_COIN			= 100;
const int CNT_TAG_BONUS_POWER			= 101;
const int CNT_TAG_BONUS_ARMOR			= 103;
const int CNT_TAG_BONUS_BULLET_SPEED	= 104;
const int CNT_TAG_BONUS_BULLET_QUENTITY = 105;

const std::string CNT_NAME_HERO_HELL		= "Hell";

const std::string CNT_NAME_BULLET_POSITION_TOP		= "Bullet_position_top";
const std::string CNT_NAME_BULLET_POSITION_BOTTOM	= "Bullet_position_bottom";
const std::string CNT_NAME_BULLET_BONUS			    = "Bullet bonus";

const std::string CNT_NAME_COINS			= "Coins";
const std::string CNT_NAME_CASKET_COINS		= "Casket_coins";
const std::string CNT_NAME_CASKET_POWERS	= "Casket_clothes";

const std::string CNT_NAME_BONUS_COIN				= "bonus_coin";
const std::string CNT_NAME_BONUS_POWER				= "bonus_power";
const std::string CNT_NAME_BONUS_ARMOR				= "bonus_armor";
const std::string CNT_NAME_BONUS_BULLET_SPEED		= "bonus_bullet_speed";
const std::string CNT_NAME_BONUS_BULLET_QUENTITY	= "bonus_bullet_quentity";

const std::string CNT_NAME_ENEMY_BLACK_1	= "black_1";
const std::string CNT_NAME_ENEMY_BLACK_2	= "black_2";
const std::string CNT_NAME_ENEMY_BLACK_3	= "black_3";
const std::string CNT_NAME_ENEMY_BLACK_4	= "black_4";
const std::string CNT_NAME_ENEMY_BLACK_5	= "black_5";

const std::string CNT_NAME_ENEMY_BLUE_1	= "blue_1";
const std::string CNT_NAME_ENEMY_BLUE_2 = "blue_2";
const std::string CNT_NAME_ENEMY_BLUE_3 = "blue_3";
const std::string CNT_NAME_ENEMY_BLUE_4 = "blue_4";
const std::string CNT_NAME_ENEMY_BLUE_5 = "blue_5";

const std::string CNT_NAME_ENEMY_GREEN_1 = "green_1";
const std::string CNT_NAME_ENEMY_GREEN_2 = "green_2";
const std::string CNT_NAME_ENEMY_GREEN_3 = "green_3";
const std::string CNT_NAME_ENEMY_GREEN_4 = "green_4";
const std::string CNT_NAME_ENEMY_GREEN_5 = "green_5";

const std::string CNT_NAME_ENEMY_RED_1 = "red_1";
const std::string CNT_NAME_ENEMY_RED_2 = "red_2";
const std::string CNT_NAME_ENEMY_RED_3 = "red_3";
const std::string CNT_NAME_ENEMY_RED_4 = "red_4";
const std::string CNT_NAME_ENEMY_RED_5 = "red_5";

const int CNT_ENEMY_HEALTH = 100;

#define HERO_COLLISION_BITMASK			0x000001
#define ENEMY_COLLISION_BITMASK			0x000002
#define BOT_BULLET_COLLISION_BITMASK	0x000003
#define SCENE_COLLISION_BITMASK			0x000004
#define BONUS_COLLISION_BITMASK			0x000005
#define HERO_BULLET_COLLISION_BITMASK	0x000006