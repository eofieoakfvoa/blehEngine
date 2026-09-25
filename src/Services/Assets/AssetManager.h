#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <string>
#include <iostream>
#include "Services/blehServices.h"
#include "Services/Assets/handle.h"
#include "renderer/Texture.h"
namespace bleh
{
	class AssetManager
	{
		private:

			//inte fan av detta 
			std::unordered_map<uint64_t, std::shared_ptr<Mesh>> _AssetManager;
			std::unordered_map<uint64_t, std::shared_ptr<Texture>> _TextureManager;
			std::unordered_map<uint64_t, std::shared_ptr<gltf::Material>> _MaterialManager;
			
			
			
			//std::unordered_map<> TextureManager;
			blehServices* _blehservices;
			void _GenerateUUID();
			std::shared_ptr<Mesh> _GetAssetInformationGLTF(std::filesystem::path);

		public:	
			void AddToRenderQueue(uint64_t key);
			blehHandle LoadMesh(std::filesystem::path MeshPath); 
			blehHandle LoadImage(const std::filesystem::path& filepath);
			void setBlehServices(blehServices&); //fixa
			void SetTextureActive(uint64_t key, int slot);
	};
}

