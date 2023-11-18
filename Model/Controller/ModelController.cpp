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
#include "../../Application/Configuration/AGlobalConfig.h"

ModelController::ModelData ModelController::LoadModel(const std::string &path) {
    std::cout << "Loading model: " << path << std::endl;

    std::vector<float> completeData;
    Assimp::Importer importer;
    unsigned int options = aiProcess_Triangulate
                           | aiProcess_OptimizeMeshes
                           | aiProcess_JoinIdenticalVertices
                           | aiProcess_CalcTangentSpace;

    const aiScene *scene = importer.ReadFile(path, options);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error("ModelController::LoadModel: Error: " + std::string(importer.GetErrorString()));
    }

    ModelData modelData;
    modelData.Type = static_cast<ModelStamp>(0);

    std::vector<std::vector<float>> meshData;

    //Load all meshes
    for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
        aiMesh *mesh = scene->mMeshes[m];

        modelData.Type = static_cast<ModelStamp>(modelData.Type | ModelStamp::MODEL_STAMP_VERTICES);

        if (mesh->HasNormals()) {
            modelData.Type = static_cast<ModelStamp>(modelData.Type | ModelStamp::MODEL_STAMP_NORMALS);
        }
        if (mesh->HasTextureCoords(0)) {
            modelData.Type = static_cast<ModelStamp>(modelData.Type | ModelStamp::MODEL_STAMP_TEXTURE_COORDS);
        }

        meshData.emplace_back();

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                unsigned int id = face.mIndices[j];

                // Vertex position
                aiVector3D pos = mesh->mVertices[id];
                meshData[m].push_back(pos.x);
                meshData[m].push_back(pos.y);
                meshData[m].push_back(pos.z);

                // Vertex normal
                if (mesh->HasNormals()) {
                    aiVector3D nor = mesh->mNormals[id];
                    meshData[m].push_back(nor.x);
                    meshData[m].push_back(nor.y);
                    meshData[m].push_back(nor.z);
                }

                // Vertex texture coordinates
                if (mesh->HasTextureCoords(0)) {
                    aiVector3D tex = mesh->mTextureCoords[0][id];
                    meshData[m].push_back(tex.x);
                    meshData[m].push_back(tex.y);
                }
            }
        }
    }


    ////Load material
    modelData.HasMaterial = false;
    if (scene->mNumMaterials > 0) {
        aiMaterial *mat = scene->mMaterials[0];

        aiString matName;
        mat->Get(AI_MATKEY_NAME, matName);
        if (std::string(matName.C_Str()) == AI_DEFAULT_MATERIAL_NAME) {
            goto no_material;
        }

        aiColor3D ambient(0.f, 0.f, 0.f);
        aiColor3D diffuse(0.f, 0.f, 0.f);
        aiColor3D specular(0.f, 0.f, 0.f);
        float shininess = 0.0f;

        mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
        mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
        mat->Get(AI_MATKEY_SHININESS, shininess);

        modelData.material = Material(
                glm::vec3(ambient.r, ambient.g, ambient.b),
                glm::vec3(diffuse.r, diffuse.g, diffuse.b),
                glm::vec3(specular.r, specular.g, specular.b),
                shininess
        );

        modelData.HasMaterial = true;
    }
    no_material:

    //Merge all meshes
    for (auto &mesh: meshData) {
        completeData.insert(completeData.end(), mesh.begin(), mesh.end());
    }

    modelData.Data = std::move(completeData);
    return modelData;
}


std::shared_ptr<StandardisedModel>
ModelController::RetrieveModel(const std::string &path, ModelStamp type, const std::string &Name, bool anyType,
                               bool standardPath) {

    std::string fullPath;
    if (standardPath) {
        fullPath = DEF_PATH_MODELS + path;
    } else {
        fullPath = path;
    }

    if (ModelsData.find(fullPath) == ModelsData.end()) {
        ModelsData[fullPath] = LoadModel(fullPath);
    }

    ModelData &mData = ModelsData[fullPath];

    if (!anyType && mData.Type != type) {
        std::cerr << "ModelController::RetrieveModel: Warning: Model type mismatch, overriding." << std::endl;
    }

    std::shared_ptr<StandardisedModel> model;

    if ((mData.Type & ModelStamp::MODEL_STAMP_VERTICES) &&
        (mData.Type & ModelStamp::MODEL_STAMP_NORMALS) &&
        (mData.Type & ModelStamp::MODEL_STAMP_TEXTURE_COORDS)) {

        model = ModelFactory::AssimpPositionNormalTex(mData.Data, Name);
    } else if ((mData.Type & ModelStamp::MODEL_STAMP_VERTICES) &&
               (mData.Type & ModelStamp::MODEL_STAMP_NORMALS)) {

        model = ModelFactory::AssimpPositionNormal(mData.Data, Name);
    } else if (mData.Type & ModelStamp::MODEL_STAMP_VERTICES) {

        model = ModelFactory::AssimpPosition(mData.Data, Name);
    } else {
        throw std::runtime_error("ModelController::RetrieveModel: Error: Model type not found");
    }


    if (mData.HasMaterial) {
        model->SetMaterial(mData.material);
    }

    return model;
}

std::shared_ptr<StandardisedModel>
ModelController::UsePositionNormalTex(const std::string &path, const std::string &Name, bool standardPath) {
    return RetrieveModel(path,
                         static_cast<ModelStamp>(
                                 ModelStamp::MODEL_STAMP_VERTICES |
                                 ModelStamp::MODEL_STAMP_NORMALS |
                                 ModelStamp::MODEL_STAMP_TEXTURE_COORDS),
                         Name, false,
                         standardPath);
}

std::shared_ptr<StandardisedModel>
ModelController::UsePositionNormal(const std::string &path, const std::string &Name, bool standardPath) {
    return RetrieveModel(path, static_cast<ModelStamp>(
            ModelStamp::MODEL_STAMP_VERTICES |
            ModelStamp::MODEL_STAMP_NORMALS), Name, false, standardPath);
}

std::shared_ptr<StandardisedModel>
ModelController::UsePosition(const std::string &path, const std::string &Name, bool standardPath) {
    return RetrieveModel(path, static_cast<ModelStamp>(
            ModelStamp::MODEL_STAMP_VERTICES), Name, false, standardPath);
}

std::shared_ptr<StandardisedModel>
ModelController::UseAny(const std::string &path, const std::string &Name, bool standardPath) {
    return RetrieveModel(path, static_cast<ModelStamp>(0), Name, true,
                         standardPath);
}




