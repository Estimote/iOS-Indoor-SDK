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
