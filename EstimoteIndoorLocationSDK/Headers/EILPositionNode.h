//  Copyright © 2016 Estimote. All rights reserved.

#import <SpriteKit/SpriteKit.h>
#import "EILIndoorLocationManager.h"

/**
 *  Name of the node that represents accuracy of position estimation.
 *  @see showAccuracy
 *  @see updateAccuracy:
 */
static NSString * const EILPositionNodeAccuracyNodeName = @"ACCURACY";

/**
 *  A subclass of SKSpriteNode designed to represent user avatar together with accuracy circle.
 *  Accuracy circle makes it easy to visualy mark the possible position estimation error.
 */
@interface EILPositionNode : SKSpriteNode

/** 
 *  If YES, then accuracy circle is displayed.
 *  @see EILPositionNodeAccuracyNodeName
 */
@property (nonatomic, assign) BOOL showAccuracy;

/** 
 *  Updates accuracy circle according to accuracy value.
 *  
 *  @param accuracy Accuracy of position estimation in scene scale.
 *  @see `locationScale` in `EILIndoorLocationScene`
 */
- (void)updateAccuracy:(CGFloat)accuracy;

@end
