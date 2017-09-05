//
//  BeaconController.m
//  BeaconTest-mobile
//
//  Created by Takauma on 2017/09/04.
//

#import "BeaconController.h"

static BeaconController *instanceOfDialogHelper;

@implementation BeaconController
+(BeaconController*) getInstance
{
    @synchronized(self)
    {
        if (instanceOfDialogHelper == nil)
        {
            instanceOfDialogHelper = [[BeaconController alloc] init];
        }
        
        return instanceOfDialogHelper;
    }
    
    // to avoid compiler warning
    return nil;
}

-(void) initBeacon:(NSString *)uuid
{
    _peripheralManager = [[CBPeripheralManager alloc] initWithDelegate:self
                                                                     queue:dispatch_get_main_queue()];
    _uuid = [uuid copy];
}

- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    
}

- (void) beaconAction:(bool)flg callback:(BeaconHandler)callback
{
    if (flg) {
        // ビーコン発信
        NSUUID* wkUUID = [[NSUUID alloc] initWithUUIDString:_uuid];
        CLBeaconRegion* region = [[CLBeaconRegion alloc] initWithProximityUUID:wkUUID
                                                                         major:1
                                                                         minor:80
                                                                    identifier:[wkUUID UUIDString]];
        
        NSDictionary* peripheralData = [region peripheralDataWithMeasuredPower:nil];
        [self.peripheralManager startAdvertising:peripheralData];
        callback(true);
    } else {
        // ビーコン停止
        [self.peripheralManager stopAdvertising];
        callback(true);
    }
}
@end
