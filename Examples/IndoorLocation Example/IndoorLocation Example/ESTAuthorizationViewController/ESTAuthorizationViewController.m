//  Copyright (c) 2014 Estimote. All rights reserved.

#import "ESTAuthorizationViewController.h"
#import "ESTIndoorLocationManager.h"
#import <ESTConfig.h>

@interface ESTAuthorizationViewController () <UITextFieldDelegate>

@property (nonatomic, strong) IBOutlet UITextField *appIdField;
@property (nonatomic, strong) IBOutlet UITextField *appTokenField;
@property (nonatomic, strong) IBOutlet UIButton *loadBeaconsBtn;

@property (nonatomic, copy) void (^completion)(NSError *error);

@end

@implementation ESTAuthorizationViewController

- (instancetype)initWithCompletion:(void (^)(NSError *))completion
{
    self = [super init];
    if (self)
    {
        self.completion = completion;
    }
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = @"Authorization";
    
    self.appIdField.delegate    = self;
    self.appTokenField.delegate = self;
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                                                           target:self
                                                                                           action:@selector(donePressed)];
}

- (void)donePressed
{
    if (self.appIdField.text.length > 0 && self.appTokenField.text.length > 0)
    {
        [self.appTokenField resignFirstResponder];
        [self.appIdField resignFirstResponder];
        
        [ESTConfig setupAppID:self.appIdField.text andAppToken:self.appTokenField.text];
        
        if (self.completion)
        {
            self.completion(nil);
        }
    }
    else
    {
        if (self.completion)
        {
            self.completion([NSError new]);
        }
    }
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - TextField delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return NO;
}

@end
