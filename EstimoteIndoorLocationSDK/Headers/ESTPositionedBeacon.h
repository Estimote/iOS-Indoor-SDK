//  Copyright (c) 2014 Estimote. All rights reserved.

#import "ESTOrientedPoint.h"
#import "ESTBeacon.h"

/** Represents a beacon with additional information about its position. Object is immutable. */
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
 * @param position Beacon position.
 * @return A positioned beacon initialized with MAC and position.
 */
- (instancetype)initWithBeaconIdentifiedByMac:(NSString *)macAddress
                                 withPosition:(ESTOrientedPoint *)position;

/**
 * Returns a new beacon object.
 *
 * @param beacon Beacon object.
 * @param position Beacon position.
 * @return A positioned beacon initialized with MAC and position.
 */
- (instancetype)initWithESTBeacon:(ESTBeacon *)beacon
                     withPosition:(ESTOrientedPoint *)position;

/**
 * Returns a new beacon object.
 *
 * @param dX X beacon position translation value.
 * @param dY Beacon Y beacon position translation value.
 * @return A beacon with position translated by (dX, dY).
 */
- (instancetype)beaconTranslatedByDX:(double)dX
                                  dY:(double)dY;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
 * Deserializes a positioned beacon from `NSDictionary`.
 *
 * @param dict `NSDictionary` to deserialize from.
 * @return A positioned beacon created from `NSDictionary`.
 */
+ (ESTPositionedBeacon *)beaconFromDictionary:(NSDictionary *)dict;

/**
 * Serializes the positioned beacon to `NSDictionary`.
 *
 * @return A positioned beacon representation in `NSDictionary`.
 */
- (NSDictionary *)toDictionary;

#pragma mark Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
 * Returns a boolean value that indicates whether given beacon is equal to this one.
 *
 * @param other The object to be compared to the beacon. May be nil.
 * @return YES if beacons are equal, otherwise NO.
 */
- (BOOL)isEqual:(id)other;

/**
 * Returns a boolean value that indicates whether given beacon is equal to this one.
 *
 * @param beacon The beacon object to be compared to the beacon. May be nil.
 * @return YES if beacons are equal, otherwise NO.
 */
- (BOOL)isEqualToPositionedBeacon:(ESTPositionedBeacon *)beacon;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

@end
