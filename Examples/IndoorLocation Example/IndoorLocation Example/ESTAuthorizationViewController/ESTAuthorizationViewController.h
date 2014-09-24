//  Copyright (c) 2014 Estimote. All rights reserved.

#import <UIKit/UIKit.h>
#import "ESTBeacon.h"

@interface ESTAuthorizationViewController : UIViewController

- (instancetype)initWithCompletion:(void (^)(NSError *error))completion;

@end
