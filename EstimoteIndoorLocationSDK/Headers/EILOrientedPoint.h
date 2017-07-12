// Copyright (c) 2014 Estimote Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "EILPoint.h"

/**
* A constant for undefined orientation
*/
#define EIL_ORIENTATION_UNDEFINED -1

NS_ASSUME_NONNULL_BEGIN

/** Represents a geometrical point with additional information about orientation. Object is immutable. */
@interface EILOrientedPoint : EILPoint <NSCoding>

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/**
 * Orientation of the point. If not defined takes EIL_ORIENTATION_UNDEFINED value.
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
* Returns a new oriented point object with orientation set to EIL_ORIENTATION_UNDEFINED
*
* @param x Coordinate on X axis.
* @param y Coordinate on Y axis.
* @return An oriented point initialized with (x, y, EIL_ORIENTATION_UNDEFINED).
*/
- (instancetype)initWithX:(double)x
                        y:(double)y;

/**
* Returns a new oriented point object with orientation set to EIL_ORIENTATION_UNDEFINED
*
* @param x Coordinate on X axis.
* @param y Coordinate on Y axis.
* @return An oriented point initialized with (x, y, EIL_ORIENTATION_UNDEFINED).
*/
+ (instancetype)pointWithX:(double)x
                         y:(double)y;

/**
* Returns a new oriented point object based on the given oriented point.
*
* @param point An oriented point.
* @return An oriented point initialized with (point.x, point.y, point.orientation).
*/
+ (instancetype)pointWithOrientedPoint:(EILOrientedPoint *)point;


/**
* Returns a new oriented point object based on the given point and orientation.
*
* @param point A point.
* @param orientation Orientation of the point.
* @return An oriented point initialized with (point.x, point.y, orientation).
*/
+ (instancetype)pointWithPoint:(EILPoint *)point
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
+ (nullable EILOrientedPoint *)pointFromDictionary:(NSDictionary *)dict;

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
- (BOOL)isEqual:(nullable id)other;

/** @see isEqual: */
- (BOOL)isEqualToOrientedPoint:(nullable EILOrientedPoint *)point;

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
- (NSString *)description;


#pragma mark Encoding and Decoding
///-----------------------------------------
/// @name Encoding and Decoding
///-----------------------------------------

/**
 * Returns an oriented point initialized from data in a given unarchiver.
 *
 * @param decoder An unarchiver object.
 * @return A new oriented point initialized using the data in decoder.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)decoder;

/**
 * Encodes the oriented point using a given archiver.
 *
 * @param An archiver object.
 */
- (void)encodeWithCoder:(NSCoder *)coder;

@end

NS_ASSUME_NONNULL_END
