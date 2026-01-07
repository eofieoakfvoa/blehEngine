#include "AssetLoader.h"
#include "vendors/nlohmann/json.hpp"
#include <print>
#include <iostream>
#include <fstream>
#include <Services/Model.h>
using json = nlohmann::json;
// viktigast först är att få gltf filer att loada sen glb sen andra typer av filer
// ignora nodes / scenes
Mesh AssetLoader::LoadAsset(const std::string &filePath) //mer som createmesh 
{
    std::ifstream gltfFile(filePath);
    json gltfData = json::parse(gltfFile);
    Mesh newMesh;
    //tror detta må va den värsta koden jag skrivit, de måsta finnas 100 improvements att göra

    for (auto &[key, value] : gltfData["buffers"].items()) // just nu tar den hela bin filen, tror den bara ska ta till längden lol anywhos som mr spear hade sagt
    {
        std::string uriPath = value["uri"].get<std::string>();
        std::string reallytemporaryPath = ResourcePath "temp/" + uriPath;
        std::ifstream uri(reallytemporaryPath, std::ios::in | std::ios::binary); // https://stackoverflow.com/questions/24716250/c-store-read-binary-file-into-buffer
        Buffer tempBuffer;
        int length = value["byteLength"].get<int>();
        tempBuffer.Data.resize(length);
        uri.read(tempBuffer.Data.data(), length);
        newMesh.AddBuffer(tempBuffer);
    }
    for (auto &[key, value] : gltfData["bufferViews"].items())
    {

        BufferView tempbufferview(
            value.value("buffer", -1),
            value.value("byteLength", -1),
            value.value("byteOffset", 0),
            value.value("byteStride", -1),
            value.value("target", -1));

        newMesh.AddBufferView(tempbufferview);
    }
    for (auto &[key, value] : gltfData["accessors"].items())
    {


        Accessor tempaccessor(
            value.value("bufferView", -1),
            value.value("byteOffset", 0),
            value.value("componentType", -1),
            value.value("count", -1),
            value["type"].get<std::string>());
        newMesh.AddAccessor(tempaccessor);
    }
    return newMesh;


// std::println("{}", gltfData.dump(4));
}