// Copyright (c) 2014 Estimote Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "EILLocationLinearObject.h"

@class EILPoint;
@class EILPositionedBeacon;
@class EILLocationPin;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents a physical location prepared for Estimote Indoor Location. Object is immutable.
 *
 * Instances of `EILLocation` can be obtained by fetching from the Estimote Cloud (see `EILRequestFetchLocation` and `EILRequestFetchLocations`), created by `EILLocationBuilder` or by importing JSON with `[EILLocationBuilder parseFromJSON:]`.
 */
@interface EILLocation : NSObject <NSCoding>

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Globally unique identifier of the location. Identifier is being set by server once location is persisted. */
@property (nonatomic, strong, readonly, nullable) NSString *identifier;

/** Name of the location. */
@property (nonatomic, strong, readonly) NSString *name;

/** Geographical location of the location. */
@property (nonatomic, strong, readonly, nullable) NSDictionary *geographicalLocation;

/** Latitude of geographical location of the location */
@property (nonatomic, strong, readonly, nullable) NSNumber *latitude;

/** Longitude of geographical location of the location */
@property (nonatomic, strong, readonly, nullable) NSNumber *longitude;

/** Email address of the owner of the location. */
@property (nonatomic, strong, readonly, nullable) NSString *owner;

/** Visibility of the location (private/public). */
@property (nonatomic, assign, readonly) BOOL isPublic;

/** Boundary of the location. */
@property (nonatomic, strong, readonly) NSArray<EILOrientedLineSegment *> *boundarySegments;

/** Bezier path of the boundary of the location. */
@property (nonatomic, strong, readonly) UIBezierPath *shape;

/** Polygon of shape of the location. Points are sorted clockwise.  */
@property (nonatomic, strong, readonly, nullable) NSArray<EILPoint *> *polygon;

/** Area of the location in square meters. */
@property (nonatomic, assign, readonly) double area;

/** Bounding box of the location. */
@property (nonatomic, assign, readonly) CGRect boundingBox;

/** Linear objects inside the location. */
@property (nonatomic, strong, readonly) NSArray<EILLocationLinearObject *> *linearObjects;

/** Beacons located in the location. */
@property (nonatomic, strong, readonly) NSArray<EILPositionedBeacon *> *beacons;

/** Orientation to magnetic north, counted clockwise. Value is in degrees. */
@property (nonatomic, assign, readonly) double orientation;

/** Location pins that belong to location. */
@property (nonatomic, strong, readonly, nullable) NSArray<EILLocationPin *> *locationPins;

/** Creation date. */
@property (nonatomic, strong, readonly) NSDate *creationDate;


#pragma mark Creating and Initializing
///-----------------------------------------
/// @name Creating and Initializing
///-----------------------------------------

/**
 * Copy constructor.
 *
 * @param location The location.
 * @return A new location based on a given location.
 */
- (instancetype)initWithLocation:(EILLocation *)location;

/**
 * Returns a new location based on a given location.
 *
 * @param location The location.
 * @return A new location based on a given location.
 */
+ (EILLocation *)locationFromLocation:(EILLocation *)location;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
 * Deserializes a location from `NSDictionary`.
 *
 * @param dict `NSDictionary` to deserialize from.
 * @return A location created from `NSDictionary`.
 */
+ (nullable EILLocation *)locationFromDictionary:(NSDictionary *)dict;

/**
 * Serializes the point to `NSDictionary`.
 *
 * @return A location representation in `NSDictionary`.
 */
- (NSDictionary *)toDictionary;

#pragma mark Utility methods
///-----------------------------------------
/// @name Utility methods
///-----------------------------------------

/**
 * Translates the location by a given vector (dX, dY) and returns a new location.
 *
 * @param x Value of the translation on X axis.
 * @param y Value of the translation on Y axis.
 * @return A new location translated by (dX, dY).
 */
- (EILLocation *)locationTranslatedByDX:(double)x dY:(double)y;

/**
 * Checks if a given point is inside the location.
 *
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return YES if given point is inside the location.
 */
- (BOOL)containsPointWithX:(double)x y:(double)y;

/** @see containsPointWithX:y: */
- (BOOL)containsPoint:(EILPoint *)point;

/**
 * Returns an equally distributed random point inside the location.
 *
 * @return A random point inside the location.
 */
- (EILPoint *)randomPointInside;

/**
 * Filters this location linear objects and returns only those for given type.
 *
 * @param type Type of linear object to filter this location linear objects.
 * @return Linear objects with given type.
 */
- (NSArray<EILLocationLinearObject *> *)linearObjectsWithType:(EILLocationLinearObjectType)type;

#pragma Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
 * Returns a Boolean value that indicates whether a given location is equal to this location.
 *
 * @param other The object to be compared to this location. May be nil.
 * @return YES if locations are equal, otherwise NO.
 */
- (BOOL)isEqual:(nullable id)other;

/** @see isEqual: */
- (BOOL)isEqualToLocation:(nullable EILLocation *)location;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

#pragma mark Describing Objects
///-----------------------------------------
/// @name Describing Objects
///-----------------------------------------

/**
 * Returns a string representation of the location.
 *
 * @return A string representation of the location.
 */
- (NSString *)description;

#pragma mark Encoding and Decoding
///-----------------------------------------
/// @name Encoding and Decoding
///-----------------------------------------

/**
 * Returns a location initialized from data in a given unarchiver.
 *
 * @param decoder An unarchiver object.
 * @return A new location initialized using the data in decoder.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)decoder;

/**
 * Encodes the location using a given archiver.
 *
 * @param An archiver object.
 */
- (void)encodeWithCoder:(NSCoder *)coder;

@end

NS_ASSUME_NONNULL_END
