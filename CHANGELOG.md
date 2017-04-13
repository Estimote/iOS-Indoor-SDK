## 2.4.0 (April, 12, 2017)
- Fixed license agreement.
- The SDK will automatically fetch the most up-to-date parameters of the positioning algorithm. This means that there is no need to update the SDK to support newer revisions of beacons hardware.

## 2.3.3.1 (February, 21, 2017)
- Fixed problem with compatibility with Estimote SDK 4.13.1.

## 2.3.3 (February, 9, 2017)
- Fixed a major responsiveness and positioning issue that occurred on iOS 10 devices while navigating inside locations with large number of beacons.

## 2.3.2 (December, 16, 2016)
- Fixed an edge case bug affecting some of the users.

## 2.3.1 (November, 10, 2016)
- Fixed enabling and disabling orientation in Light Mode.

## 2.3.0 (October, 28, 2016)
- Increased Indoor Light navigation mode position granularity, resulting in better accuracy.
- Indoor Light is now more stable when the user is not moving.
- Added information about orientation to Indoor Light.
- Added SpriteKit based EILIndoorLocationScene with built in zoom in/out, rotate and pan gestures handling.

## 2.2.1 (May, 2, 2016)
- Fixed a bug resulting in EILIndoorLocationManager sometimes not providing updates after start.

## 2.2.0 (April, 1, 2016)
- We improved how we detect walking direction. It also improves the accuracy of positioning quite a bit!
- _CAN BREAK BUILD_: We reorganized and updated resources - all possible beacon colors and resolutions are covered now.

## 2.1.0 (February, 3, 2016)
- `EILIndoorLocationManager` can provide position update in two different modes. In addition to normal mode, light mode delivers stable, but a bit less responsive position updates. Has a very low system resource usage.
- In `EILLocationBuilder` beacons can be placed at arbitrary positions.
- Added request for modifying locations in Estimote Cloud.
- Updated resources with all resolutions.

## 2.0.1 (November, 16, 2015)
- Fixed a bug with EILIndoorLocationManager not starting at all, if it was started while the application was in Inactive state.

## 2.0.0 (November, 6, 2015)
- Prefix was changed from EST to EIL.
- Updated dependency to Estimote iOS SDK 3.8.0.
- Using `EILIndoorLocationManager` to provide position updates is separated into three layers now:
  - Use `start` to warm-up `EILIndoorLocationManager` to deliver earlier location states and position updates later on.
  - Use `startMonitoringForLocation:` to enable checking inside-outside location state. You can monitor multiple locations at the same time.
  - Use `startPositionUpdatesForLocation:` to obtain real-time position updates. 
- Mapping tool is no longer present in SDK, use [Estimote Indoor Location app](https://itunes.apple.com/us/app/estimote-indoor-location/id963704810?mt=8) to access most recent version of the mapping tool instead.
- Managing locations in Estimote Cloud is no longer handled by `EILIndoorLocationManager`. Use dedicated request classes. See README for more information.

## 1.6.0 (June, 9, 2015)
- Significant improvements to user orientation within location, making the positioning more accurate and less error prone.
- Generic improvements to ESTIndoorLocationView, giving user more control over location drawing.

## 1.5.0 (May, 26, 2015)
- Added methods for fetching nearby public locations from Estimote Cloud. You can also fetch a single location (your or public) from the cloud by its identifier. For example, if you want to get your hands on the “living-room”, you can now do so without fetching all the locations and filtering the array manually.
- It is now possible to convert the picture coordinates (as seen on the ESTIndoorLocationView, e.g. x=110px, y=50px) to real coordinates (e.g. x=2.2m, y=1m).
- ESTLocationBuilder is now more robust: it provides meaningful errors should something go wrong creating a location.

## 1.4.0 (April, 23, 2015)
- If you're outside a mapped location, the app will detect that much more quickly.
- If your position is off, we’ll recover it much faster when you’re close to the beacons.

## 1.3.0 (April, 10, 2015)
 - Locations can be stored in the cloud.
 - We are now providing accuracy of determined position. IndoorLocationManager delegate method `indoorLocationManager:didUpdatePosition:inLocation:` is now deprecated. Instead of it, use `indoorLocationManager:didUpdatePosition:withAccuracy:inLocation:`. `ESTPositionView.h` was added to provide example usage of determined position accuracy.
 - Added IndoorLocationManager delegate method to tell that delegate is ready and will start updating position (`indoorLocationManagerIsReady:`).
 - Meaningful error codes are provided when IndoorLocationManager fails to update position (described in `ESTIndoorLocationManager.h`).

Please note that iPod is no longer supported due to absence of magnetometer.

## 1.2.1 (March 17, 2015)
 - The Estimote Indoor SDK now works better in large locations.

## 1.2.0 (March 3, 2015)

 - Major improvements in user's orientation within location. Orientation in position reported via  [ESTIndoorLocationManagerDelegate indoorLocationManager:didUpdatePosition:inLocation:] is less error-prone and more responsive to user's rotation.
 - Updated dependency to Estimote iOS SDK 2.4.0.

## 1.1.2 (January 30, 2015)

 - Removing warnings during linking.

## 1.1.1 (January 22, 2015)

 - Bugfix release.

## 1.1.0 (January 21, 2015)

 - Improvements to accuracy and stability of localisation.
 - Greater responsiveness for 32-bit devices (iPhone 5C and older)
 - New functionality in ESTIndoorLocationView: helper methods to calculate view coordinates based on real coordinates, cropping view to rectangular region of interest
 - _CAN BREAK BUILD_: change in way of setting up appID and appToken. Use `[ESTConfig setupAppID:andAppToken:]` instead of `[ESTIndoorLocationManager setupAppID:andAppToken:]`. 
 - _CAN BREAK BUILD_: change in Estimote SDK version dependency (2.3.2)
 - _CAN BREAK BUILD_: new requirement for the library. Application needs to add `-lc++` to Other Linker Flags (project's Build Settings).

## 1.0.0 (September 23, 2014)

First version.
