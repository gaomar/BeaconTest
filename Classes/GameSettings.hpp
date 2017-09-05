//
//  GameSettings.hpp
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#ifndef GameSettings_hpp
#define GameSettings_hpp

#include "cocos2d.h"
#include "GameDataDM.hpp"
USING_NS_CC;
#define GS GameSettings::sharedSettings()

class GameSettings;

using GameSettingsCallback = std::function<void (const bool &)>;

class GameSettings {
public:
    ~GameSettings();
    GameSettings();
    static GameSettings* sharedSettings(void);
    
    void writeLocalData(GameSettingsCallback callback);
private:
    CC_SYNTHESIZE(GameDataDM*, _gameDataDM, GameDataDM);
    CC_SYNTHESIZE(ValueMap, _localData, LocalData);
    
    // UUID
    CC_PROPERTY(std::string, _uuID, UUID);
};

#endif /* GameSettings_hpp */
