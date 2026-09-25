#include "blehGame.h"
namespace bleh
{
	blehGame::blehGame()
	{
		_AssetManager = std::make_shared<AssetManager>();
	}
	void blehGame::setBlehServices(blehServices& blehservices)
	{
		_blehservices = &blehservices;
	}
}
