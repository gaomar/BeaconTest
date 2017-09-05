//
//  BeaconBridge.mm
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#import "BeaconBridge.hpp"
#import "BeaconController.h"

// ビーコン発信・停止
void BeaconBridge::beaconAction(bool flg, BeaconCallback callback)
{
    [[BeaconController getInstance] beaconAction:flg callback:^(bool flg) {
        callback(flg);
    }];
}

// UUID生成
std::string BeaconBridge::initBeaconUUID()
{
    NSString* userID = [[UIDevice currentDevice].identifierForVendor UUIDString];
    return [userID UTF8String];
}

// ビーコン初期化
void BeaconBridge::initBeacon(const std::string& uuid)
{
    NSString *aUUID = [NSString stringWithCString:uuid.c_str()
                                           encoding:[NSString defaultCStringEncoding]];
    [[BeaconController getInstance] initBeacon:aUUID];
    
}

