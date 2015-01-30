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
