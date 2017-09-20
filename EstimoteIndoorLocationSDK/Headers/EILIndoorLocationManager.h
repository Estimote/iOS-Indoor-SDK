//  Copyright © 2015 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

/**
 * The possible modes of EILIndoorLocationManager position updates delivery.
 */
typedef NS_ENUM(NSInteger, EILIndoorLocationManagerMode)
{
    /**
     * Standard mode - provides stable and responsive position updates. This mode is compatible with all devices. Previously called `EILIndoorLocationManagerModeLight`.
     *
     * This is the default mode of `EILIndoorLocationManager`.
     */
            EILIndoorLocationManagerModeStandard,
    /**
     * Experimental With Inertia mode - provides more responsive position updates thanks to using inertial sensors. Requires device to be in portrait mode. This mode is not supported by iPad & iPod device families. Previously called `EILIndoorLocationManagerModeNormal`.
     */
            EILIndoorLocationManagerModeExperimentalWithInertia,
    /**
     * Experimental With ARKit mode - provides hyper precise and responsive position updates thanks to using ARKit. If you are designing a mixed-reality experience this is the suggested mode. Requires iOS 11 device compatible with ARKit World Tracking.
     *
     * Augmented Reality Kit relies on access to the camera to work correctly. You need to add `NSCameraUsageDescription` key to the `Info.plist` file, explaining how your app is going to use this privilege. For example, "We use Augmented Reality to give you a virtual tour around the museum."
     */
            EILIndoorLocationManagerModeExperimentalWithARKit,
};

/**
 * The possible states of the monitored location.
 */
typedef NS_ENUM(NSInteger, EILLocationState)
{
    /** The state of the monitored location is unknown. */
            EILLocationStateUnknown,
    /** The user is inside the location. */
            EILLocationStateInside,
    /** The user is outside the location. */
            EILLocationStateOutside
};

/**
 * The possible errors returned during updating position.
 */
typedef NS_ENUM(NSInteger, EILIndoorErrorCode)
{
    /** An unknown error occurred. */
            EILIndoorGenericError,
    /** Device is outside the location. */
            EILIndoorPositionOutsideLocationError,
    /** The device does not have mangetometer or there is a hardware problem with it. */
            EILIndoorMagnetometerInitializationError,
    /** Bluetooth is powered off. */
            EILBluetoothOffError,
    /** App is not authorized to use Bluetooth Low Energy. */
            EILUnauthorizedToUseBluetoothError,
    /** Platform does not support Bluetooth Low Energy. */
            EILBluetoothNotSupportedError
};

NS_ASSUME_NONNULL_BEGIN

/**
 * Describes the accuracy of the determined position.
 * Accuracy can be represented as a circle of given radius within which the real position is expected to be.
 * Note that values for accuracy levels are approximate and can change in the future.
 */
typedef NS_ENUM(NSInteger, EILPositionAccuracy)
{
    /**
     * Very high accuracy represents the state when the algorithm is highly certain about determined position.
     * Accuracy is below 1m.
     */
            EILPositionAccuracyVeryHigh = 0,

    /**
     * Accuracy of determined position is high.
     * Accuracy is below 1.62m.
     */
            EILPositionAccuracyHigh = 1,

    /**
     * Accuracy of determined position is medium.
     * Accuracy is below 2.62m.
     */
            EILPositionAccuracyMedium = 2,

    /**
     * Accuracy of determined position is low.
     * Accuracy is below 4.24m.
     */
            EILPositionAccuracyLow = 3,

    /**
     * Accuracy of determined position is very low - typically during the initialization phase.
     * Accuracy can also drop to this level when the quality of determined position decreases significantly.
     * Accuracy should be thought of as comparable to location size.
     */
            EILPositionAccuracyVeryLow = 4,

    /**
     * Accuracy of determined position is unknown.
     */
            EILPositionAccuracyUnknown = 5
};

@class EILIndoorLocationManager;
@class EILLocation;
@class EILOrientedPoint;
@class ARSession;
@class EILPoint;

/**
 * The `EILIndoorLocationManagerDelegate` protocol defines the methods to receive location updates.
 */
@protocol EILIndoorLocationManagerDelegate <NSObject>

@optional

/**
 * Tells the delegate that new position update is available.
 *
 * @param manager The manager object that generated the event.
 * @param position The position inside the location.
 * @param positionAccuracy The accuracy of the determined position.
 * @param location The location for which the position was updated.
 */
- (void)indoorLocationManager:(EILIndoorLocationManager *)manager
            didUpdatePosition:(EILOrientedPoint *)position
                 withAccuracy:(EILPositionAccuracy)positionAccuracy
                   inLocation:(EILLocation *)location;

/**
 * Tells the delegate that position update could not be determined.
 *
 * @param manager The manager object that generated the event.
 * @param error The error object containing information why position could not be determined.
 */
- (void)   indoorLocationManager:(EILIndoorLocationManager *)manager
didFailToUpdatePositionWithError:(NSError *)error;

@end

@interface EILIndoorLocationManager : NSObject

/**
 * The delegate object to receive position update events.
 */
@property (nonatomic, weak, nullable) id <EILIndoorLocationManagerDelegate> delegate;

/**
 * Starts `Indoor Location Manager`.
 *
 * Starting `Indoor Location Manager` early allows it to warm-up and later on deliver without delay `Indoor Location` status change and position updates.
 */
- (void)start;

/**
 * Completely stops `Indoor Location Manager`.
 *
 * Invoking this method will stop all `Indoor Location` monitoring and position updates.
 */
