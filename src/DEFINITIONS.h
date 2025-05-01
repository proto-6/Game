#pragma once
#include <memory>
#define SPLASHstate_SHOW_TIME 3.0f
#define TILE_SIZE 16
#define SCREEN_WIDTH 1920.f
#define SCREEN_HEIGHT 1080.f
#define NEGATIVE_BORDER_X -960
#define POSITIVE_BORDER_X 960
#define NEGATIVE_BORDER_Y -512
#define POSITIVE_BORDER_Y 512
#define CHARACTER_WIDTH 16 // In pixels
#define CHARACTER_HEIGHT 21 // In pixels *note in file height is 28 but upper 7 pixels are empty all time


namespace Font
{
	enum Type
	{
		PixeloidSans
	};
	
}

namespace Texture
{
	enum Type
	{
		Blue_Flame,
		MainMenu_Background,
		GameMenu_Background,
		CharacterIdle0,
		CharacterIdle1,
		CharacterIdle2,
		CharacterIdle3,
		CharacterRun0,
		CharacterRun1,
		CharacterRun2,
		CharacterRun3,
		EnemyIdle0,
		EnemyIdle1,
		EnemyIdle2,
		EnemyIdle3,
		EnemyRun0,
		EnemyRun1,
		EnemyRun2,
		EnemyRun3,
	};
}


namespace ButtonName
{
	enum Type
	{
		Play, Exit, Alright, None
	};
}

