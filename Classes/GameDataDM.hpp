//
//  GameDataDM.hpp
//  Mashumarodrops
//
//  Created by Takauma on 2017/02/13.
//
//

#ifndef GameDataDM_hpp
#define GameDataDM_hpp

#include "cocos2d.h"

USING_NS_CC;

class GameDataDM;

using GameDataDMCallback = std::function<void (const bool &)>;

class GameDataDM : public cocos2d::Node
{
public:
    GameDataDM();
    virtual ~GameDataDM();
    virtual bool init();
    CREATE_FUNC(GameDataDM);
    
    ValueMap LoadBundlePlist(const char* pListName);
    void writeSaveFile(ValueMap data, GameDataDMCallback callback);
    
    CC_SYNTHESIZE(ValueMap, _dicItems, DicItem);
    
private:
};

#endif /* GameDataDM_hpp */
