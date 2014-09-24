//  Copyright (c) 2014 Estimote Inc. All rights reserved.

#import "ESTLocation.h"
#import "ESTIndoorLocationView.h"

@interface ESTIndoorLocationViewController : UIViewController

@property (nonatomic, strong) IBOutlet ESTIndoorLocationView *indoorLocationView;
@property (nonatomic, strong) IBOutlet UISwitch *showTraceSwitch;
@property (nonatomic, strong) IBOutlet UISwitch *rotateOnUpdateSwitch;

@property (nonatomic, strong) IBOutlet UILabel *positionLabel;

- (instancetype)initWithLocation:(ESTLocation *)location;

@end
