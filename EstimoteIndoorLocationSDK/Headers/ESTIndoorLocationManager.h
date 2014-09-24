//  Copyright (c) 2014 Estimote. All rights reserved.

#import "ESTLocation.h"
#import "ESTOrientedPoint.h"

@class ESTIndoorLocationManager;

/**
 * The `ESTIndoorLocationManagerDelegate` protocol defines the methods to receive position updates.
 */
@protocol ESTIndoorLocationManagerDelegate

/**
 * Tells the delegate that new position update is available.
 *
 * @param manager The manager object that generated the event.
 * @param position A position inside the location.
 * @param location The location for which which the position was updated.
 */
- (void)indoorLocationManager:(ESTIndoorLocationManager *)manager
            didUpdatePosition:(ESTOrientedPoint *)position
                   inLocation:(ESTLocation *)location;
/**
 * Tells the delegate that position update could not be determined.
 *
 * @param manager The manager object that generated the event.
 * @param error Error why position could not be determined.
 */
- (void)indoorLocationManager:(ESTIndoorLocationManager *)manager
didFailToUpdatePositionWithError:(NSError *)error;

@end

/**
The `ESTIndoorLocationManager` class defines the interface for Estimote Indoor Location SDK. Use
this class to setup a new location and to obtain position inside the location.
Only one instance of this class should be created inside the application.

### Setting up a new location
 
In order to obtain precise position updates you need to prepare a physical location for Estimote Indoor Location.
The procedure consists of the following steps:

- Configuration of the beacons.
- Placing beacons.
- Mapping the physical location to an instance of `ESTLocation`.
 
Invoke `locationSetupControllerWithCompletion:` to obtain dedicated UIViewController guiding through this process.
Result of this procedure is a prepared physical location and an instance of ESTLocation that can be used for obtaining position updates.

 
### Obtaining position inside the location
 
Once you have instance of `ESTLocation` you can start obtaining position updates for that location.
First you need to set a `delegate` which will be receiving the updates and then start the manager for
the location. Note that only one location at a time is supported.
 
    indoorLocationManager.delegate = yourDelegate;
    [indoorLocationManager startIndoorLocation:yourLocation];

Do not forget to stop the manager if you are not using location updates any more.

    [indoorLocationManager stopIndoorLocation];

 */
@interface ESTIndoorLocationManager : NSObject

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** The delegate object to receive position update events. */
@property (nonatomic, weak) id <ESTIndoorLocationManagerDelegate> delegate;

/** Current active location. */
@property (nonatomic, strong, readonly) ESTLocation *currentLocation;

#pragma mark Setting up a new location
///-----------------------------------------
/// @name Setting up a new location
///-----------------------------------------

/**
 * Sets App ID and App Token, enabling communication with the Estimote Cloud API. It is required for
 * `locationSetupControllerWithCompletion:` to be able to configure the beacons for Indoor Location.
 *
 * You can find your API App ID and API App Token in the Account Settings section of the Estimote Cloud.
 *
 * @param appID The API App ID.
 * @param appToken The API App Token.
 */
+ (void)setupAppID:(NSString *)appID andAppToken:(NSString *)appToken;

/**
 * Checks if App ID and App Token were set.
 */
+ (BOOL)isAuthorized;

/**
 * Creates a `UIViewController` that guides through a process for preparing physical location for
 * Estimote Indoor Location.
 *
 * @param completion A block that is invoked when setup has been finished.
 * @return Controller for setting up location.
 */
+ (UIViewController *)locationSetupControllerWithCompletion:(void (^)(ESTLocation *location, NSError *error))completion;

#pragma mark Obtaining position inside the location
///----------------------------------------------
/// @name Obtaining position inside the location
///----------------------------------------------

/**
 * Starts the delivery of position updates for the specified location. Only one location is supported at the same time.
 * Calling this method without stopping the indoor location for previous location results in an exception.
 *
 * @param location The location.
 */
- (void)startIndoorLocation:(ESTLocation *)location;

/**
 * Stops the delivery of position updates.
 */
- (void)stopIndoorLocation;

@end
