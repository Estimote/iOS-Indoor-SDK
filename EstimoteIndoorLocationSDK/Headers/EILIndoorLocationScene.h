//  Copyright © 2016 Estimote. All rights reserved.

#import <SpriteKit/SpriteKit.h>

@class EILLocation;
@class EILOrientedPoint;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Name of the node that represents user position.
 *  User position is represented using `EILPositionNode`.
 */
static NSString * const EILIndoorLocationSceneUserNodeName = @"USER";

/**
 *  Name of the node that represesnts trace.
 *  Trace is represented by a dashed line that is updated after each position update.
 *  Trace makes it easy to see the path that user took while moving inside location.
 *  @see showTrace
 */
static NSString * const EILIndoorLocationSceneTraceNodeName = @"TRACE";

/**
 *  Name of the node that represents location shape.
 */
static NSString * const EILIndoorLocationSceneShapeNodeName = @"SHAPE";

/**
 *  Name of the node that represesnts background image.
 */
static NSString * const EILIndoorLocationSceneBackgroundImageNodeName = @"BACKGROUND_IMAGE";

/**
 *  Name of the node that represents the center button which centers the camera on user node.
 *  @see centerOnUser
 */
static NSString * const EILIndoorLocationSceneCenterUserButtonNodeName = @"CENTER_USER";

/**
 *  Name of the node that represents the compass button that changes the property that makes the location or avatar rotate on position update.
 *  @see rotateLocationOnPositionUpdate
 */
static NSString * const EILIndoorLocationSceneCompassButtonNodeName = @"COMPASS";

/**
 *  Default lindeWidth value of shape node that represents location border.
 *  @see locationBorderThickness
 *  @see EILIndoorLocationSceneShapeNodeName
 */
static const CGFloat EILIndoorLocationSceneDefaultLocationBorderThickness = 0.5;

/**
 *  Default lineWidth property value of shape nodes that represent linear objects of type EILLocationLinearObjectTypeWindow.
 *  @see windowThickness
 */
static const CGFloat EILIndoorLocationSceneDefaultWindowThickness = 0.7;

/**
 *  Default lineWidth property value of shape nodes that represent linear objects of type EILLocationLinearObjectTypeDoor.
 *  @see doorThickness
 */
static const CGFloat EILIndoorLocationSceneDefaultDoorThickness = 0.7;

/**
 *  Default lineWidth property value of shape node that represents trace.
 *  @see traceThickness
 *  @see EILIndoorLocationSceneTraceNodeName
 */
static const CGFloat EILIndoorLocationSceneDefaultTraceThickness = 0.6;

/**
 *  Default size property value of node that represents user location.
 *  @see EILIndoorLocationSceneUserNodeName
 */
static const CGSize EILIndoorLocationSceneDefaultAvatarSize = {32,32};

/**
 *  Default size property value of sprite nodes that represent beacons.
 *  @see beaconSize
 */
static const CGSize EILIndoorLocationSceneDefaultBeaconSize = {18,28};

/**
 *  Defines z axis position where default nodes are and where user defined nodes should be placed.
 *  User defined nodes should be placed on Foreground or Background positions.
 *
 *  @see EILIndoorLocationSceneUserNodeName
 *  @see EILIndoorLocationSceneTraceNodeName
 *  @see EILIndoorLocationSceneShapeNodeName
 *  @see EILIndoorLocationSceneBackgroundImageNodeName
 */
typedef enum : NSInteger {
    EILIndoorLocationSceneZPositionBackground = -10,
    EILIndoorLocationSceneZPositionLocationShape = 0,
    EILIndoorLocationSceneZPositionTrace = 20,
    EILIndoorLocationSceneZPositionForeground = 30,
    EILIndoorLocationSceneZPositionBeacons = 40,
    EILIndoorLocationSceneZPositionAvatar = 50
} EILIndoorLocationSceneZPosition;

/**
 *  A subclass of SKScene designed to draw EILLocation and user position inside it.
 *  Provides a build in mechanism for handling zoom in/out, rotation and pan gestures.
 */
@interface EILIndoorLocationScene : SKScene

#pragma mark Properties
///-----------------------------------------
/// @name Properties
///-----------------------------------------

/** Currently presented `EILLocation` object. */
@property (nonatomic, strong, readonly, nullable) EILLocation *location;

/**
 *  If YES, then a beacons will be displayed.
 *  Default: YES.
 */
@property (nonatomic, assign) BOOL showBeacons;

/**
 *  If YES, then a trace will be displayed.
 *  Default: NO.
 *  @see EILIndoorLocationSceneTraceNodeName
 */
@property (nonatomic, assign) BOOL showTrace;

/**
 *  If YES, then the location will be rotated with position updates making the position indicator always point up.
 *  If NO, then the position indicator will rotate together with position updates leaving the location unrotated.
 *  Changes after touching compass button.
 *  Default: NO.
 *  @see EILIndoorLocationSceneCompassButtonNodeName
 */
@property (nonatomic, assign) BOOL rotateLocationOnPositionUpdate;

/**
 *  Value calculated after calling `drawLocation:`. 
 *  Factor by which every location coordinate is multiplied before drawing.
 *  Value doesn't change while zooming in/out.
 *
 *  Use it to transform scene coordinates to real coordinates.
 *  sceneCoordinate = realCoordinate * locationScale
 *  realCoordinate = sceneCoordinate / locationScale
 */
@property (nonatomic, assign, readonly) CGFloat locationScale;

/**
 * Length of the move animation duration.
 */
@property (nonatomic, assign) double moveAnimationDuration;

