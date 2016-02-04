// Copyright (c) 2015 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "EILIndoorLocationManager.h"

NS_ASSUME_NONNULL_BEGIN

/** 
 * View representing current position indicator with accuracy circle. 
 * It adjusts itself to always show correctly accuracy in scale.
 */
@interface EILPositionView : UIImageView

/** 
 * Returns an initialized EILPositionView object for given location and size of superview.
 *
 * @param location The location for which the position is visualized.
 * @param showAccuracyCircle If YES then in addition to avatar, accuracy circle will be displayed.
 * @param bounds Bounds of Indoor LocationView, used to calculate scale for drawing avatar.
 * @return An initialized EILPositionView object.
 */
- (instancetype)initWithImage:(UIImage *)image
                     location:(EILLocation *)location
           showAccuracyCircle:(BOOL)showAccuracyCircle
            forViewWithBounds:(CGRect)bounds;

/** 
 * Returns an initialized EILPositionView object for given location and size of superview.
 *
 * @param location The location for which the position is visualized.
 * @param regionOfInterest Region of interest to be drawn for the location.
 * @param showAccuracyCircle If YES then in addition to avatar, accuracy circle will be displayed.
 * @param bounds Bounds of Indoor LocationView, used to calculate scale for drawing avatar.
 * @return An initialized EILPositionView object.
 */
- (instancetype)initWithImage:(UIImage *)image
                     location:(EILLocation *)location
           showAccuracyCircle:(BOOL)showAccuracyCircle
             regionOfInterest:(CGRect)regionOfInterest
            forViewWithBounds:(CGRect)bounds;

/**
 * Updates accuracy value.
 */
- (void)updateAccuracy:(EILPositionAccuracy)accuracy;

@end

NS_ASSUME_NONNULL_END
