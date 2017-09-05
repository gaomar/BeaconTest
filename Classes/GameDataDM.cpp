//
//  GameDataDM.cpp
//  Mashumarodrops
//
//  Created by Takauma on 2017/02/13.
//
//

#include "GameDataDM.hpp"

#define FILE_NAME "GameData"
////////////////////////////////////////////////////////////////////////////////
GameDataDM::GameDataDM()
: _dicItems(NULL)
{
}

////////////////////////////////////////////////////////////////////////////////
GameDataDM::~GameDataDM()
{
}
////////////////////////////////////////////////////////////////////////////////
bool GameDataDM::init()
{
    std::string str = StringUtils::format("%s", FILE_NAME);
    _dicItems = this->LoadBundlePlist(str.c_str());
    return true;
}
////////////////////////////////////////////////////////////////////////////////
ValueMap GameDataDM::LoadBundlePlist(const char *pListName)
{
    std::string pWorkStr = StringUtils::format("%s.%s.svd", "jp.co.ienter.BeaconTest", pListName);
    std::string savepath = FileUtils::getInstance()->getWritablePath() + pWorkStr.c_str();
    ValueMap dic;
    dic.clear();
    if(FileUtils::getInstance()->isFileExist(savepath)) {
        dic = FileUtils::getInstance()->getValueMapFromFile(savepath.c_str());
    }
    return dic;
}
////////////////////////////////////////////////////////////////////////////////
void GameDataDM::writeSaveFile(ValueMap data, GameDataDMCallback callback)
{
    std::string pWorkStr = StringUtils::format("%s.%s.svd", "jp.co.ienter.BeaconTest", FILE_NAME);
    
    //保存箇所のフルパスを取得
    std::string savepath = FileUtils::getInstance()->getWritablePath() + pWorkStr.c_str();
    //保存
    if(!FileUtils::getInstance()->writeToFile(data, savepath.c_str())) {
        log("save Failed:%s" , savepath.c_str());
        callback(false);
    } else {
        callback(true);
    }
}
