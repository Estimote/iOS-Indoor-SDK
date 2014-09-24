// Copyright (c) 2014 Estimote Inc. All rights reserved.

#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import "ESTOrientedLineSegment.h"
#import "ESTPositionedBeacon.h"
#import "ESTLocationLinearObject.h"

/**
* Represents a physical location prepared for Estimote Indoor Location. Object is immutable.
*
* Instances of `ESTLocation` can be created by `ESTLocationBuilder` or by importing
* JSON with `[ESTLocationBuilder parseFromJSON:]`.
*/
@interface ESTLocation : NSObject

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Name of the location. */
@property (nonatomic, strong, readonly) NSString        *name;

/** Boundary of the location. Array of `ESTOrientedLineSegment`. */
@property (nonatomic, strong, readonly) NSArray         *boundarySegments;

/** Bezier path of the boundary of the location. */
@property (nonatomic, strong, readonly) UIBezierPath    *shape;

/** Bounding box of the location. */
@property (nonatomic, assign, readonly) CGRect          boundingBox;

/** Linear objects inside the location. Array of `ESTLocationLinearObject`. */
@property (nonatomic, strong, readonly) NSArray         *linearObjects;

/** Beacons located in the location. Array of `ESTPositionedBeacon`. */
@property (nonatomic, strong, readonly) NSArray         *beacons;

/** Orientation to magnetic north, counted clockwise. Value is in degrees. */
@property (nonatomic, assign, readonly) double          orientation;

/** Creation date. */
@property (nonatomic, strong, readonly) NSDate          *creationDate;


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
- (instancetype)initWithLocation:(ESTLocation *)location;

/**
* Returns a new location based on a given location.
*
* @param location The location.
* @return A new location based on a given location.
*/
+ (ESTLocation *)locationFromLocation:(ESTLocation *)location;

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
+ (ESTLocation *)locationFromDictionary:(NSDictionary *)dict;

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
- (ESTLocation *)locationTranslatedByDX:(double)x dY:(double)y;

/**
* Checks if a given point is inside the location.
*
* @param x X coordinate.
* @param y Y coordinate.
* @return YES if given point is inside the location.
*/
- (BOOL)containsPointWithX:(double)x y:(double)y;

/** @see containsPointWithX:y: */
- (BOOL)containsPoint:(ESTPoint *)point;

/**
* Returns a equally distributed random point inside the location.
*
* @return A random point inside the location.
*/
- (ESTPoint *)randomPointInside;

/**
* Filters this location linear objects and returns only those for given type.
*
* @param type Type of linear object to filter this location linear objects.
* @return Array of `ESTLinearObject` with given type.
*/
- (NSArray *)linearObjectsWithType:(ESTLocationLinearObjectType)type;

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
- (BOOL)isEqual:(id)other;

/** @see isEqual: */
- (BOOL)isEqualToLocation:(ESTLocation *)location;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

@end
