//
//  BeaconBridge.hpp
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#ifndef BeaconBridge_hpp
#define BeaconBridge_hpp

#include "cocos2d.h"

USING_NS_CC;

class BeaconBridge;

using BeaconCallback = std::function<void (const bool &)>;

class BeaconBridge
{
public :
    static void beaconAction(bool flg, BeaconCallback callback);
    static std::string initBeaconUUID();
    static void initBeacon(const std::string& uuid);
};


#endif /* BeaconBridge_hpp */
