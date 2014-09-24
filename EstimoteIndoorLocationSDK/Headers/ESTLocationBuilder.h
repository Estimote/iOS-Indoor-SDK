//  Copyright (c) 2014 Estimote. All rights reserved.

#import "ESTOrientedPoint.h"
#import "ESTLocation.h"

#define EST_LOCATION_DEFAULT_NAME @"MyEstimoteLocation"

/** Side of the boundary segment as seen from inside of the location. */
typedef NS_ENUM(int, ESTLocationBuilderSide) {

    /** Left side of the boundary segment as seen from inside of the location. */
    ESTLocationBuilderLeftSide,

    /** Right side of the boundary segment as seen from inside of the location. */
    ESTLocationBuilderRightSide,
};


/**
`ESTLocationBuilder` is a builder object for creating `ESTLocation` objects.

In order to construct a new location you need to:

- set the shape of the location and its orientation
- add details such as beacons, walls, doors on boundary segments

The shape of the location is defined by its boundary points. For example, consider a square
defined by points (0,0), (0,5), (5,5), (5,0) along with its orientation with respect
to the magnetic north.

    [locationBuilder setLocationBoundaryPoints:@[
        [ESTPoint pointWithX:0 y:0],
        [ESTPoint pointWithX:0 y:5],
        [ESTPoint pointWithX:5 y:5],
        [ESTPoint pointWithX:5 y:0]]];

    [locationBuilder setLocationOrientation:0];

Points that define shape of location also define its boundary segments. They are indexed
in the same order as the points. There are following 4 segments: [(0,0), (0,5)], [(0,5), (5,5)],
[(5,5), (5,0)], [(5,0), (0,0)].

The next step is to place beacons, doors on the boundary segments of the location:

    [locationBuilder addBeaconIdentifiedByMac:@"MAC1"
                       atBoundarySegmentIndex:0
                                   inDistance:2
                                     fromSide:ESTLocationBuilderLeftSide];

*/
@interface ESTLocationBuilder : NSObject

#pragma mark Preparing shape of the location
///-----------------------------------------
/// @name Preparing shape of the location
///-----------------------------------------

/**
 * Adds a list of boundary points of location. Can be added clockwise or anti-clockwise.
 *
 * @param boundaryPoints List of boundary points (`ESTPoint`) that defines a location.
 */
- (void)setLocationBoundaryPoints:(NSArray *)boundaryPoints;

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
 * @param macAddress MAC address of the beacon.
 * @param boundarySegmentIndex Index of the boundary segment.
 * @param distance Distance from the beacon to the side of the boundary segment.
 * @param side Side of the boundary segment as seen from inside of the location.
 */
- (void)addBeaconIdentifiedByMac:(NSString *)macAddress
          atBoundarySegmentIndex:(NSUInteger)boundarySegmentIndex
                      inDistance:(double)distance
                        fromSide:(ESTLocationBuilderSide)side;

/**
 * Places a door on the boundary segment.
 * Boundary segments were created in the same order as points were added.
 *
 * @param length Length of the door.
 * @param boundarySegmentIndex Index of the boundary segment.
 * @param distance Distance from the door to the side of the boundary segment.
 * @param side Side of the boundary segment as seen from inside of the location.
 */
- (void)addDoorsWithLength:(double)length
    atBoundarySegmentIndex:(NSUInteger)boundarySegmentIndex
                inDistance:(double)distance
                  fromSide:(ESTLocationBuilderSide)side;

/**
 * Places a window on the boundary segment.
 * Boundary segments were created in the same order as points were added.
 *
 * @param length Length of the window.
 * @param boundarySegmentIndex Index of the boundary segment.
 * @param distance Distance from the window to the side of the boundary segment.
 * @param side Side of the boundary segment as seen from inside of the location.
 */
- (void)addWindowWithLength:(double)length
     atBoundarySegmentIndex:(NSUInteger)boundarySegmentIndex
                 inDistance:(double)distance
                   fromSide:(ESTLocationBuilderSide)side;

/**
 * Sets a name of the location. If not set EST_LOCATION_DEFAULT_NAME is used.
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
- (ESTLocation *)build;

/**
* Parses JSON string representation of the location. You might have it from the app
* through "Export location code snippet".
*
* If location cannot be constructed based on JSON, an exception will be raised with
* explanation why it has happened.
*
* @param json JSON encoded as a string representation of the location.
* @return Location object built based upon the JSON. Returns nil if location cannot be built.
*/
+ (ESTLocation *)parseFromJSON:(NSString *)json;

@end
