//
//  DeviceModel.m
//  GWP2P
//
//  Created by zengyuying on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "DeviceModel.h"
#import <GWP2P/GWP2P.h>

static NSMutableArray *deviceModels = nil;

@implementation DeviceModel

- (void)encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:self.deviceID forKey:@"deviceID"];
    [aCoder encodeObject:self.devicePassword forKey:@"devicePassword"];
    [aCoder encodeInteger:self.deviceType forKey:@"deviceType"];
    [aCoder encodeInteger:self.deviceSubtype forKey:@"deviceSubtype"];
    [aCoder encodeBool:self.deviceSharingType forKey:@"deviceSharingType"];
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super init];
    if (self) {
        self.deviceID = [aDecoder decodeObjectForKey:@"deviceID"];
        self.devicePassword = [aDecoder decodeObjectForKey:@"devicePassword"];
        self.deviceType = [aDecoder decodeIntegerForKey:@"deviceType"];
        self.deviceSubtype = [aDecoder decodeIntegerForKey:@"deviceSubtype"];
        self.deviceSharingType = [aDecoder decodeBoolForKey:@"deviceSharingType"];
    }
    return self;
}

+ (void)updateDeviceModels {
    NSString *docPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
    NSString *userID = [[NSUserDefaults standardUserDefaults] valueForKey:@"kGWLoginAccount"]; 
    NSString *userPath = [docPath stringByAppendingFormat:@"/archive/%@",userID];
    NSArray *deviceFiles = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:userPath error:nil];
    deviceModels = [NSMutableArray array];
    for (NSString *deviceFile in deviceFiles) {
        NSString *devicePath = [userPath stringByAppendingPathComponent:deviceFile];
        DeviceModel *deviceModel = [NSKeyedUnarchiver unarchiveObjectWithFile:devicePath];
        [deviceModels addObject:deviceModel];
    }
}

+ (NSArray<DeviceModel *> *)deviceModels {
    if (!deviceModels) {
        [self updateDeviceModels];
    }
    return deviceModels;
}

+ (void)saveDeviceModel:(DeviceModel *)deviceModel {
    NSString *docPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
    NSString *userID = [[NSUserDefaults standardUserDefaults] valueForKey:@"kGWLoginAccount"];
    NSString *userPath = [docPath stringByAppendingFormat:@"/archive/%@",userID];
    NSString *devicePath = [userPath stringByAppendingPathComponent:deviceModel.deviceID];
    [[NSFileManager defaultManager] createDirectoryAtPath:userPath withIntermediateDirectories:YES attributes:nil error:nil];
    [NSKeyedArchiver archiveRootObject:deviceModel toFile:devicePath];
    [self updateDeviceModels];
}

+ (void)removeDeviceModel:(DeviceModel *)deviceModel {
    NSString *docPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
    NSString *userID = [[NSUserDefaults standardUserDefaults] valueForKey:@"kGWLoginAccount"];
    NSString *userPath = [docPath stringByAppendingFormat:@"/archive/%@",userID];
    NSString *devicePath = [userPath stringByAppendingPathComponent:deviceModel.deviceID];
    [[NSFileManager defaultManager] removeItemAtPath:devicePath error:nil];
    [self updateDeviceModels];
}

@end
