//  Copyright (c) 2014 Estimote. All rights reserved.

#import "ESTOrientedPoint.h"
#import "ESTBeacon.h"

/** Represents a measured beacon. Object is immutable. */
@interface ESTPositionedBeacon : NSObject

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Oriented point representing beacons position and orientation. */
@property (nonatomic, strong, readonly) ESTOrientedPoint *position;
/** Beacons mac address. */
@property (nonatomic, strong, readonly) NSString *macAddress;
/** Beacons color. */
@property (nonatomic, assign, readonly) ESTBeaconColor color;

#pragma mark Creating and Initializing Beacons
///-----------------------------------------
/// @name Creating and Initializing Beacons
///-----------------------------------------

/**
 * Designated initializer. Returns a new beacon object.
 *
 * @param macAddress Beacon MAC address.
 * @param position Beacon position oriented point.
 * @return A beacon initialized with MAC and oriented point.
 */
- (instancetype)initWithBeaconIdentifiedByMac:(NSString *)macAddress
                                 withPosition:(ESTOrientedPoint *)position;

/**
 * Returns a new beacon object.
 *
 * @param beacon Beacon object.
 * @param position Beacon position oriented point.
 * @return A beacon initialized with beacon object and oriented point.
 */
- (instancetype)initWithESTBeacon:(ESTBeacon *)beacon
                     withPosition:(ESTOrientedPoint *)position;

/**
 * Returns a new beacon object.
 *
 * @param dX X beacon position translation value.
 * @param dY Beacon Y beacon position translation value.
 * @return A beacon initialized with beacon translation values.
 */
- (instancetype)beaconTranslatedByDX:(double)dX
                                  dY:(double)dY;

/**
 * Returns a new beacon object.
 *
 * @param dict A dictionary containing beacon creation data.
 * @return A beacon initialized with disctionary.
 */
+ (ESTPositionedBeacon *)beaconFromDictionary:(NSDictionary *)dict;

/**
 * Beacon data in dictionary.
 *
 * @return A dictionary containing beacon creation data.
 */
- (NSDictionary *)toDictionary;

#pragma mark Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
 * Returns a boolean value that indicates whether given navigation beacon is equal to this one.
 *
 * @param other The object to be compared to the navigation beacon. May be nil.
 * @return YES if navigation beacons are equal, otherwise NO.
 */
- (BOOL)isEqual:(id)other;

/**
 * Returns a boolean value that indicates whether given navigation beacon is equal to this one.
 *
 * @param navigationBeacon The beacon object to be compared to the navigation beacon. May be nil.
 * @return YES if navigation beacons are equal, otherwise NO.
 */
- (BOOL)isEqualToPositionedBeacon:(ESTPositionedBeacon *)navigationBeacon;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

@end
