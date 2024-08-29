#include <fstream>
#include <sstream>
#include "../include/Map.h"
#include "../include/AssetManager.h"
#include "../include/ECS/EntityComponentSystem.h"
#include "../include/ECS/Components.h"

extern Manager g_Manager;

Map::Map(const std::string p_TextureID, int p_MapScale, int p_TileSize)
    : m_TextureID(p_TextureID), m_MapScale(p_MapScale), m_TileSize(p_TileSize) {
    m_ScaledSize = p_MapScale * p_TileSize;
}

Map::~Map() {}

void Map::LoadMap(const std::string p_Path, int p_SizeX, int p_SizeY, int p_SSTilePerRow) {
    // Open the map file
    std::ifstream mapFile(p_Path);
    if (!mapFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Read the entire file content into a string
    std::string content((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
    mapFile.close();

    // Find the position of the separator (empty line) between tile map and collider map
    size_t separatorPos = content.find("\n\n");
    if (separatorPos == std::string::npos) {
        std::cerr << "Error: No separator found between tile map and collider map." << std::endl;
        return;
    }

    // Extract the tile map content and collider map content
    std::string tileMapContent = content.substr(0, separatorPos);
    std::string colliderMapContent = content.substr(separatorPos + 2);

    // Parse the tile map
    std::istringstream tileMapStream(tileMapContent);
    mapData.resize(p_SizeY, std::vector<int>(p_SizeX, 0));
    std::string line;
    int y = 0;

    // Read each line of the tile map
    while (std::getline(tileMapStream, line) && y < p_SizeY) {
        std::stringstream ss(line);
        std::string cell;
        int x = 0;

        // Read each cell in the line
        while (std::getline(ss, cell, ',')) {
            if (x < p_SizeX) {
                mapData[y][x] = std::stoi(cell); // Convert cell to integer and store in mapData
                x++;
            }
        }
        y++;
    }

    // Parse the collider map
    std::istringstream colliderMapStream(colliderMapContent);
    std::vector<std::vector<int>> colliderData(p_SizeY, std::vector<int>(p_SizeX, 0));
    y = 0;

    // Read each line of the collider map
    while (std::getline(colliderMapStream, line) && y < p_SizeY) {
        std::stringstream ss(line);
        std::string cell;
        int x = 0;

        // Read each cell in the line
        while (std::getline(ss, cell, ',')) {
            if (x < p_SizeX) {
                colliderData[y][x] = std::stoi(cell); // Convert cell to integer and store in colliderData
                x++;
            }
        }
        y++;
    }

    // Add tiles based on the tile map
    for (int y = 0; y < p_SizeY; y++) {
        for (int x = 0; x < p_SizeX; x++) {
            int tileValue = mapData[y][x];
            int srcX = (tileValue % p_SSTilePerRow) * m_TileSize;
            int srcY = (tileValue / p_SSTilePerRow) * m_TileSize;
            AddTile(srcX, srcY, x * m_ScaledSize, y * m_ScaledSize);
        }
    }

    // Add colliders based on the collider map
    for (int y = 0; y < p_SizeY; y++) {
        for (int x = 0; x < p_SizeX; x++) {
            if (colliderData[y][x] == 1) {
                auto& tileCollider(g_Manager.AddEntity());
                tileCollider.AddComponent<ColliderComponent>("mapColliders", x * m_ScaledSize, y * m_ScaledSize, m_ScaledSize);
                tileCollider.GetComponent<ColliderComponent>().m_drawCollider = false;
                tileCollider.AddGroup(AssetManager::groupColliders);
            }
        }
    }
}

void Map::AddTile(int p_SrcX, int p_SrcY, int p_XPos, int p_YPos) {
    auto& tile(g_Manager.AddEntity());
    tile.AddComponent<TileComponent>(p_SrcX, p_SrcY, p_XPos, p_YPos, m_TileSize, m_MapScale, m_TextureID);
    tile.AddGroup(AssetManager::groupTiles);
}