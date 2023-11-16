//
// Created by lvi on 11/16/23.
//

#include <stdexcept>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include <iostream>

#include "ModelController.h"
#include "../Factory/ModelFactory.h"

ModelController::ModelData ModelController::LoadModel(const std::string &path) {
    std::vector<float> data;
    unsigned int count = 0;

    Assimp::Importer importer;
    unsigned int options = aiProcess_Triangulate
                           | aiProcess_OptimizeMeshes
                           | aiProcess_JoinIdenticalVertices
                           | aiProcess_CalcTangentSpace;

    const aiScene *scene = importer.ReadFile(path, options);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("ModelController::LoadModel: Error: " + std::string(importer.GetErrorString()));
    }

    aiMesh *mesh = scene->mMeshes[0];
    count = mesh->mNumFaces * 3;

    ModelData modelData;

    if (mesh->HasNormals() && mesh->HasTextureCoords(0)) {
        modelData.Type = ModelType::PositionNormalTex;
    } else if (mesh->HasNormals()) {
        modelData.Type = ModelType::PositionNormal;
    } else {
        modelData.Type = ModelType::Position;
    }


    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < 3; j++) {
            unsigned int id = face.mIndices[j];

            // Vertex position
            aiVector3D pos = mesh->mVertices[id];
            data.push_back(pos.x);
            data.push_back(pos.y);
            data.push_back(pos.z);

            // Vertex normal
            if (mesh->HasNormals()) {
                aiVector3D nor = mesh->mNormals[id];
                data.push_back(nor.x);
                data.push_back(nor.y);
                data.push_back(nor.z);
            }

            // Vertex texture coordinates
            if (mesh->HasTextureCoords(0)) {
                aiVector3D tex = mesh->mTextureCoords[0][id];
                data.push_back(tex.x);
                data.push_back(tex.y);
            }
        }
    }

    modelData.Data = std::move(data);
    return modelData;
}


std::shared_ptr<StandardisedModel>
ModelController::RetrieveModel(const std::string &path, ModelController::ModelType type, const std::string &Name,
                               bool exists) {

    if (ModelsData.find(path) == ModelsData.end()) {
        if (exists)
            throw std::runtime_error("ModelController::RetrieveModel: Debug: Model does not exist");
        ModelsData[path] = LoadModel(path);
    }

    ModelData &mData = ModelsData[path];

    if (type != Any && mData.Type != type) {
        std::cerr << "ModelController::RetrieveModel: Warning: Model type mismatch, overriding." << std::endl;
    }

    switch (mData.Type) {
        case ModelType::PositionNormalTex:
            return ModelFactory::AssimpPositionNormalTex(mData.Data, Name);
        case ModelType::PositionNormal:
            return ModelFactory::AssimpPositionNormal(mData.Data, Name);
        case ModelType::Position:
            return ModelFactory::AssimpPosition(mData.Data, Name);

        case Any:
            break;
    }

    throw std::runtime_error("ModelController::RetrieveModel: Error: Model type not found");
}

std::shared_ptr<StandardisedModel>
ModelController::UsePositionNormalTex(const std::string &path, const std::string &Name) {
    std::shared_ptr<StandardisedModel> model = RetrieveModel(path, ModelType::PositionNormalTex, Name, false);
    return model;
}

std::shared_ptr<StandardisedModel>
ModelController::UsePositionNormal(const std::string &path, const std::string &Name) {
    std::shared_ptr<StandardisedModel> model = RetrieveModel(path, ModelType::PositionNormal, Name, false);
    return model;
}

std::shared_ptr<StandardisedModel> ModelController::UsePosition(const std::string &path, const std::string &Name) {
    std::shared_ptr<StandardisedModel> model = RetrieveModel(path, ModelType::Position, Name, false);
    return model;
}

std::shared_ptr<StandardisedModel> ModelController::UseAny(const std::string &path, const std::string &Name) {
    std::shared_ptr<StandardisedModel> model = RetrieveModel(path, ModelType::Any, Name, true);
    return model;
}




