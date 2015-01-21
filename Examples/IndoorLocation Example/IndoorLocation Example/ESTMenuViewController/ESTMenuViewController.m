//  Copyright (c) 2014 Estimote Inc. All rights reserved.

#import "ESTMenuViewController.h"
#import "ESTAuthorizationViewController.h"
#import "ESTIndoorLocationViewController.h"
#import <ESTIndoorLocationManager.h>
#import <ESTConfig.h>
#import <ESTLocationBuilder.h>

#define LAST_CREATED_LOCATION_KEY @"last_created_location_key"

@interface ESTMenuViewController ()

@end

@implementation ESTMenuViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)showLocationSetup
{
    __weak ESTMenuViewController *weakSelf = self;
    UIViewController *nextVC = [ESTIndoorLocationManager locationSetupControllerWithCompletion:^(ESTLocation *location, NSError *error) {
        
        [weakSelf dismissViewControllerAnimated:YES completion:^{
            if (location)
            {
                [[NSUserDefaults standardUserDefaults] setObject:[location toDictionary] forKey:LAST_CREATED_LOCATION_KEY];
                
                ESTIndoorLocationViewController *navigationVC = [[ESTIndoorLocationViewController alloc] initWithLocation:location];
                [weakSelf.navigationController pushViewController:navigationVC animated:YES];
            }
        }];
    }];
    
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:nextVC];
    [self presentViewController:navController animated:YES completion:nil];
}

#pragma mark - Button handling
- (IBAction)setupNewLocation:(id)sender
{
    if (![ESTConfig isAuthorized])
    {
        __weak ESTMenuViewController *weakSelf = self;
        ESTAuthorizationViewController *authorizationVC = [[ESTAuthorizationViewController alloc] initWithCompletion:^(NSError *error) {
            
            if (!error)
            {
                [weakSelf performSelector:@selector(showLocationSetup) withObject:nil afterDelay:1];
            }
        }];

        [self presentViewController:[[UINavigationController alloc] initWithRootViewController:authorizationVC]
                           animated:YES
                         completion:nil];
    }
    else
    {
        [self showLocationSetup];
    }
}

- (IBAction)loadPreviousLocation:(id)sender
{
    NSDictionary *dictionaryLocationRepresentation = [[NSUserDefaults standardUserDefaults] objectForKey:LAST_CREATED_LOCATION_KEY];
    if (dictionaryLocationRepresentation)
    {
        ESTLocation *location = [ESTLocation locationFromDictionary:dictionaryLocationRepresentation];

        ESTIndoorLocationViewController *navigationVC = [[ESTIndoorLocationViewController alloc] initWithLocation:location];
        [self.navigationController pushViewController:navigationVC animated:YES];
    }
    else
    {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"No saved location"
                                                            message:@"Setup a new location first"
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil, nil];
        [alertView show];
    }
}

- (IBAction)loadLocationFromJSON:(id)sender
{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"location" ofType:@"json"];
    NSString *content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    
    ESTLocation *location = [ESTLocationBuilder parseFromJSON:content];
    ESTIndoorLocationViewController *navigationVC = [[ESTIndoorLocationViewController alloc] initWithLocation:location];
    [self.navigationController pushViewController:navigationVC animated:YES];
}

@end
