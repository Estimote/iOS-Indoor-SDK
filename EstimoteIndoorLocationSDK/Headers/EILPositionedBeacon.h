//  Copyright (c) 2014 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import "EILColor.h"

@class EILOrientedPoint;

NS_ASSUME_NONNULL_BEGIN

/** Represents a beacon with additional information about its position. Object is immutable. */
@interface EILPositionedBeacon : NSObject <NSCoding>

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Oriented point representing beacons position and orientation. */
@property (nonatomic, strong, readonly) EILOrientedPoint *position;
/** Beacons identifier. */
@property (nonatomic, strong, readonly) NSString *identifier;
/** Beacons color. */
@property (nonatomic, assign, readonly) EILColor color;
/** Beacons proximity UUID. Can be nil, if unknown. */
@property (nonatomic, strong, readonly, nullable) NSUUID *proximityUUID;
/** Beacons major value. Can be nil, if unknown. */
@property (nonatomic, strong, readonly, nullable) NSNumber *major;
/** Beacons minor value. Can be nil, if unknown. */
@property (nonatomic, strong, readonly, nullable) NSNumber *minor;


#pragma mark Creating and Initializing Beacons
///-----------------------------------------
/// @name Creating and Initializing Beacons
///-----------------------------------------

/**
 * Returns a new beacon object.
 *
 * @param identifier Beacon identifier (MAC address or identifier).
 * @param position Beacon position.
 * @return A positioned beacon initialized with identifier and position.
 */
- (instancetype)initWithBeaconIdentifier:(NSString *)identifier
                                position:(EILOrientedPoint *)position;

/**
 * Designated initializer. Returns a new beacon object.
 *
 * @param identifier Beacon identifier (MAC address or identifier).
 * @param position Beacon position.
 * @param color Beacon color
 * @return A positioned beacon initialized with identifier and position.
 */
- (instancetype)initWithBeaconIdentifier:(NSString *)identifier
                                position:(EILOrientedPoint *)position
                                   color:(EILColor)color;

/**
 * Designated initializer. Returns a new beacon object.
 *
 * @param identifier Beacon identifier (MAC address or identifier).
 * @param position Beacon position.
 * @param color Beacon color
 * @param proximityUUID Beacon proximity UUID.
 * @param major Beacon major value.
 * @param minor Beacon minor value.
 * @return A positioned beacon initialized with provided data.
 */
- (instancetype)initWithBeaconIdentifier:(NSString *)identifier
                                position:(EILOrientedPoint *)position
                                   color:(EILColor)color
                           proximityUUID:(nullable NSUUID *)proximityUUID
                                   major:(nullable NSNumber *)major
                                   minor:(nullable NSNumber *)minor;

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
+ (nullable EILPositionedBeacon *)beaconFromDictionary:(NSDictionary *)dict;

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
- (BOOL)isEqual:(nullable id)other;

/**
 * Returns a boolean value that indicates whether given beacon is equal to this one.
 *
 * @param beacon The beacon object to be compared to the beacon. May be nil.
 * @return YES if beacons are equal, otherwise NO.
 */
- (BOOL)isEqualToPositionedBeacon:(nullable EILPositionedBeacon *)beacon;

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
- (NSString *)description;

#pragma mark Encoding and Decoding
///-----------------------------------------
/// @name Encoding and Decoding
///-----------------------------------------

/**
 * Returns a positioned beacon initialized from data in a given unarchiver.
 *
 * @param decoder An unarchiver object.
 * @return A new positioned beacon initialized using the data in decoder.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)decoder;

/**
 * Encodes the positioned beacon segment using a given archiver.
 *
 * @param An archiver object.
 */
- (void)encodeWithCoder:(NSCoder *)coder;

@end

NS_ASSUME_NONNULL_END
