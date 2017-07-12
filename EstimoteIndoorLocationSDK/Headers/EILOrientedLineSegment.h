//  Copyright (c) 2014 Estimote Inc. All rights reserved.

#import <Foundation/Foundation.h>

@class EILPoint;
@class EILOrientedPoint;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents a geometrical line segment with additional information about orientation.
 * Object is immutable.
 */
@interface EILOrientedLineSegment : NSObject <NSCoding>

///-----------------------------------------
/// @name Properties
///-----------------------------------------
#pragma mark Properties

/** Coordinates of the first end point of the line segment. */
@property (nonatomic, strong, readonly) EILPoint *point1;
/** Coordinates of the second end point of the line segment. */
@property (nonatomic, strong, readonly) EILPoint *point2;
/**
 * Orientation associated with the line segment. If not defined takes EIL_ORIENTATION_UNDEFINED value.
 * Value is in degrees, counted clockwise.
 */
@property (nonatomic, assign, readonly) double orientation;

#pragma mark Creating and Initializing Line Segments
///-----------------------------------------------
/// @name Creating and Initializing Line Segments
///-----------------------------------------------

/**
 * Returns a new oriented line segment object.
 *
 * @param point1 An EILPoint object representing first end point of the line segment.
 * @param point2 An EILPoint object representing second end point of the line segment.
 * @param orientation Orientation of the line segment.
 * @return A line segment initialized with (point1, point2, orientation).
 */
- (instancetype)initWithPoint1:(EILPoint *)point1
                        point2:(EILPoint *)point2
                   orientation:(double)orientation;

/**
 * Returns a new oriented line segment object.
 *
 * @param point1 An EILPoint object representing first end point of the line segment.
 * @param point2 An EILPoint object representing second end point of the line segment.
 * @param orientation Orientation of the line segment.
 * @return A line segment initialized with (point1, point2, orientation).
 */
+ (instancetype)lineWithPoint1:(EILPoint *)point1
                        point2:(EILPoint *)point2
                   orientation:(double)orientation;

/**
 * Returns a new oriented line segment object.
 *
 * @param x1 A x coordinate of the first end point of the line segment.
 * @param y1 An y coordinate of the first end point of the line segment.
 * @param x2 A x coordinate of the second end point of the line segment.
 * @param y2 An y coordinate of the second end point of the line segment.
 * @param orientation Orientation of the line segment.
 * @return A line segment initialized with ((x1,y1), (x2,y2), orientation).
 */
+ (instancetype)lineWithX1:(double)x1
                        y1:(double)y1
                        x2:(double)x2
                        y2:(double)y2
               orientation:(double)orientation;

/**
 * Returns a new oriented line segment object based on the given oriented line segment.
 *
 * @param line An oriented line segment.
 * @return An oriented line initialized with (line.point1, line.point2, line.orientation).
 */
+ (instancetype)lineWithLine:(EILOrientedLineSegment *)line;

#pragma mark Operations on line segment
///-----------------------------------------
/// @name Operations on line segment
///-----------------------------------------

/**
 * Calculates a center point of the line. Has the same orientation as the line segment.
 *
 * @return A new oriented point representing center of the line segment.
 */
- (EILOrientedPoint *)centerPoint;

/**
 * Calculates left point of the line.
 *
 * If the orientation of the line is pointing at you, the left point will be on the left.
 *
 * If the line does not have an orientation nil will be returned.
 *
 * @return An oriented point representing left point of the line. It will have the same orientation as the line.
 */
- (EILOrientedPoint *)leftPoint;

/**
 * Calculates right point of the line.
 *
 * If the orientation of the line is pointing at you, the right point will be on the right.
 *
 * If the line does not have an orientation nil will be returned.
 *
 * @return An oriented point representing right point of the line. It will have the same orientation as the line.
 */
- (EILOrientedPoint *)rightPoint;

/**
 * Calculates length of the line segment.
 *
 * @return A length of the line.
 */
- (double)length;

/**
 * Translates the line segment by a given vector (dX, dY) and returns a new line segment.
 *
 * @param dX Value of translation on X axis.
 * @param dY Value of translation on Y axis.
 * @return A new line segment translated by (dX, dY).
 */
- (EILOrientedLineSegment *)lineTranslatedBydX:(double)dX
                                            dY:(double)dY;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
* Deserializes an oriented line segment from `NSDictionary`.
*
* @param dict NSDictionary to deserialize from.
* @return An oriented line segment created from NSDictionary.
*/
+ (nullable EILOrientedLineSegment *)lineFromDictionary:(NSDictionary *)dict;

/**
 * Serializes the oriented line segment to `NSDictionary`.
 *
 * @return An oriented line segment representation in NSDictionary.
 */
- (NSDictionary *)toDictionary;

#pragma mark Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
 * Returns a boolean value that indicates whether given oriented line segment is equal to this one.
 *
 * @param other The object to be compared to this oriented line segment. May be nil.
 * @return YES if oriented line segments are equal, otherwise NO.
 */
- (BOOL)isEqual:(nullable id)other;

/** @see isEqual: */
- (BOOL)isEqualToOrientedLine:(nullable EILOrientedLineSegment *)line;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

#pragma mark Describing Objects
///-----------------------------------------
/// @name Describing Objects
///-----------------------------------------

/**
 * Returns a string representation of the receiver.
 *
 * @return A string representation of the oriented line segment in form of ((x1,y1),(x2,y2), orientation)
 */
- (NSString *)description;

#pragma mark Encoding and Decoding
///-----------------------------------------
/// @name Encoding and Decoding
///-----------------------------------------

/**
 * Returns an oriented line segment initialized from data in a given unarchiver.
 *
 * @param decoder An unarchiver object.
 * @return A new oriented line segment initialized using the data in decoder.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)decoder;

/**
 * Encodes the oriented line segment using a given archiver.
 *
 * @param An archiver object.
 */
- (void)encodeWithCoder:(NSCoder *)coder;

@end

NS_ASSUME_NONNULL_END
