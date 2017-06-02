//  Copyright © 2016 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import "EILIndoorLocationManager.h"

NS_ASSUME_NONNULL_BEGIN

@class EILBackgroundIndoorLocationManager;

/**
 * The `EILBackgroundIndoorLocationManagerDelegate` protocol defines the methods to receive location updates in background.
 */
@protocol EILBackgroundIndoorLocationManagerDelegate <NSObject>

@optional

/**
 * Tells the delegate that new position update is available.
 *
 * @param locationManager The manager object that generated the event.
 * @param position The position inside the location.
 * @param positionAccuracy The accuracy of the determined position.
 * @param location The location for which the position was updated.
 */
- (void)backgroundIndoorLocationManager:(EILBackgroundIndoorLocationManager *)locationManager
                      didUpdatePosition:(EILOrientedPoint *)position
                           withAccuracy:(EILPositionAccuracy)positionAccuracy
                             inLocation:(EILLocation *)location;

/**
 * Tells the delegate that position update could not be determined.
 *
 * @param locationManager The locationManager object that generated the event.
 * @param error The error object containing information why position could not be determined.
 */
- (void)backgroundIndoorLocationManager:(EILBackgroundIndoorLocationManager *)locationManager
       didFailToUpdatePositionWithError:(NSError *)error;

@end

/**
 * Background Indoor Location Manager class provides position updates in background.
 *
 * In order to relaunch the application (if it is killed by operating system or user) as the user enters the location "Always in use" Location Services authorization is required.
 *
 * Please note that when the application is relaunched in background no UI code is executed. All the logic regarding positioning in background should be executed in the App Delegate including recreating an instance of EILBackgroundIndoorLocationManager.
 *
 * @see requestAlwaysAuthorization
 */
@interface EILBackgroundIndoorLocationManager : NSObject

/**
 * The delegate object to receive position update events.
 */
@property (nonatomic, weak, nullable) id <EILBackgroundIndoorLocationManagerDelegate> delegate;

/**
 * Requests permission to use location services whenever the app is running.
 *
 * "Always in use" Location Services authorization is required for the background manager to be able to relaunch the app, if it is killed by operating system or user.
 *
 * For more details about the location services authorization model please refer to the CoreLocation documentation.
 *
 * For best UX patterns for requesting permission please refer to the following blog post: http://blog.estimote.com/post/144805191465/how-to-ask-users-for-permission-to-use-location
 *
 * @see -[CLLocationManager requestWhenInUseAuthorization]
 */
- (void)requestAlwaysAuthorization;

/**
 * Starts `Background Indoor Location Manager`.
 *
 * Starting `Background Indoor Location Manager` early allows it to warm-up and later on deliver without delay `Indoor Location` status change and position updates.
 */
- (void)start;

/**
 * Completely stops `Background Indoor Location Manager`.
 *
 * Invoking this method will stop all `Indoor Location` monitoring and position updates.
 */
- (void)stop;

/**
 * Informs whether `Background Indoor Location Manager` is currently running.
 */
@property (nonatomic, assign, readonly) BOOL isRunning;

#pragma mark - Indoor Location Monitoring
///--------------------------------------------------------------------
/// @name Indoor Location Monitoring
///--------------------------------------------------------------------

/**
 * Starts monitoring the specified `Indoor Location` allowing you determine if you are inside or outside monitored location.
 *
 * To function properly Background Location Manager requires "Always in use" Location Services authorization.
 *
 * The current state, i.e., inside/outside, is available on-demand, by calling the `stateForLocation:` method.
 *
 * If the `Background Indoor Location Manager` is not started this method will start it.
 *
 * Starting monitoring for `Indoor Location` early allows position updates to be delivered without delay later on.
 *
 * Starting monitoring for a location already monitored will do nothing.
 *
 * @param location The `Indoor Location` object that defines the boundary to monitor.
 *
 * @see stopMonitoringForLocation:
 * @see requestAlwaysAuthorization
 */
- (void)startMonitoringForLocation:(EILLocation *)location;

/**
 * Stops monitoring the specified `Indoor Location`.
 *
 * @param location The `Indoor Location` object currently being monitored. The object you specify need not be the exact same object that you registered, but its identifier or name should be the same.
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
 * Starts the delivery of position updates for the specified location.
 *
 * To function properly Background Location Manager requires "Always in use" Location Services authorization.
 *
 * If the `Background Indoor Location Manager` is not started invoking this method will start it.
 *
 * Calling this method without calling start `startMonitoringForLocation:` will result in approximately 6 s delay before first position updates are provided. Starting monitoring earlier will reduce this time by the amount of time monitoring was running.
 *
 * @param location The location.
 * @see requestAlwaysAuthorization
 */
- (void)startPositionUpdatesForLocation:(EILLocation *)location;

/**
 * Stops the delivery of position updates for the specified location.
 *
 * @param location The location.
 */
- (void)stopPositionUpdatesForLocation:(EILLocation *)location;

/**
 * Stops the delivery of position updates.
 */
- (void)stopPositionUpdates;


@end

NS_ASSUME_NONNULL_END
