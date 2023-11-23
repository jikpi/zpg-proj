//
// Created by KOP0269 on 10/20/23.
//

#ifndef ZPG_TEST_MAPTOSHADERLINKER_H
#define ZPG_TEST_MAPTOSHADERLINKER_H


#include <vector>
#include <memory>
#include "ShaderObjectSet/ShaderObjectSet.h"
#include "../Map/Map.h"

class MapToShaderLinker {
private:
    std::vector<std::shared_ptr<ShaderObjectSet>> ShaderObjectSets;
    void AddShader(ShaderHandler *shader);

    std::weak_ptr<ShaderHandler> FallbackShader;
    bool TryUseFallbackShader();

    void AddObjectToShader(ShaderHandler *shader, const std::shared_ptr<StandardisedModel> &object);
    void AddObjectToShaderWithName(const std::string& name, std::shared_ptr<StandardisedModel> &object);

    static void PrintBuildingObjectError(const std::shared_ptr<StandardisedModel> &object);

    void LinkLightsToShader(std::shared_ptr<ShaderHandler> &shader, const std::shared_ptr<Map> &map);
    unsigned short NextContextID{};
    unsigned short GetNextContextID();
public:
    MapToShaderLinker();
    void SetFallbackShader(std::shared_ptr<ShaderHandler> &shader);

    std::vector<std::shared_ptr<ShaderObjectSet>>::iterator begin() { return ShaderObjectSets.begin(); }
    std::vector<std::shared_ptr<ShaderObjectSet>>::iterator end() { return ShaderObjectSets.end(); }

    void BuildWithMap(const std::shared_ptr<Map> &map);
    void BuildWithMapSingleObject(const std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object);

    void NotifyLightsOnCurrentMapChanged();
};


#endif //ZPG_TEST_MAPTOSHADERLINKER_H
