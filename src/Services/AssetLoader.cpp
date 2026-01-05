#include "AssetLoader.h"
#include "vendors/nlohmann/json.hpp"
#include <print>
#include <iostream>
#include <fstream>
using json = nlohmann::json;
//viktigast först är att få gltf filer att loada sen glb sen andra typer av filer
void AssetLoader::LoadAsset(const std::string &filePath)
{
    std::ifstream gltfFile(filePath);
    json gltfData = json::parse(gltfFile);

    //std::println("{}", gltfData.dump(4));
}