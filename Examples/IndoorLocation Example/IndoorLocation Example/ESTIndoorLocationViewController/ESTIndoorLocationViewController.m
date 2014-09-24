//  Copyright (c) 2014 Estimote Inc. All rights reserved.

#import "ESTIndoorLocationViewController.h"
#import "ESTIndoorLocationManager.h"
#import "ESTIndoorLocationView.h"

@interface ESTIndoorLocationViewController () <ESTIndoorLocationManagerDelegate>

@property (nonatomic, strong) ESTIndoorLocationManager *manager;
@property (nonatomic, strong) ESTLocation *location;

@end

@implementation ESTIndoorLocationViewController

- (instancetype)initWithLocation:(ESTLocation *)location
{
    self = [super init];
    if (self)
    {
        self.manager = [[ESTIndoorLocationManager alloc] init];
        self.manager.delegate = self;
        
        self.location = location;
    }
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = self.location.name;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    self.indoorLocationView.backgroundColor = [UIColor clearColor];
    
    self.indoorLocationView.showTrace               = self.showTraceSwitch.isOn;
    self.indoorLocationView.rotateOnPositionUpdate  = self.rotateOnUpdateSwitch.isOn;
    
    self.indoorLocationView.showWallLengthLabels    = YES;
    
    self.indoorLocationView.locationBorderColor     = [UIColor blackColor];
    self.indoorLocationView.locationBorderThickness = 4;
    self.indoorLocationView.doorColor               = [UIColor brownColor];
    self.indoorLocationView.doorThickness           = 6;
    self.indoorLocationView.traceColor              = [UIColor blueColor];
    self.indoorLocationView.traceThickness          = 2;
    self.indoorLocationView.wallLengthLabelsColor   = [UIColor blackColor];
    
    [self.indoorLocationView drawLocation:self.location];
    
    // You can change the avatar using positionImage property of ESTIndoorLocationView class.
    // self.indoorLocationView.positionImage = [UIImage imageNamed:@"name_of_your_image"];
    
    [self.manager startIndoorLocation:self.location];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.manager stopIndoorLocation];
    [super viewWillDisappear:animated];
}

#pragma mark - UISwitch events

- (IBAction)showTraceSwitchChanged:(id)sender
{
    [self.indoorLocationView clearTrace];
    self.indoorLocationView.showTrace = self.showTraceSwitch.isOn;
}

- (IBAction)rotateOnUpdateSwitchChanged:(id)sender
{
    self.indoorLocationView.rotateOnPositionUpdate = self.rotateOnUpdateSwitch.isOn;
}

#pragma mark - ESTIndoorLocationManager delegate

- (void)indoorLocationManager:(ESTIndoorLocationManager *)manager
            didUpdatePosition:(ESTOrientedPoint *)position
                   inLocation:(ESTLocation *)location
{
    self.positionLabel.text = [NSString stringWithFormat:@"x: %.2f  y: %.2f   α: %.2f",
                               position.x,
                               position.y,
                               position.orientation];
    
    [self.indoorLocationView updatePosition:position];
}

- (void)indoorLocationManager:(ESTIndoorLocationManager *)manager didFailToUpdatePositionWithError:(NSError *)error
{
    self.positionLabel.text = @"It seems you are outside the location.";
    NSLog(@"%@", error.localizedDescription);
}

@end
