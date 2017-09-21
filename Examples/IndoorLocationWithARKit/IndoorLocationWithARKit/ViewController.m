#import "ViewController.h"
#import <EstimoteSDK/EstimoteSDK.h>
#import "EILIndoorSDK.h"

@interface ViewController () <EILIndoorLocationManagerDelegate>

@property (nonatomic, strong) EILIndoorLocationManager *indoorLocationManager;
@property (nonatomic, strong) EILLocation *location;

@property (nonatomic, strong) EILIndoorLocationView *locationView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // TODO: put your App ID and App Token here
    // You can get them by adding your app on https://cloud.estimote.com/#/apps
    [ESTConfig setupAppID:@"<#App ID#>" andAppToken:@"<#App Token#>"];
    
    self.indoorLocationManager = [EILIndoorLocationManager new];
    self.indoorLocationManager.delegate = self;
    self.indoorLocationManager.mode = EILIndoorLocationManagerModeExperimentalWithARKit;
    [self.indoorLocationManager start];
    
    EILRequestFetchLocation *request = [[EILRequestFetchLocation alloc] initWithLocationIdentifier:@"<#my-location#>"];
    [request sendRequestWithCompletion:^(EILLocation * _Nullable location, NSError * _Nullable error) {
        if (location)
        {
            self.location = location;
            
            self.locationView = [[EILIndoorLocationView alloc] initWithFrame:self.view.frame];
            self.locationView.rotateOnPositionUpdate = NO;
            [self.locationView drawLocation:self.location];
            [self.view addSubview:self.locationView];
            
            [self.indoorLocationManager startPositionUpdatesForLocation:self.location];
            
        } else {
            NSLog(@"Can't fetch location: %@", error);
        }
    }];
}

- (void)indoorLocationManager:(EILIndoorLocationManager *)manager
            didUpdatePosition:(EILOrientedPoint *)position
                 withAccuracy:(EILPositionAccuracy)positionAccuracy
                   inLocation:(EILLocation *)location {
    EILPoint *positionInARKitCoordinates = [self.indoorLocationManager ARKitPointFromIndoorLocationPoint:position];
    NSLog(@"IL Position x: %5.2f, y: %5.2f, orientation: %3.0f", position.x, position.y, position.orientation);
    NSLog(@"ARKit Position x: %5.2f, y: %5.2f", positionInARKitCoordinates.x, positionInARKitCoordinates.y);
    [self.locationView updatePosition:position];
}

- (void)indoorLocationManager:(EILIndoorLocationManager *)manager didFailToUpdatePositionWithError:(NSError *)error {
    NSLog(@"Failed to update position: %@", error);
}

@end
