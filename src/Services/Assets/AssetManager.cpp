#include "AssetManager.h"

#include <print>
#include <memory>
#include <iostream>
#include <fstream>
#include <Services/Assets/Model.h>
#include <filesystem>


#include "Random.h"
#include "stb_image.h"
#include "debug.h"
#include "nlohmann/json.hpp"


using json = nlohmann::json;
namespace bleh
{
	blehHandle AssetManager::LoadMesh(std::filesystem::path MeshPath)
	{
		std::string FileType = MeshPath.extension().string();
		std::println("MESH: START: Loading mesh from path: {}, extension: {}", MeshPath.string(), FileType);
		if (FileType == ".gltf")
		{

			std::shared_ptr<Mesh> newmesh = _GetAssetInformationGLTF(MeshPath);
			
            newmesh->CreateVertexArray();
			if (newmesh->GetMaterials().size() != 0)
			{
				std::println("yo");
				//bleh::debug::Timer timer;
				for (gltf::Primative& meshParts : newmesh->meshParts)
				{
					int MaterialID = meshParts.Material;
					gltf::Material material = newmesh->GetMaterials()[MaterialID];

					std::filesystem::path imagepath = newmesh->GetImages()[material.PBR.baseColorTexture].URI;
					std::string stringpath = (newmesh->filepath / imagepath).string();
					meshParts.TextureHandle = LoadImage(stringpath);

				}
				std::println("BaseTexture UUID = {} ", newmesh->BaseTexture.UUID);
			}
			newmesh->handle.UUID = bleh::Random::RandomInt64();
			
			
			std::println("MESH: COMPLETE: mesh uuid = {}", newmesh->handle.UUID);
            std::println();
            _AssetManager[newmesh->handle.UUID] = newmesh;
			return newmesh->handle;
		}


		std::println("MESH FUCKED UP");
		return blehHandle{};

	}

