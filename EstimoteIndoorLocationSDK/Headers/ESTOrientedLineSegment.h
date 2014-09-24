//  Copyright (c) 2014 Estimote Inc. All rights reserved.

#import "ESTOrientedPoint.h"

/**
 * Represents a geometrical line segment with additional information about orientation.
 * Object is immutable.
 */
@interface ESTOrientedLineSegment : NSObject

///-----------------------------------------
/// @name Properties
///-----------------------------------------
#pragma mark Properties

/** Coordinates of the first end point of the line segment. */
@property (nonatomic, strong, readonly) ESTPoint *point1;
/** Coordinates of the second end point of the line segment. */
@property (nonatomic, strong, readonly) ESTPoint *point2;
/**
 * Orientation associated with the line segment. If not defined takes EST_ORIENTATION_UNDEFINED value.
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
 * @param point1 An ESTPoint object representing first end point of the line segment.
 * @param point2 An ESTPoint object representing second end point of the line segment.
 * @param orientation Orientation of the line segment.
 * @return A line segment initialized with (point1, point2, orientation).
 */
- (instancetype)initWithPoint1:(ESTPoint *)point1
                        point2:(ESTPoint *)point2
                   orientation:(double)orientation;

/**
 * Returns a new oriented line segment object.
 *
 * @param point1 An ESTPoint object representing first end point of the line segment.
 * @param point2 An ESTPoint object representing second end point of the line segment.
 * @param orientation Orientation of the line segment.
 * @return A line segment initialized with (point1, point2, orientation).
 */
+ (instancetype)lineWithPoint1:(ESTPoint *)point1
                        point2:(ESTPoint *)point2
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
+ (instancetype)lineWithLine:(ESTOrientedLineSegment *)line;

#pragma mark Operations on line segment
///-----------------------------------------
/// @name Operations on line segment
///-----------------------------------------

/**
 * Calculates a center point of the line. Has the same orientation as the line segment.
 *
 * @return A new oriented point representing center of the line segment.
 */
- (ESTOrientedPoint *)centerPoint;

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
- (ESTOrientedLineSegment *)lineTranslatedBydX:(double)dX
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
+ (ESTOrientedLineSegment *)lineFromDictionary:(NSDictionary *)dict;

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
- (BOOL)isEqual:(id)other;

/** @see isEqual: */
- (BOOL)isEqualToOrientedLine:(ESTOrientedLineSegment *)line;

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
-(NSString *)description;

@end
