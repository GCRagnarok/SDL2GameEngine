#pragma once
#include <string>
#include <vector>

class Map {
public:
    Map(const std::string p_TextureID, int p_MapScale, int p_TileSize);
    ~Map();

    void LoadMap(const std::string p_Path, int p_SizeX, int p_SizeY, int p_SSTilePerRow);
    void AddTile(int p_SrcX, int p_SrcY, int p_XPos, int p_YPos);

private:
    std::string m_TextureID;
    int m_MapScale;
    int m_TileSize;
    int m_ScaledSize;
    std::vector<std::vector<int>> mapData;
};
