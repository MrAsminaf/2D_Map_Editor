#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

template<typename T>
class Interface
{
public:
	virtual void DeleteTile() = 0;
	virtual void AddTile() = 0;
	virtual T GetTileAtCoords(int x, int y) = 0;
private:
	virtual void HighlightTile() = 0;
	virtual bool CheckIfTileExists(int x, int y) const = 0;
};