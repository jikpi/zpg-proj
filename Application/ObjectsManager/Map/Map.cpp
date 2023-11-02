//
// Created by KOP0269 on 10/6/23.
//

#include "Map.h"

#include <utility>
#include <iostream>

Map::Map(std::string name) {
    this->Name = std::move(name);
    Lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
}

std::string Map::GetName() const {
    return Name;
}

void Map::InsertObject(const std::shared_ptr<StandardisedModel>& object) {
    Objects.push_back(object);
}

std::shared_ptr<StandardisedModel> & Map::GetObject(int index) {
    return Objects.at(index);
}

std::shared_ptr<StandardisedModel> &Map::GetObjectByName(const std::string &name) {
    for (auto &object: Objects) {
        if (object->Name() == name) {
            return object;
        }
    }

    std::cerr << "ERROR: Map: Object with name \"" << name << "\" not found." << std::endl;
    return Objects.at(0);
}

unsigned long Map::GetObjectCount() {
    return Objects.size();
}

void Map::InsertLight(const std::shared_ptr<Light> &light) {
    Lights->push_back(light);

}

unsigned long Map::GetLightCount() {
    return Lights->size();
}

std::shared_ptr<Light> &Map::GetLight(int index) {
    return Lights->at(index);
}

void Map::ChangeLight(int index, const std::shared_ptr<Light> &light) {
    Lights->at(index) = light;
}
