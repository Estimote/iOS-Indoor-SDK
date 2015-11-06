//  Copyright (c) 2014 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <EstimoteSDK/EstimoteSDK.h>

@class EILOrientedPoint;

/** Represents a beacon with additional information about its position. Object is immutable. */
@interface EILPositionedBeacon : NSObject

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Oriented point representing beacons position and orientation. */
@property (nonatomic, strong, readonly) EILOrientedPoint *position;
/** Beacons mac address. */
@property (nonatomic, strong, readonly) NSString *macAddress;
/** Beacons color. */
@property (nonatomic, assign, readonly) ESTColor color;
/** Beacons proximity UUID. Can be nil, if unknown. */
@property (nonatomic, strong, readonly) NSUUID *proximityUUID;
/** Beacons major value. Can be nil, if unknown. */
@property (nonatomic, strong, readonly) NSNumber *major;
/** Beacons minor value. Can be nil, if unknown. */
@property (nonatomic, strong, readonly) NSNumber *minor;


#pragma mark Creating and Initializing Beacons
///-----------------------------------------
/// @name Creating and Initializing Beacons
///-----------------------------------------

/**
 * Returns a new beacon object.
 *
 * @param macAddress Beacon MAC address.
 * @param position Beacon position.
 * @return A positioned beacon initialized with MAC and position.
 */
- (instancetype)initWithBeaconIdentifiedByMac:(NSString *)macAddress
                                 withPosition:(EILOrientedPoint *)position;

/**
 * Designated initializer. Returns a new beacon object.
 *
 * @param macAddress Beacon MAC address.
 * @param position Beacon position.
 * @param color Beacon color
 * @return A positioned beacon initialized with MAC and position.
 */
- (instancetype)initWithBeaconIdentifiedByMac:(NSString *)macAddress
                                 withPosition:(EILOrientedPoint *)position
                                        color:(ESTColor)color;

/**
 * Designated initializer. Returns a new beacon object.
 *
 * @param macAddress Beacon MAC address.
 * @param position Beacon position.
 * @param color Beacon color
 * @param proximityUUID Beacon proximity UUID.
 * @param major Beacon major value.
 * @param minor Beacon minor value.
 * @return A positioned beacon initialized with provided data.
 */
- (instancetype)initWithBeaconIdentifiedByMac:(NSString *)macAddress
                                 withPosition:(EILOrientedPoint *)position
                                        color:(ESTColor)color
                                proximityUUID:(NSUUID *)proximityUUID
                                        major:(NSNumber *)major
                                        minor:(NSNumber *)minor;

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
+ (EILPositionedBeacon *)beaconFromDictionary:(NSDictionary *)dict;

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
- (BOOL)isEqualToPositionedBeacon:(EILPositionedBeacon *)beacon;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

#pragma mark Describing Objects
///-----------------------------------------
/// @name Describing Objects
///-----------------------------------------

/**
 * Returns a string representation of the positioned beacon.
 *
 * @return A string representation of the EILPositionedBeacon.
 */
-(NSString *)description;

@end
