//  Copyright (c) 2014 Estimote. All rights reserved.

#import "ESTLocation.h"
#import "ESTOrientedPoint.h"

/** A block object to be executed when the request finishes successfully. */
typedef void (^ESTIndoorCloudSuccess)(id object);
/** A block object to be executed when the request finishes with failure. */
typedef void (^ESTIndoorCloudFailure)(NSError *error);

/**
 * The possible errors returned during updating position.
 */
typedef NS_ENUM(NSInteger, ESTIndoorErrorCode) {
    /** An unknown error occurred. */
    ESTIndoorGenericError,
    /** Device is outside the location. */
    ESTIndoorPositionOutsideLocationError,
    /** The device does not have mangetometer or there is a hardware problem with it. */
    ESTIndoorMagnetometerInitializationError,
    /** Bluetooth is powered off. */
    ESTBluetoothOffError,
    /** App is not authorized to use Bluetooth Low Energy. */
    ESTUnauthorizedToUseBluetoothError,
    /** Platform does not support Bluetooth Low Energy. */
    ESTBluetoothNotSupportedError
};

/**
 * Describes the accuracy of the determined position.
 * Accuracy can be represented as a circle of given radius within which the real position is expected to be.
 * Note that values for accuracy levels are approximate and can change in the future.
 */
typedef NS_ENUM(NSInteger, ESTPositionAccuracy)
{
    /**
     * Very high accuracy represents the state when the algorithm is highly certain about determined position.
     * Accuracy is below 1m.
     */
    ESTPositionAccuracyVeryHigh = 0,

    /**
     * Accuracy of determined position is high.
     * Accuracy is below 1.62m.
     */
    ESTPositionAccuracyHigh     = 1,

    /**
     * Accuracy of determined position is medium.
     * Accuracy is below 2.62m.
     */
    ESTPositionAccuracyMedium   = 2,

    /**
     * Accuracy of determined position is low.
     * Accuracy is below 4.24m.
     */
    ESTPositionAccuracyLow      = 3,

    /**
     * Accuracy of determined position is very low - typically during the initialization phase.
     * Accuracy can also drop to this level when the quality of determined position decreases significantly.
     * Accuracy should be thought of as comparable to location size.
     */
    ESTPositionAccuracyVeryLow  = 4,
};

@class ESTIndoorLocationManager;

/**
 * The `ESTIndoorLocationManagerDelegate` protocol defines the methods to receive position updates.
 */
@protocol ESTIndoorLocationManagerDelegate <NSObject>

@optional

/**
 * Tells the delegate that new position update is available.
 *
 * @param manager The manager object that generated the event.
 * @param position The position inside the location.
 * @param location The location for which the position was updated.
 */
- (void)indoorLocationManager:(ESTIndoorLocationManager *)manager
            didUpdatePosition:(ESTOrientedPoint *)position
                   inLocation:(ESTLocation *)location __attribute__((deprecated(("Use indoorLocationManager:didUpdatePosition:withAccuracy:inLocation: instead"))));

/**
 * Tells the delegate that Location Manager is ready and will start updating position.
 *
 * @param manager The manager object that generated the event.
 */
- (void)indoorLocationManagerIsReady:(ESTIndoorLocationManager *)manager;

/**
 * Tells the delegate that new position update is available.
 *
 * @param manager The manager object that generated the event.
 * @param position The position inside the location.
 * @param positionAccuracy The accuracy of the determined position.
 * @param location The location for which the position was updated.
 */
- (void)indoorLocationManager:(ESTIndoorLocationManager *)manager
            didUpdatePosition:(ESTOrientedPoint *)position
                 withAccuracy:(ESTPositionAccuracy)positionAccuracy
                   inLocation:(ESTLocation *)location;

/**
 * Tells the delegate that position update could not be determined.
 *
 * @param manager The manager object that generated the event.
 * @param error The error object containing information why position could not be determined.
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
Result of this procedure is a prepared physical location and an instance of `ESTLocation` that can be used for obtaining position updates.


### Obtaining position inside the location

Once you have instance of `ESTLocation` you can start obtaining position updates for that location.
First you need to set a `delegate` which will be receiving the updates and then start the manager for
the location. Note that only one location at a time is supported.

    indoorLocationManager.delegate = yourDelegate;
    [indoorLocationManager startIndoorLocation:yourLocation];

Do not forget to stop the manager if you are not using location updates any more.

    [indoorLocationManager stopIndoorLocation];


### Managing locations in the cloud

You can manage your locations in Cloud either through http://cloud.estimote.com or with Estimote Indoor Location SDK.
With the SDK you can add and remove locations to the cloud account associated with the used appId
as well as fetch all the locations stored for that account.

Please remember that in order to have any of these methods working you need to call -[ESTConfig setupAppID:andAppToken:] first.


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
 * Creates a `UIViewController` that guides through a process for preparing physical location for
 * Estimote Indoor Location.
 *
 * In order to have this method working you need to call -[ESTConfig setupAppID:andAppToken:] first
 * to configure the beacons for Indoor Location.
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

#pragma mark Managing locations in the cloud
///----------------------------------------------
/// @name Managing locations in the cloud
///----------------------------------------------

/**
 * Saves new location to user's account associated with the currently used AppId.
 *
 * In order to have this method working you need to call -[ESTConfig setupAppID:andAppToken:] first.
 *
 * @param location Location to add.
 * @param success Success callback. Object returned is a new `ESTLocation` same as given with identifier set from cloud.
 * @param failure Failure callback. Contains error that occurred.
 */
- (void)addNewLocation:(ESTLocation *)location
               success:(ESTIndoorCloudSuccess)success
               failure:(ESTIndoorCloudFailure)failure;

/**
 * Removes a location from user's account associated with the currently used AppId.
 *
 * In order to have this method working you need to call -[ESTConfig setupAppID:andAppToken:] first.
 *
 * @param location Location to remove. Must contain cloud's identifier `[ESTLocation identifier]`.
 * @param success Success callback. Object returned is the removed `ESTLocation`.
 * @param failure Failure callback. Contains error that occurred.
 */
- (void)removeLocation:(ESTLocation *)location
               success:(ESTIndoorCloudSuccess)success
               failure:(ESTIndoorCloudFailure)failure;

/**
 * Fetches all locations from user's account associated with the currently used AppId.
 *
 * In order to have this method working you need to call -[ESTConfig setupAppID:andAppToken:] first.
 *
 * @param success Success callback. Invoked after location from cloud are fetched. Contains array of `ESTLocation`s.
 * @param failure Failure callback. Contains error that occurred.
 */
- (void)fetchUserLocationsWithSuccess:(ESTIndoorCloudSuccess)success
                              failure:(ESTIndoorCloudFailure)failure;

/**
 * Fetches nearby public locations from cloud.
 *
 * @param success Success callback. Invoked after location from cloud are fetched. Contains array of locations.
 * @param failure Failure callback. Contains error that occurred.
 */
- (void)fetchNearbyPublicLocationsWithSuccess:(ESTIndoorCloudSuccess)success
                                      failure:(ESTIndoorCloudFailure)failure;

/**
 * Fetches location of specified identifier from cloud.
 *
 * @param locationIdentifier Identifier of given public location.
 * @param success Success callback. Invoked after location from cloud is fetched. Contains location.
 * @param failure Failure callback. Contains error that occurred.
 */
- (void)fetchLocationByIdentifier:(NSString *)locationIdentifier
                      withSuccess:(ESTIndoorCloudSuccess)success
                          failure:(ESTIndoorCloudFailure)failure;


@end
