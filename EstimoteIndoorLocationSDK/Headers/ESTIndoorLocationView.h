//  Copyright (c) 2014 Estimote. All rights reserved.

#import <UIKit/UIKit.h>
#import "ESTLocation.h"

#ifdef IB_DESIGNABLE
IB_DESIGNABLE
#endif

/** A simple view for drawing ESTLocation and position within it. */
@interface ESTIndoorLocationView : UIView

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** `ESTLocation` object to be drawn. */
@property (nonatomic, strong, readonly) ESTLocation *location;

/** If YES then a trace will be displayed. */
@property (nonatomic, assign) BOOL showTrace;

/** If YES then the view will be rotated so the position indicator will always be pointing up. */
@property (nonatomic, assign) BOOL rotateOnPositionUpdate;

/** Determines if location was drawn successfully. */
@property (nonatomic, assign, readonly) BOOL locationDrawn;

#pragma mark Styling properties
///-----------------------------------------
/// @name Styling properties
///-----------------------------------------

/** View representing current position indicator */
@property (nonatomic, strong) UIView    *positionView;

/** Image used as current position indicator. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, strong) IBInspectable UIImage   *positionImage;
#else
@property (nonatomic, strong) UIImage   *positionImage;
#endif

/** Color of the location boundary. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, strong) IBInspectable UIColor   *locationBorderColor;
#else
@property (nonatomic, strong) UIColor   *locationBorderColor;
#endif

/** Thickness of the location boundary. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, assign) IBInspectable NSInteger locationBorderThickness;
#else
@property (nonatomic, assign) NSInteger locationBorderThickness;
#endif

/** Color of the location door. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, strong) IBInspectable UIColor   *doorColor;
#else
@property (nonatomic, strong) UIColor   *doorColor;
#endif

/** Thickness of the location door. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, assign) IBInspectable NSInteger doorThickness;
#else
@property (nonatomic, assign) NSInteger doorThickness;
#endif

/** Color of the location window. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, strong) IBInspectable UIColor   *windowColor;
#else
@property (nonatomic, strong) UIColor   *windowColor;
#endif

/** Thickness of the location window. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, assign) IBInspectable NSInteger windowThickness;
#else
@property (nonatomic, assign) NSInteger windowThickness;
#endif

/** Color of the location trace. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, strong) IBInspectable UIColor   *traceColor;
#else
@property (nonatomic, strong) UIColor   *traceColor;
#endif

/** Thickness of the trace. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, assign) IBInspectable NSInteger traceThickness;
#else
@property (nonatomic, assign) NSInteger traceThickness;
#endif

/** Color of the wall length labels. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, strong) IBInspectable UIColor   *wallLengthLabelsColor;
#else
@property (nonatomic, strong) UIColor   *wallLengthLabelsColor;
#endif

/** If YES then wall length labels will be displayed. */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 80000
@property (nonatomic, assign) IBInspectable BOOL showWallLengthLabels;
#else
@property (nonatomic, assign) BOOL showWallLengthLabels;
#endif

#pragma mark Drawing
///-----------------------------------------
/// @name Drawing
///-----------------------------------------

/**
* Draws a graphical representation of `ESTLocation` object.
*
* @param location Object representing current location.
*/
- (void)drawLocation:(ESTLocation *)location;

/**
 * Draws a view that represets a real object at given position.
 *
 * @param  object View representing a real object.
 * @param  position Object representing position in the location.
 */
- (void)drawObject:(UIView *)object withPosition:(ESTPoint *)position;

/**
 * Updates current position indicator to the given position. If position is nil, indicator is hidden.
 * Will throw an exception if called without first calling `drawLocation:`.
 *
 * @param position Object representing current position in the location.
 */
- (void)updatePosition:(ESTOrientedPoint *)position;

/**
 * Clears the trace.
 * Will throw an exception if called without first calling `drawLocation:`.
 */
- (void)clearTrace;

@end
