// Copyright (c) 2017 Estimote. All rights reserved.

/** Version of this iOS Indoor Location SDK. */
#define EIL_IOS_INDOOR_SDK_VERSION_STRING @"2.7.1"


/** Library header, import this to import all of the public types in the Indoor SDK. */

// Main interface for Indoor SDK.
#import "EILIndoorLocationManager.h"

// Position updates in background.
#import "EILBackgroundIndoorLocationManager.h"

// Location data structures.
#import "EILPoint.h"
#import "EILOrientedPoint.h"
#import "EILOrientedLineSegment.h"
#import "EILLocationLinearObject.h"
#import "EILPositionedBeacon.h"
#import "EILLocation.h"

// Manually building location.
#import "EILLocationBuilder.h"

// UI.
#import "EILIndoorLocationScene.h"
#import "EILIndoorLocationView.h"
#import "EILPositionView.h"

// Cloud communication
#import "EILRequestAddLocation.h"
#import "EILRequestFetchLocation.h"
#import "EILRequestFetchLocations.h"
#import "EILRequestFetchPublicLocations.h"
#import "EILRequestRemoveLocation.h"
#import "EILRequestModifyLocation.h"
