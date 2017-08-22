//  Copyright (c) 2014 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <EstimoteSDK/EstimoteSDK.h>

#define EIL_LOCATION_DEFAULT_NAME @"MyEstimoteLocation"

/** Side of the boundary segment as seen from inside of the location. */
typedef NS_ENUM(int, EILLocationBuilderSide) {

    /** Left side of the boundary segment as seen from inside of the location. */
            EILLocationBuilderLeftSide,

    /** Right side of the boundary segment as seen from inside of the location. */
            EILLocationBuilderRightSide,
};

@class EILLocation;
@class EILOrientedPoint;
@class EILPoint;

NS_ASSUME_NONNULL_BEGIN

`EILLocationBuilder` is a builder object for creating `EILLocation` objects.

In order to construct a new location you need to:

- set the shape of the location and its orientation
- add details such as beacons, walls, doors on boundary segments

The shape of the location is defined by its boundary points. For example, consider a square
defined by points (0,0), (0,5), (5,5), (5,0) along with its orientation with respect
to the magnetic north.

    [locationBuilder setLocationBoundaryPoints:@[
        [EILPoint pointWithX:0 y:0],
        [EILPoint pointWithX:0 y:5],
        [EILPoint pointWithX:5 y:5],
        [EILPoint pointWithX:5 y:0]]];

    [locationBuilder setLocationOrientation:0];

Points that define shape of location also define its boundary segments. They are indexed
in the same order as the points. There are following 4 segments: [(0,0), (0,5)], [(0,5), (5,5)],
[(5,5), (5,0)], [(5,0), (0,0)].

The next step is to place beacons, doors on the boundary segments of the location:

    [locationBuilder addBeaconWithIdentifier:@"63d4819e6a1d"
                      atBoundarySegmentIndex:0
                                  inDistance:2
                                    fromSide:EILLocationBuilderLeftSide];


@interface EILLocationBuilder : NSObject

#pragma mark Preparing shape of the location
///-----------------------------------------
/// @name Preparing shape of the location
///-----------------------------------------

/**
 * Adds a list of boundary points of location. Can be added clockwise or counter clockwise.
 *
 * @param boundaryPoints List of boundary points that defines a location.
 */
- (void)setLocationBoundaryPoints:(NSArray<EILPoint *> *)boundaryPoints;

/**
 * Sets the orientation of the room with respect to the magnetic north. Counted clockwise in degrees.
 *
 * @param orientation Location orientation in degrees.
 */
- (void)setLocationOrientation:(double)orientation;

#pragma mark Adding details of the location
///-----------------------------------------
/// @name Adding details of the location
///-----------------------------------------

/**
 * Places a beacon on the boundary segment.
 * Boundary segments were created in the same order as points were added.
 *
 * @param identifier Beacon identifier (MAC address or identifier).
 * @param boundarySegmentIndex Index of the boundary segment.
 * @param distance Distance from the beacon to the side of the boundary segment.
 * @param side Side of the boundary segment as seen from inside of the location.
 */
- (void)addBeaconWithIdentifier:(NSString *)identifier
         atBoundarySegmentIndex:(NSUInteger)boundarySegmentIndex
                     inDistance:(double)distance
                       fromSide:(EILLocationBuilderSide)side;

/**
 * Places a beacon in the location.
 *
 * @param identifier Beacon identifier (MAC address or identifier).
 * @param position Coordinates of the beacon position.
 */
- (void)addBeaconWithIdentifier:(NSString *)identifier
                   withPosition:(EILOrientedPoint *)position;

/**
 * Places a beacon in the location.
 *
 * @param identifier Beacon identifier (MAC address or identifier).
 * @param position Coordinates of the beacon position.
 * @param color Color of the beacon.
 */
- (void)addBeaconWithIdentifier:(NSString *)identifier
                   withPosition:(EILOrientedPoint *)position
                       andColor:(ESTColor)color;



/**
 * Places a beacon in the location.
 *
 * @param macAddress Beacon MAC address.
 * @param position Coordinates of the beacon position.
 *
 * This method is deprecated. Use addBeaconWithIdentifier:withPosition: instead.
 */
- (void)addBeaconIdentifiedByMac:(NSString *)macAddress
                    withPosition:(EILOrientedPoint *)position
                    __deprecated_msg("Use addBeaconWithIdentifier:withPosition: instead.");

/**
 * Places a beacon in the location.
 *
 * @param macAddress Beacon MAC address.
 * @param position Coordinates of the beacon position.
 * @param color Color of the beacon.
 *
 * This method is deprecated. Use addBeaconWithIdentifier:withPosition:andColor: instead.
 */
- (void)addBeaconIdentifiedByMac:(NSString *)macAddress
                    withPosition:(EILOrientedPoint *)position
                        andColor:(ESTColor)color
                        __deprecated_msg("Use addBeaconWithIdentifier:withPosition:andColor: instead.");

/**
 * Places a door on the boundary segment.

 */
- (void)addDoorsWithLength:(double)length
    atBoundarySegmentIndex:(NSUInteger)boundarySegmentIndex
                inDistance:(double)distance
                  fromSide:(EILLocationBuilderSide)side;

/**
 
 */
- (void)addWindowWithLength:(double)length
     atBoundarySegmentIndex:(NSUInteger)boundarySegmentIndex
                 inDistance:(double)distance
                   fromSide:(EILLocationBuilderSide)side;

/**
 * Sets a name of the location. If not set EIL_LOCATION_DEFAULT_NAME is used.
 *
 * @param locationName Name of the location.
 */
- (void)setLocationName:(NSString *)locationName;

/**
 * Sets a creation date of the location. If not set the current date is used.
 *
 * @param date Creation date.
 */
- (void)setLocationCreationDate:(NSDate *)date;

#pragma mark Building & Importing Location
///-----------------------------------------
/// @name Building & Importing Location
///-----------------------------------------

/**
 * Builds a location.
 *
 * @return A valid location.
 */
- (nullable EILLocation *)build;

/**

 */
+ (nullable EILLocation *)parseFromJSON:(NSString *)json;

@end

NS_ASSUME_NONNULL_END
