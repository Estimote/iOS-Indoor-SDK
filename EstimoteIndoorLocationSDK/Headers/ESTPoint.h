//  Copyright (c) 2014 Estimote. All rights reserved.


/** Represents a geometrical point. Object is immutable. */
@interface ESTPoint : NSObject

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** X coordinate of the point. */
@property (nonatomic, assign, readonly) double x;
/** Y coordinate of the point. */
@property (nonatomic, assign, readonly) double y;

#pragma mark Creating and Initializing Points
///-----------------------------------------
/// @name Creating and Initializing Points
///-----------------------------------------

/**
 * Returns a new point object.
 * 
 * @param x Coordinate on X axis.
 * @param y Coordinate on Y axis.
 * @return A point initialized with (x, y).
 */
- (instancetype)initWithX:(double)x
                        y:(double)y;

/**
 * Returns a new point object.
 *
 * @param x Coordinate on X axis.
 * @param y Coordinate on Y axis.
 * @return A point initialized with (x, y).
 */
+ (instancetype)pointWithX:(double)x
                         y:(double)y;

/**
 * Returns a new point object based on the given point.
 *
 * @param point A point.
 * @return A point initialized with (point.x, point.y).
 */
+ (instancetype)pointWithPoint:(ESTPoint *)point;

#pragma mark Operations on point
///-----------------------------------------
/// @name Operations on point
///-----------------------------------------

/**
 * Translates the point by a given vector (dX, dY) and returns a new point.
 * 
 * @param dX Value of translation on X axis.
 * @param dY Value of translation on Y axis.
 * @return A new point translated by (dX, dY).
 */
- (instancetype)pointTranslatedBydX:(double)dX
                                 dY:(double)dY;
/**
 * Computes distance between given point and this point.
 *
 * @param point Given point to which distance will be computed.
 * @return Distance between points.
 */
- (double)distanceToPoint:(ESTPoint *)point;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
 * Deserializes a point from `NSDictionary`.
 *
 * @param dict NSDictionary to deserialize from.
 * @return A point created from NSDictionary.
 */
+ (ESTPoint *)pointFromDictionary:(NSDictionary *)dict;

/**
 * Serializes the point to `NSDictionary`.
 *
 * @return A point representation in NSDictionary.
 */
- (NSDictionary *)toDictionary;

#pragma mark Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
 * Returns a boolean value that indicates whether given point is equal to this one.
 *
 * @param other The object to be compared to this point. May be nil.
 * @return YES if points are equal, otherwise NO.
 */
- (BOOL)isEqual:(id)other;

/** @see isEqual: */
- (BOOL)isEqualToPoint:(ESTPoint *)point;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

#pragma mark Describing Objects
///-----------------------------------------
/// @name Describing Objects
///-----------------------------------------

/**
 * Returns a string representation of the receiver.
 *
 * @return A string representation of the point in form of (x,y)
 */
-(NSString *)description;


@end
