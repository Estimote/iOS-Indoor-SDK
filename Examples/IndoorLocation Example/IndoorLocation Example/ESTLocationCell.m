//  Copyright (c) 2015 Estimote Inc. All rights reserved.

#import "ESTLocationCell.h"

@implementation ESTLocationCell

- (void)awakeFromNib
{
    self.locationNameLabel.textColor = [UIColor blackColor];
    self.locationNameLabel.font = [UIFont fontWithName:@"SlatePro-Bk" size:20];
}

@end