- (void)stop;

/**
 * Informs whether `Indoor Location Manager` is currently running.
 */
@property (nonatomic, assign, readonly) BOOL isRunning;

#pragma mark - Indoor Location Monitoring
///--------------------------------------------------------------------
/// @name Indoor Location Monitoring
///--------------------------------------------------------------------

/**
 * Starts monitoring the specified `Indoor Location` allowing you determine if you are inside or outside monitored location.
 *
 * The current state, i.e., inside/outside, is available on-demand, by calling the `stateForLocation:` method.
 *
 * If the `Indoor Location Manager` is not started this method will start it.
 *
 * Starting monitoring for `Indoor Location` early allows position updates to be delivered without delay later on.
 *
 * Starting monitoring for a location already monitored will do nothing.
 *
 * @param location The `Indoor Location` object that defines the boundary to monitor. This parameter must not be `nil.`
 *
 * @see stopMonitoringForLocation:
 */
- (void)startMonitoringForLocation:(EILLocation *)location;

/**
 * Stops monitoring the specified `Indoor Location`.
 *
 * @param location The `Indoor Location` object currently being monitored. This parameter must not be `nil`. The object you specify need not be the exact same object that you registered, but its identifier or name should be the same.
 *
 * @see startMonitoringForLocation:
 */
- (void)stopMonitoringForLocation:(EILLocation *)location;

/**
 * The set of all monitored `Indoor Location`s.
 */
@property (nonatomic, strong, readonly) NSSet<EILLocation *> *monitoredLocations;

/**
 * Determines state for the monitored location.
 *
 * If the location is not monitored `EILLocationStateUnknown` will be returned.
 *
 * @param location An `EILLocation` object for which state should be determined.
 * @return State in which the monitored location is.
 */
- (EILLocationState)stateForLocation:(EILLocation *)location;

/**
 * Determines state for the monitored location identified by its identifier.
 *
 * Each location saved in Estimote Cloud is given a unique string identifier that corresponds to the `identifier` property of `EILLocation`. You can find it on cloud.estimote.com, on the "Locations" screen, and use it with the Indoor SDK to, among other things, fetch your stored location from Estimote Cloud.
 *
 * If the location is not monitored `EILLocationStateUnknown` will be returned.
 *
 * @param locationIdentifier An identifier of the location for which state should be determined.
 * @return State in which the monitored location is.
 */
- (EILLocationState)stateForLocationWithIdentifier:(NSString *)locationIdentifier;

#pragma mark - Indoor Location Position Updates
///--------------------------------------------------------------------
/// @name Indoor Location Position Updates
///--------------------------------------------------------------------

/**
 * Mode of `EILIndoorLocationManager` position updates delivery.
 *
 * Default mode of `EILIndoorLocationManager` is `EILIndoorLocationManagerModeNormal`.
 *
 * Switching mode while delivery of position updates is in progress will effectively restart position updates with new mode.
 *
 * @see EILIndoorLocationManagerMode
 */
@property (nonatomic, assign) EILIndoorLocationManagerMode mode;

/**
 * Enables providing orientation for position updates in Light mode.
 *
 * Default value is NO.
 *
 * If set to YES, for a brief moment after the start of positioning the orientation may be `EIL_ORIENTATION_UNDEFINED`.
 */
@property (nonatomic, assign) BOOL provideOrientationForLightMode;

/**
 * Supported modes (`EILIndoorLocationManagerMode`) for the device.
 *
 * @return An array of supported modes (`EILIndoorLocationManagerMode`) encoded as `NSNumber *` objects.
 */
+ (NSArray<NSNumber *> *)supportedModes;

/**
 * Starts the delivery of position updates for the specified location.
 *
 * If the `Indoor Location Manager` is not started invoking this method will start it.
 *
 * Only one location is supported at the same time. Calling this method without previously stopping position updates will have no effect.
 *
 * Calling this method without calling start `startMonitoringForLocation:` will result in approximately 6 s delay before first position updates are provided. Starting monitoring earlier will reduce this time by the amount of time monitoring was running.
 *
 * @param location The location.
 */
- (void)startPositionUpdatesForLocation:(EILLocation *)location;

/**
 * Stops the delivery of position updates.
 */
- (void)stopPositionUpdates;

/**
 * If run in Experimental With ARKit positioning mode this property exposes internal ARKit session. For the `EILIndoorLocationManager` to work correctly it should be never started or stopped manually. Please rely on the `startPositionUpdatesForLocation:` and `stopPositionUpdates` methods of `EILIndoorLocationManager`.
 */
@property (nonatomic, strong, readonly) ARSession *arSession NS_AVAILABLE_IOS(11_0);

/**
 * Method for coordinate transformation between ARKit and Indoor Location.
 *
 * @param arkitPoint Position in ARKit coordinate system.
 * @return Position in Indoor Location coordinate system.
 */
- (EILPoint *)indoorLocationPointFromARKitPoint:(EILPoint *)arkitPoint NS_AVAILABLE_IOS(11_0);

/**
 * Method for coordinate transformation between ARKit and Indoor Location.
 *
 * @param indoorLocationPoint Position in Indoor Location coordinate system.
 * @return Position in ARKit coordinate system.
 */
- (EILPoint *)ARKitPointFromIndoorLocationPoint:(EILPoint *)indoorLocationPoint NS_AVAILABLE_IOS(11_0);

@end

NS_ASSUME_NONNULL_END