/**
 *  Block of code that will be invoked every time a node on `EILIndoorLocationScene` is touched.
 *  @param nodeName Name of node that was touched.
 */
@property (nonatomic, copy, nullable) void (^touchHandler)(NSString *nodeName);

#pragma mark Styling properties
///-----------------------------------------
/// @name Styling properties
///-----------------------------------------

/**
 *  Name of the image asset that should be used as an avatar.
 *  Avatar node will be recreated after each change of this property.
 *  @see EILIndoorLocationSceneUserNodeName
 */
@property (nonatomic, strong, nullable) NSString *avatarImageName;

/**
 *  Name of the image asset that should be used as a background.
 *  It will be resized to fit location size.
 *  If background image represents a floorplan it shouldn't contain any margins to fit properly.
 *  Background node will be recreated after each change of this property.
 *  @see EILIndoorLocationSceneBackgroundImageNodeName
 */
@property (nonatomic, strong, nullable) NSString *backgroundImageName;

/**
 *  Name of the image asset that should be used as a center user button.
 *  Center user button node will be recreated after each change of this property.
 *  @see EILIndoorLocationSceneCenterUserButtonNodeName
 */
@property (nonatomic, strong, nullable) NSString *centerUserButtonImageName;

/**
 *  Name of the image asset that should be used as a compass button.
 *  Compass button node will be recreated after each change of this property.
 *  @see EILIndoorLocationSceneCompassButtonNodeName
 */
@property (nonatomic, strong, nullable) NSString *compassButtonImageName;

/**
 *  strokeColor property value of the shape node that represents location border.
 *  Default: Black.
 *  @see EILIndoorLocationSceneShapeNodeName
 */
@property (nonatomic, strong) UIColor *locationBorderColor;

/**
 *  lindeWidth property value of the shape node that represents location border.
 *  @see EILIndoorLocationSceneDefaultLocationBorderThickness
 *  @see EILIndoorLocationSceneShapeNodeName
 */
@property (nonatomic, assign) CGFloat locationBorderThickness;

/**
 *  strokeColor property value of the shape nodes that represent linear objects of type `EILLocationLinearObjectTypeWindow`.
 *  Default: Blue.
 */
@property (nonatomic, strong) UIColor *windowColor;

/**
 *  lindeWidth property value of the shape nodes that represent linear objects of type `EILLocationLinearObjectTypeWindow`.
 *  @see EILIndoorLocationSceneDefaultWindowThickness
 */
@property (nonatomic, assign) CGFloat windowThickness;

/**
 *  strokeColor property value of the shape nodes that represent linear objects of type `EILLocationLinearObjectTypeDoor`.
 *  Default: White.
 */
@property (nonatomic, strong) UIColor *doorColor;

/**
 *  lindeWidth property value of the shape nodes that represent linear objects of type `EILLocationLinearObjectTypeDoor`.
 *  @see EILIndoorLocationSceneDefaultDoorThickness
 */
@property (nonatomic, assign) CGFloat doorThickness;

/**
 *  strokeColor property value of the shape node that represesnts trace.
 *  Default: Yellow.
 *  @see EILIndoorLocationSceneTraceNodeName
 */
@property (nonatomic, strong) UIColor *traceColor;

/**
 *  lineWidth property value of the shape node that represents trace.
 *  @see EILIndoorLocationSceneDefaultTraceThickness
 *  @see EILIndoorLocationSceneTraceNodeName
 */
@property (nonatomic, assign) CGFloat traceThickness;

/**
 *  size property value of the sprite nodes that represent beacons.
 *  If this value is supposed to be different than default, set it before calling `drawLocation:`.
 *  @see EILIndoorLocationSceneDefaultBeaconSize
 */
@property (nonatomic, assign) CGSize beaconSize;

#pragma mark Drawing location
///-----------------------------------------
/// @name Drawing location
///-----------------------------------------

/**
 *  Draws a graphical representation of `EILLocation` object.
 *
 *  @param location Object representing current location.
 */
- (void)drawLocation:(EILLocation *)location;

#pragma mark Handling position updates
///-----------------------------------------
/// @name Handling position updates
///-----------------------------------------

/**
 *  Updates avatar position to the given position. 
 *  If position is nil, avatar node is removed from scene.
 *  Sets `showAccuracy` to YES on `EILPositionNode` class object that represents avatar.
 *
 *  @see EILIndoorLocationSceneUserNodeName
 *  @param position Object representing current position in the location.
 *  @param accuracy Value describing accuracy of position estimation. Calls `updateAccuracy:` on `EILPositionNode` class object that represents avatar.
 */
- (void)updateUserPosition:(nullable EILOrientedPoint *)position withAccuracy:(CGFloat)accuracy;

/**
 *  Updates avatar position to the given position.
 *  If position is nil, avatar node is removed from scene.
 *  Sets `showAccuracy` to NO on `EILPositionNode` class object that represents avatar.
 *
 *  @see EILIndoorLocationSceneUserNodeName
 *  @param position Object representing current position in the location.
 */
- (void)updateUserPosition:(nullable EILOrientedPoint *)position;

/**
 *  Sets camera property position to current position of avatar node in an animated way.
 *  Called after touching center user button.
 *  @see EILIndoorLocationSceneCenterUserButtonNodeName
 *  @see EILIndoorLocationSceneUserNodeName
 */
- (void)centerOnUser;

#pragma mark Drawing trace
///-----------------------------------------
/// @name Drawing trace
///-----------------------------------------

/** 
 *  Clears the trace by removing trace node. 
 *  @see EILIndoorLocationSceneTraceNodeName
 */
- (void)clearTrace;

@end

NS_ASSUME_NONNULL_END
