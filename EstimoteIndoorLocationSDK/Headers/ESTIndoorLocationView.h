//  Copyright (c) 2014 Estimote. All rights reserved.

#import <UIKit/UIKit.h>

@class ESTLocation;
@class ESTPoint;
@class ESTOrientedPoint;

/**
 * Width of the border around location shape.
 * Non-zero value is needed for objects like beacons
 * to be rendered inside view.
 */
static const int kShapeLayerMargin = 20;

#ifdef IB_DESIGNABLE
IB_DESIGNABLE
#endif

/**
 * A view for drawing ESTLocation and user position within it.
 */
@interface ESTIndoorLocationView : UIView

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** `ESTLocation` object to be drawn. */
@property (nonatomic, strong, readonly) ESTLocation *location;

/** If YES, then a trace will be displayed. */
@property (nonatomic, assign) BOOL showTrace;

/** If YES. then the view will be rotated so the position indicator will always be pointing up. */
@property (nonatomic, assign) BOOL rotateOnPositionUpdate;

/** Determines if location was drawn successfully. */
@property (nonatomic, assign, readonly) BOOL locationDrawn;

#pragma mark Styling properties
///-----------------------------------------
/// @name Styling properties
///-----------------------------------------

/** View representing current position indicator. */
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

#pragma mark Drawing location
///-----------------------------------------
/// @name Drawing location
///-----------------------------------------

/**
 * Draws a graphical representation of `ESTLocation` object.
 *
 * @param location Object representing current location.
 */
- (void)drawLocation:(ESTLocation *)location;

/**
 * Draws a graphical representation of `ESTLocation` object
 * cropped to only include things explicitly inside the chosen
 * region (defined by bounding box).
 *
 * @param location Object representing current location.
 * @param regionOfInterest Region of interest to be drawn
 */
- (void)drawLocation:(ESTLocation *)location
  inRegionOfInterest:(CGRect)regionOfInterest;

#pragma mark Handling position updates
///-----------------------------------------
/// @name Handling position updates
///-----------------------------------------

/**
 * Updates current position indicator to the given position. If position is nil, indicator is hidden.
 * Will throw an exception if called without first calling `drawLocation:`.
 *
 * @param position Object representing current position in the location.
 */
- (void)updatePosition:(ESTOrientedPoint *)position;

#pragma mark Drawing trace
///-----------------------------------------
/// @name Drawing trace
///-----------------------------------------

/**
 * Clears the trace.
 *
 * Will throw an exception if called without first calling `drawLocation:`.
 */
- (void)clearTrace;

#pragma mark Drawing user objects
///-----------------------------------------
/// @name Drawing user objects
///-----------------------------------------

/**
 * Draws a view that represents a real object at given position.
 *
 * Will throw an exception if called without first calling `drawLocation:`.
 *
 * @param  object View representing a real object. Cannot be nil.
 * @param  position Object representing position in the location. Cannot be nil.
 */
- (void)drawObject:(UIView *)object
      withPosition:(ESTPoint *)position __attribute__((deprecated(("Use drawObjectInBackground:withPosition:identifier: and drawObjectInForeground:withPosition:identifier: instead"))));

/**
 * Draws a view that represents a real object at given position in background.
 *
 * Background objects are drawn in order of addition below all other views.
 * Object will be rotated with regard to location to match orientation of the position.
 * Will throw an exception if called without first calling `drawLocation:`.
 *
 * @param object View representing a real object. Cannot be nil.
 * @param position Object representing position in the location. Cannot be nil.
 * @param identifier Unique identifier by which view will be identified. Cannot be nil.
 */
- (void)drawObjectInBackground:(UIView *)object
                  withPosition:(ESTOrientedPoint *)position
                    identifier:(NSString *)identifier;

/**
 * Draws a view that represents a real object at given position in foreground.
 *
 * Foreground objects are drawn in order of addition on top of background objects,
 * location and trace, but below position view. Object will be rotated with
 * regard to location to match orientation of the position.
 * Will throw an exception if called without first calling `drawLocation:`.
 *
 * @param object View representing a real object. Cannot be nil.
 * @param position Object representing position in the location. Cannot be nil.
 * @param identifier Unique identifier by which view will be identified. Cannot be nil.
 */
- (void)drawObjectInForeground:(UIView *)object
                  withPosition:(ESTOrientedPoint *)position
                    identifier:(NSString *)identifier;

/**
 * Moves an object identified by identifier to a given position.
 *
 * Object will be be rotated with regard to location to match orientation of the position.
 * If animated is set to true, the transition will be animated with 0.1 s duration.
 * Will throw an exception, if there is no view with corresponding identifier.
 *
 * @param identifier Unique identifier by which view will be identified. Cannot be nil.
 * @param position Object representing position in the location. Cannot be nil.
 * @param animated Whether transition should be animated.
 */
- (void)moveObjectWithIdentifier:(NSString *)identifier
                      toPosition:(ESTOrientedPoint *)position
                        animated:(BOOL)animated;

/**
 * Removes an object identified by identifier from the view.
 *
 * Will throw an exception, if there is no view with corresponding identifier.
 *
 * @param identifier Unique identifier by which view will be identified. Cannot be nil.
 */
- (void)removeObjectWithIdentifier:(NSString *)identifier;

#pragma mark Real to image coordinate calculations
///-----------------------------------------
/// @name Real to image coordinate calculations
///-----------------------------------------

/**
 * Calculates X in view coordinate system from X in physical coordinate system.
 *
 * @param realX X coordinate in physical coordinate system (in meters).
 *
 * @return X coordinate in view coordinate system (in pixels).
 */
- (CGFloat)calculatePictureCoordinateForRealX:(double)realX;

/**
 * Calculates Y in view coordinate system from Y in physical coordinate system.
 *
 * @param realY Y coordinate in physical coordinate system (in meters).
 *
 * @return Y coordinate in view coordinate system (in pixels).
 */
- (CGFloat)calculatePictureCoordinateForRealY:(double)realY;

/**
 * Calculates point in view coordinate system from point in physical coordinate system.
 *
 * @param realPoint Point with coordinates in physical coordinate system (in meters).
 *
 * @return Point with coordinates in view coordinate system (in pixels).
 */
- (CGPoint)calculatePicturePointFromRealPoint:(ESTPoint *)realPoint;

/**
 * Calculates X in physical coordinate system from X in view coordinate system.
 *
 * @param realX X coordinate in view coordinate system (in pixels).
 *
 * @return X coordinate in physical coordinate system (in meters).
 */
- (double)calculateRealCoordinateForPictureX:(CGFloat)pictureX;

/**
 * Calculates Y in physical coordinate system from T in view coordinate system.
 *
 * @param realY Y coordinate in view coordinate system (in pixels).
 *
 * @return Y coordinate in physical coordinate system (in meters).
 */
- (double)calculateRealCoordinateForPictureY:(CGFloat)pictureY;

/**
 * Calculates point in physical coordinate system from point in view coordinate system.
 *
 * @param realPoint Point with coordinates in view coordinate system (in pixels).
 *
 * @return Point with coordinates in physical coordinate system (in meters).
 */
- (ESTPoint *)calculateRealPointFromPicturePoint:(CGPoint)picturePoint;

@end
