//  Copyright (c) 2015 Estimote Inc. All rights reserved.

import UIKit

class LocationCell: UITableViewCell {

    @IBOutlet var locationNameLabel:UILabel!
    
    override func awakeFromNib() {
        self.locationNameLabel.textColor = UIColor.blackColor()
        self.locationNameLabel.font = UIFont(name: "SlatePro-Bk", size: 16)
    }
}
