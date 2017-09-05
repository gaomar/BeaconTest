//
//  BeaconController.h
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#ifndef BeaconController_h
#define BeaconController_h

#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreLocation/CoreLocation.h>

@class BeaconController;

typedef void (^BeaconHandler)(bool flg);

@interface BeaconController : NSObject<CBPeripheralManagerDelegate>
{
    
}

@property (nonatomic, readonly) CBPeripheralManager* peripheralManager;
@property (nonatomic, readonly) NSString *uuid;

+(BeaconController*) getInstance;
- (void)initBeacon:(NSString*)uuid;
- (void)beaconAction:(bool)flg callback:(BeaconHandler)callback;

@end;
#endif /* BeaconController_h */
