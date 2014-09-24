// Copyright (c) 2014 Estimote Inc. All rights reserved.

#import "ESTPoint.h"


/**
* A constant for undefined orientation
*/
#define EST_ORIENTATION_UNDEFINED -1


/** Represents a geometrical point with additional information about orientation. Object is immutable. */
@interface ESTOrientedPoint : ESTPoint

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/**
 * Orientation of the point. If not defined takes EST_ORIENTATION_UNDEFINED value.
 * Value is in degrees, counted clockwise.
 */
@property (nonatomic, assign) double orientation;

#pragma mark Creating and Initializing Points
///-----------------------------------------
/// @name Creating and Initializing Points
///-----------------------------------------

/**
* Returns a new oriented point object.
*
* @param x Coordinate on X axis.
* @param y Coordinate on Y axis.
* @param orientation Orientation of the point.
* @return An oriented point initialized with (x, y, orientation).
*/
- (instancetype)initWithX:(double)x
                        y:(double)y
              orientation:(double)orientation;
/**
* Returns a new oriented point object.
*
* @param x Coordinate on X axis.
* @param y Coordinate on Y axis.
* @param orientation Orientation of the point.
* @return An oriented point initialized with (x, y, orientation).
*/
+ (instancetype)pointWithX:(double)x
                         y:(double)y
               orientation:(double)orientation;

/**
* Returns a new oriented point object with orientation set to EST_ORIENTATION_UNDEFINED
*
* @param x Coordinate on X axis.
* @param y Coordinate on Y axis.
* @return An oriented point initialized with (x, y, EST_ORIENTATION_UNDEFINED).
*/
- (instancetype)initWithX:(double)x
                        y:(double)y;

/**
* Returns a new oriented point object with orientation set to EST_ORIENTATION_UNDEFINED
*
* @param x Coordinate on X axis.
* @param y Coordinate on Y axis.
* @return An oriented point initialized with (x, y, EST_ORIENTATION_UNDEFINED).
*/
+ (instancetype)pointWithX:(double)x
                         y:(double)y;

/**
* Returns a new oriented point object based on the given oriented point.
*
* @param point An oriented point.
* @return An oriented point initialized with (point.x, point.y, point.orientation).
*/
+ (instancetype)pointWithOrientedPoint:(ESTOrientedPoint *)point;


/**
* Returns a new oriented point object based on the given oriented point and orientation.
*
* @param point An oriented point.
* @param orientation Orientation of the point.
* @return An oriented point initialized with (point.x, point.y, orientation).
*/
+ (instancetype)pointWithPoint:(ESTPoint *)point
                   orientation:(double)orientation;

#pragma mark Operations on point
///-----------------------------------------
/// @name Operations on point
///-----------------------------------------

/**
* Translates the oriented point by a given vector (dX, dY) and returns a new oriented point.
*
* @param dX Value of translation on X axis.
* @param dY Value of translation on Y axis.
* @return A new oriented point translated by (dX, dY).
*/
- (instancetype)pointTranslatedBydX:(double)dX
                                 dY:(double)dY;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
* Deserializes an oriented point from `NSDictionary`.
*
* @param dict NSDictionary to deserialize from.
* @return An oriented point created from NSDictionary.
*/
+ (ESTOrientedPoint *)pointFromDictionary:(NSDictionary *)dict;

/**
* Serializes the oriented point to `NSDictionary`.
*
* @return An oriented point representation in NSDictionary.
*/
- (NSDictionary *)toDictionary;

#pragma mark Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
 * Returns a boolean value that indicates whether given oriented point is equal to this one.
 *
 * @param other The object to be compared to this oriented point. May be nil.
 * @return YES if oriented points  are equal, otherwise NO.
 */
- (BOOL)isEqual:(id)other;

/** @see isEqual: */
- (BOOL)isEqualToOrientedPoint:(ESTOrientedPoint *)point;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

#pragma mark Describing Objects
///-----------------------------------------
/// @name Describing Objects
///-----------------------------------------

/**
* Returns a string representation of the receiver.
*
* @return A string representation of the point in form of (x,y, orientation)
*/
-(NSString *)description;

@end