	blehHandle AssetManager::LoadImage(const std::filesystem::path& filepath)
	{
		//Fixa så att bleh kan ladda in .png filer med GL_RGBA :P
		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
		//stbi_set_flip_vertically_on_load(true);

		std::string stringFilePath = filepath.string();
		std::println("loading image Filepath = {}", filepath.string());
		unsigned char* data = stbi_load(stringFilePath.c_str(), &newTexture->Width, &newTexture->Height, &newTexture->nrChannels, 0);
		if (!data)
		{
			std::cerr << "Failed to load texture: " << stbi_failure_reason() << std::endl;
			std::cout << "Failed to load texture" << std::endl;
			return blehHandle{};
		}
		GLenum format = newTexture->nrChannels == 4 ? GL_RGBA :
			newTexture->nrChannels == 3 ? GL_RGB :
			newTexture->nrChannels == 1 ? GL_RED : 0;

		glCreateTextures(GL_TEXTURE_2D, 1, &newTexture->_RenderID);

		glTextureStorage2D(newTexture->_RenderID, 1, (format == GL_RGBA ? GL_RGBA8 : GL_RGB8), newTexture->Width, newTexture->Height);
		glTextureSubImage2D(newTexture->_RenderID, 0, 0, 0, newTexture->Width, newTexture->Height, format, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(newTexture->_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(newTexture->_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(newTexture->_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(newTexture->_RenderID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateTextureMipmap(newTexture->_RenderID);

		stbi_image_free(data);
		newTexture->Handle.UUID = bleh::Random::RandomInt64();
		_TextureManager[newTexture->Handle.UUID] = newTexture;
		return newTexture->Handle;
	}


	void AssetManager::AddToRenderQueue(uint64_t key)
	{
		std::shared_ptr<Mesh> newmesh = _AssetManager[key];
		_blehservices->GetRenderer().AddMesh(newmesh);
	}


	void AssetManager::setBlehServices(blehServices& blehservices)
	{
		_blehservices = &blehservices;
	}



	void AssetManager::SetTextureActive(uint64_t key, int slot) //ideally ska den kolla i material istället för att få sin slot som är som shaderlayout fast för textures / bara fixa denna temporära kod
	{
		std::weak_ptr<Texture> temptexture = _TextureManager[key];
		if (std::shared_ptr<Texture> instance = temptexture.lock())
		{
			instance->SetActive(slot);
		}
		
	}



    std::shared_ptr<Mesh> AssetManager::_GetAssetInformationGLTF(std::filesystem::path filePath) // mer som createmesh
    {
        bleh::Benchmark::Timer timer;
        std::println("Loading Asset Start");
        std::ifstream gltfFile(filePath.string());
        json gltfData = json::parse(gltfFile);
        std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>();
        newMesh->filepath = filePath.parent_path();

        // tror detta må va den värsta koden jag skrivit, de måsta finnas 100 improvements att göra
        // det viktiga är att det fungerar - jag i framtiden, behöver fixa allt senare

        for (auto& [key, value] : gltfData["buffers"].items()) // just nu tar den hela bin filen, tror den bara ska ta till längden lol anywhos som mr spear hade sagt
        {

            std::string uriPath = value["uri"].get<std::string>();
            std::filesystem::path binPath = filePath.parent_path() / uriPath;
            std::ifstream uri(binPath, std::ios::in | std::ios::binary); // https://stackoverflow.com/questions/24716250/c-store-read-binary-file-into-buffer

            gltf::Buffer tempBuffer;
            int length = value["byteLength"].get<int>();
            tempBuffer.Data.resize(length);
            uri.read(tempBuffer.Data.data(), length);
            newMesh->AddBuffer(tempBuffer);
        }

        for (auto& [key, value] : gltfData["bufferViews"].items())
        {

            gltf::BufferView tempbufferview(
                value.value("buffer", -1),
                value.value("byteLength", -1),
                value.value("byteOffset", 0),
                value.value("byteStride", -1),
                value.value("target", -1));

            newMesh->AddBufferView(tempbufferview);
        }

        for (auto& [key, value] : gltfData["accessors"].items())
        {

            gltf::Accessor tempaccessor(
                value.value("bufferView", -1),
                value.value("byteOffset", 0),
                value.value("componentType", -1),
                value.value("count", -1),
                value["type"].get<std::string>());

            newMesh->AddAccessor(tempaccessor);
        }

        newMesh->meshParts.reserve(gltfData["meshes"].size());
        for (auto& [key, value] : gltfData["meshes"].items())
        {
            gltf::Primative tempPrimative;
            tempPrimative.Name = value.value("name", "bleh");

            for (auto& [key, value] : value["primitives"].items())
            {
                tempPrimative.Mode = value.value("mode", 4);
                tempPrimative.IndicesIndex = value.value("indices", -1);
                tempPrimative.Material = value.value("material", -1);
    
                for (auto& [key, value] : value["attributes"].items())
                {

                    std::println("key = {}", key);
                    if (key == "POSITION") //XDDDDDD
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::Position] = value.get<int>();
                        continue;
                    };
                    if (key == "NORMAL")
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::Normal] = value.get<int>();
                        continue;
                    };
                    if (key == "TANGENT")
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::Tangent] = value.get<int>();
                        continue;
                    };
                    if (key == "TEXCOORD_0")
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::TextCoord_0] = value.get<int>();
                        continue;
                    };
                    if (key == "TEXCOORD_1")
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::TextCoord_1] = value.get<int>();
                        continue;
                    };
                    if (key == "TEXCOORD_2")
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::TextCoord_2] = value.get<int>();
                        continue;
                    };
                    if (key == "TEXCOORD_3")
                    {
                        tempPrimative.attributes[gltf::ShaderLayout::TextCoord_3] = value.get<int>();
                        continue;
                    };

                }
                //std::println("POSITION accessor {}", tempPrimative.attributes[ShaderLayout::Position]);
                //std::println("NORMAL accessor {}", tempPrimative.attributes[ShaderLayout::Normal]);
                //std::println("TEX accessor {}", tempPrimative.attributes[ShaderLayout::TextCoord_0]);
                newMesh->AddMeshPart(tempPrimative);

            }

        }

        //Image Loading ska basically just nu bara vara att den tar information sen på samma sätt som CreateVertexArray fungerar så ska det här också.
        //alltså den loadar images efter

        for (auto& [key, value] : gltfData["images"].items())
        {
            gltf::Image tempImage;
            tempImage.URI = value["uri"].get<std::filesystem::path>();


            newMesh->AddImage(tempImage);
        }


        for (auto& [key, value] : gltfData["materials"].items())
        {
            //varje material kan nu använda loadimage för att skapa en texture
            if (value["pbrMetallicRoughness"]["baseColorTexture"].contains("index"))
            {
                std::println("Hello I have texture: {}", value["pbrMetallicRoughness"]["baseColorTexture"].value("index", -1));
                gltf::Material tempMaterial;
                tempMaterial.doubleSided = value.value("doubleSided", 0);
                tempMaterial.Name = value.value("name", "bleh");
                tempMaterial.PBR.baseColorTexture = value["pbrMetallicRoughness"]["baseColorTexture"].value("index", -1);
                newMesh->AddMaterial(tempMaterial);
            }
        }
        //materials har handle till image
        for (auto& [key, value] : gltfData["samplers"].items())
        {
            //idk finns ju en ganska liten mängd av samplers det kan vara
        }
        for (auto& [key, value] : gltfData["textures"].items())
        {
            //idk finns ju en ganska liten mängd av samplers det kan vara
        }



        //for (auto& [key, value] : gltfData["meshes"][0]["primitives"].items()) // gud
        //{

        //}



        std::println("Loading Asset End");

        return newMesh;

    }
}
