//  Copyright (c) 2015 Estimote Inc. All rights reserved.

#import "ESTListViewController.h"
#import "ESTIndoorLocationManager.h"
#import "ESTLocationCell.h"
#import <ESTConfig.h>

@interface ESTListViewController () <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) ESTIndoorLocationManager *manager;
@property (nonatomic, strong) NSMutableArray *ownLocationsArray;
@property (nonatomic, strong) NSMutableArray *publicLocationsArray;
@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) UIRefreshControl *refreshControl;
@property (nonatomic, assign) NSInteger sectionsBeingRefreshed;
@property (nonatomic, strong) UITableViewCell *errorCell;
@property (nonatomic, assign) BOOL hadError;

@end

@implementation ESTListViewController

- (instancetype)initWithIndoorLocationManager:(ESTIndoorLocationManager *)manager
{
    self = [super init];
    if (self)
    {
        self.manager = manager;
        self.ownLocationsArray = [NSMutableArray new];
        self.publicLocationsArray = [NSMutableArray new];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"List of locations";
    
    UITableViewController *tableViewController = [[UITableViewController alloc] initWithStyle:UITableViewStylePlain];
    tableViewController.tableView.contentInset = UIEdgeInsetsMake(0, 0, 96, 0);
    tableViewController.tableView.estimatedRowHeight = 44;
    tableViewController.tableView.dataSource = self;
    tableViewController.tableView.delegate = self;
    tableViewController.tableView.allowsMultipleSelectionDuringEditing = NO;
    [tableViewController.tableView registerNib:[UINib nibWithNibName:@"ESTLocationCell" bundle:nil] forCellReuseIdentifier:@"ESTLocationCell"];

    self.refreshControl = [[UIRefreshControl alloc] init];
    [self.refreshControl addTarget:self
                            action:@selector(refreshLocations)
                  forControlEvents:UIControlEventValueChanged];
    [tableViewController setRefreshControl:self.refreshControl];
    self.tableView = tableViewController.tableView;
    self.tableView.frame = self.view.frame;
    [self.view addSubview:self.tableView];

    self.errorCell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleDefault reuseIdentifier:@"ErrorCell"];
    self.errorCell.textLabel.textColor = [UIColor blackColor];
    self.errorCell.textLabel.attributedText = [[NSAttributedString alloc] initWithString: @""/*"Error while refreshing data…"*/ attributes:@{ NSBaselineOffsetAttributeName : @-2 }];
    self.errorCell.textLabel.font = [UIFont fontWithName:@"SlatePro-Bk" size:16];
    self.errorCell.backgroundColor = [UIColor lightGrayColor];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self.tableView setContentOffset:CGPointMake(0, self.tableView.contentOffset.y - self.refreshControl.frame.size.height) animated:YES];
    [self.refreshControl beginRefreshing];
    [self refreshLocations];
}

- (void)refreshLocations
{
    self.sectionsBeingRefreshed = 1;
    [self fetchOwnLocations];
    [self refreshNearbyLocations];
}

- (void)fetchOwnLocations
{
    __weak ESTListViewController *weakSelf = self;
    void (^onSuccess)(id locations) = ^void(id locations)
    {
        weakSelf.ownLocationsArray = locations;
        [weakSelf.tableView reloadData];
        weakSelf.hadError = NO;
        [self finishedSectionRefresh];
    };
    void (^onFailure)(NSError *error) = ^void(NSError *error)
    {
        NSLog(@"Error while fetching user locations list: %@", error);
        [self.tableView beginUpdates];
        weakSelf.hadError = YES;
        [self.tableView endUpdates];
        [self finishedSectionRefresh];
        [weakSelf.tableView reloadData];
    };
    [self.manager fetchUserLocationsWithSuccess:onSuccess failure:onFailure];
}

- (void)refreshNearbyLocations
{
    __weak ESTListViewController *weakSelf = self;
    void (^onSuccess)(id locations) = ^void(id locations)
    {
        weakSelf.publicLocationsArray = locations;
        [weakSelf.tableView reloadData];
        weakSelf.hadError = NO;
        [self finishedSectionRefresh];
    };
    void (^onFailure)(NSError *error) = ^void(NSError *error)
    {
        NSLog(@"Error while fetching public locations list: %@", error);
        [self.tableView beginUpdates];
        weakSelf.hadError = YES;
        [self.tableView endUpdates];
        [self finishedSectionRefresh];
        [weakSelf.tableView reloadData];
    };
    [self.manager fetchNearbyPublicLocationsWithSuccess:onSuccess failure:onFailure];
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    if (self.publicLocationsArray.count)
    {
        return 3;
    }
    else
    {
        return 2;
    }
}

- (void)finishedSectionRefresh
{
    if (--self.sectionsBeingRefreshed == 0)
    {
        [self.refreshControl endRefreshing];
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0)
    {
        return 1;
    }
    else if (section == 1)
    {
        return self.publicLocationsArray.count;
    }
    else
    {
        return self.ownLocationsArray.count;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 1 || indexPath.section == 2)
    {
        ESTLocationCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ESTLocationCell"];
        cell.accessoryType = UITableViewCellAccessoryNone;
        ESTLocation *location = [self locationForIndexPath:indexPath];
        cell.locationNameLabel.text = location.name;
        cell.userInteractionEnabled = NO;
        
        return cell;
    }
    else
    {
        return self.errorCell;
    }
}

- (ESTLocation *)locationForIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        return nil;
    }
    else if (indexPath.section == 1)
    {
        return self.publicLocationsArray[indexPath.row];
    }
    else
    {
        return self.ownLocationsArray[indexPath.row];
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0)
    {
        return nil;
    }
    else if (section == 1)
    {
        return @"Public Locations";
    }
    else
    {
        return @"My locations";
    }
}

- (void)tableView:(UITableView *)tableView willDisplayHeaderView:(UIView *)view forSection:(NSInteger)section
{
    UITableViewHeaderFooterView *header = (UITableViewHeaderFooterView *)view;
    
    header.textLabel.font = [UIFont fontWithName:@"SlatePro-Bk" size:16];
    header.textLabel.attributedText = [[NSAttributedString alloc] initWithString:[self tableView:self.tableView titleForHeaderInSection:section] attributes:@{ NSBaselineOffsetAttributeName : @-1}];
    header.textLabel.textAlignment = NSTextAlignmentLeft;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row == 0 && indexPath.section == 0)
    {
        return (self.hadError ? 32 : 0);
    }
    else
    {
        return 44;
    }
}

@end
