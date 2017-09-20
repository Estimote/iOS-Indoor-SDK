//  Copyright © 2017 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class EILLocation;
@class EILOrientedPoint;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents a physical objects inside location like landmarks or points of interests.
 */

@interface EILLocationPin : NSObject <NSCoding>

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/**  Name of the location pin. */
@property (nonatomic, strong, readonly) NSString *name;

/** Type of the location pin. */
@property (nonatomic, strong, readonly) NSString *type;

/** Identifier of the location pin. */
@property (nonatomic, readonly) NSNumber *identifier;

/** Postion of the pin inside a location. */
@property (nonatomic, strong, readonly) EILOrientedPoint *position;


#pragma mark Creating and Initializing
///-----------------------------------------
/// @name Creating and Initializing
///-----------------------------------------

- (instancetype) init NS_UNAVAILABLE;

/**
 * Class constructor.
 *
 * @param name of the pin.
 * @param type of the pin.
 * @param identifier of the pin.
 * @param position of the pin.
 * @return A new location pin.
 */
- (instancetype)initWithName:(NSString *)name
                        type:(NSString *)type
                  identifier:(nullable NSNumber *)identifier
                    position:(EILOrientedPoint *)position;

/**
 * Translates the location pin by a given vector (dX, dY) and returns a new pin.
 *
 * @param dX Value of translation on X axis.
 * @param dY Value of translation on Y axis.
 * @return A new location pin translated by (dX, dY).
 */
- (instancetype)locationPinTranslatedBydX:(double)dX
                                       dY:(double)dY;

#pragma mark Serialization
///-----------------------------------------
/// @name Serialization
///-----------------------------------------

/**
 * Deserializes a location pin from `NSDictionary`.
 *
 * @param dict `NSDictionary` to deserialize from.
 * @return A location pin created from `NSDictionary`.
 */
+ (nullable EILLocationPin *)locationPinFromDictionary:(NSDictionary *)dict;

/**
 * Serializes the point to `NSDictionary`.
 *
 * @return A location pin representation in `NSDictionary`.
 */
- (NSDictionary *)toDictionary;

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
