// Copyright (c) 2015 Estimote. All rights reserved.

#import <UIKit/UIKit.h>
#import "ESTIndoorLocationManager.h"


/** 
 * View representing current position indicator with accuracy circle. 
 * It adjusts itself to always show correctly accuracy in scale.
 */
@interface ESTPositionView : UIImageView

/** 
 * Returns an initialized ESTPositionView object for given location and size of superview.
 *
 * @param location The location for which the position is visualized.
 * @param bounds Bounds of superview.
 * @return An initialized ESTPositionView object.
 */
- (instancetype)initWithImage:(UIImage *)image location:(ESTLocation *)location forViewWithBounds:(CGRect)bounds;

/** 
 * Returns an initialized ESTPositionView object for given location and size of superview.
 *
 * @param location The location for which the position is visualized.
 * @param regionOfInterest Region of interest to be drawn for the location.
 * @param bounds Bounds of superview.
 * @return An initialized ESTPositionView object.
 */
- (instancetype)initWithImage:(UIImage *)image location:(ESTLocation *)location regionOfInterest:(CGRect)regionOfInterest forViewWithBounds:(CGRect)bounds;

/** Updates accuracy value. */
- (void)updateAccuracy:(ESTPositionAccuracy)accuracy;

@end
