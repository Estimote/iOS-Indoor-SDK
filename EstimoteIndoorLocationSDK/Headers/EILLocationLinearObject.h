//  Copyright (c) 2014 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

@class EILOrientedLineSegment;

///-----------------------------------------
/// @name Constants
///-----------------------------------------
#pragma mark Constants

/** Describes the type of the linear object. */
typedef enum : NSUInteger {
    EILLocationLinearObjectTypeDoor,
    EILLocationLinearObjectTypeWindow,
} EILLocationLinearObjectType;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents an object in a location which position can be described by a line segment.
 * Typical examples are doors, windows, internal partition walls etc.
 * Object is immutable.
 */
@interface EILLocationLinearObject : NSObject <NSCoding>

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Type of the object. */
@property (nonatomic, assign, readonly) EILLocationLinearObjectType type;
/**
 * Coordinates of the object in form of an oriented line segment.
 * Orientation typically represent direction toward center of the location, perpendicular to the line segment.
 */
@property (nonatomic, strong, readonly) EILOrientedLineSegment *position;

#pragma mark Creating and Initializing Points
///------------------------------------------------
/// @name Creating and Initializing Linear Objects
///------------------------------------------------

/**
 * Returns a new linear object.
 *
 * @param type A type of the linear object.
 * @param position Coordinates of the object in form of an oriented line segment
 * @return A linear object initialized with position and type.
 */
- (instancetype)initWithType:(EILLocationLinearObjectType)type
                    position:(EILOrientedLineSegment *)position;

/**
 * Returns a new linear object based on the given linear object.
 *
 * @param point A linear object.
 * @return An linear object initialized with linearObject.type and linearObject.position
 */
+ (instancetype)linearObjectWithLinearObject:(EILLocationLinearObject *)linearObject;

#pragma mark Operations on linear object
///-----------------------------------------
/// @name Operations on linear object
///-----------------------------------------

/**
* Translates the linear object by a given vector (dX, dY) and returns a new linear object.
*
* @param dX Value of translation on X axis.
* @param dY Value of translation on Y axis.
* @return A new linear object translated by (dX, dY).
*/
- (instancetype)linearObjectTranslatedByDX:(double)dX
                                        dY:(double)dY;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
* Deserializes a linear object from `NSDictionary`.
*
* @param dict NSDictionary to deserialize from.
* @return A linear object created from NSDictionary.
*/
+ (nullable EILLocationLinearObject *)linearObjectFromDictionary:(NSDictionary *)dict;

/**
* Serializes the linear object to `NSDictionary`.
*
* @return A linear object representation in NSDictionary.
*/
- (NSDictionary *)toDictionary;

#pragma mark Identifying and Comparing Objects
///-----------------------------------------
/// @name Identifying and Comparing Objects
///-----------------------------------------

/**
* Returns a boolean value that indicates whether given linear object is equal to this one.
*
* @param other The object to be compared to this linear object. May be nil.
* @return YES if linear objects are equal, otherwise NO.
*/
- (BOOL)isEqual:(nullable id)other;

/** @see isEqual: */
- (BOOL)isEqualToLinearObject:(nullable EILLocationLinearObject *)object;

/** Returns an integer that can be used as a table address in a hash table structure. */
- (NSUInteger)hash;

#pragma mark Describing Objects
///-----------------------------------------
/// @name Describing Objects
///-----------------------------------------

/**
 * Returns a string representation of the location linear object.
 *
 * @return A string representation of the location linear object.
 */
- (NSString *)description;

#pragma mark Encoding and Decoding
///-----------------------------------------
/// @name Encoding and Decoding
///-----------------------------------------

/**
 * Returns a location linear object initialized from data in a given unarchiver.
 *
 * @param decoder An unarchiver object.
 * @return A new location linear object initialized using the data in decoder.
 */
- (nullable instancetype)initWithCoder:(NSCoder *)decoder;

/**
 * Encodes the location linear object using a given archiver.
 *
 * @param An archiver object.
 */
- (void)encodeWithCoder:(NSCoder *)coder;

@end

NS_ASSUME_NONNULL_END
