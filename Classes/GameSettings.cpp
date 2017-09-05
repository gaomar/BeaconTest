//
//  GameSettings.cpp
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#include "GameSettings.hpp"

#define USER_DEFAULTS_KEY_UUID      "UUIDKey"

static GameSettings* g_gameSettings = NULL;

GameSettings* GameSettings::sharedSettings() {
    if (! g_gameSettings) {
        g_gameSettings = new GameSettings();
        
    }
    return g_gameSettings;
}

GameSettings::~GameSettings()
{
}

GameSettings::GameSettings()
{
    _gameDataDM = GameDataDM::create();
    _localData = _gameDataDM->getDicItem();
}

void GameSettings::writeLocalData(GameSettingsCallback callback)
{
    _gameDataDM->writeSaveFile(_localData, [=](bool flg)
    {
        callback(flg);
    });
}

std::string GameSettings::getUUID() const
{
    std::string ret = "";
    
    if (_localData.count(USER_DEFAULTS_KEY_UUID)) {
        ret = _localData.at(USER_DEFAULTS_KEY_UUID).asString();
    }
    return ret;
}
void GameSettings::setUUID(std::string var)
{
    _localData[USER_DEFAULTS_KEY_UUID] = var.c_str();
    this->writeLocalData([=](bool flg){log("setUUID=%d", flg);});
}
