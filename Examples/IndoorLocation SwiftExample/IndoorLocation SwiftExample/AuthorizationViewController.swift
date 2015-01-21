//  Copyright (c) 2014 Estimote Inc. All rights reserved.

import UIKit

protocol AuthorizationViewControllerDelegate {
    
    func authorizationEnded(error:NSError?)
}

class AuthorizationViewController: UIViewController {
    
    var delegate:AuthorizationViewControllerDelegate!
    
    var appIDTextField:UITextField!
    var appTokenTextField:UITextField!
    var informationLabel:UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.view.backgroundColor = UIColor.whiteColor()
        
        self.title = "Authorization"
        
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: UIBarButtonSystemItem.Done, target: self, action: Selector("donePressed"))
        
        self.appIDTextField = UITextField(frame: CGRectMake(20, 70, self.view.frame.size.width - 40, 44))
        self.appIDTextField.borderStyle = UITextBorderStyle.RoundedRect
        self.appIDTextField.placeholder = "AppID"
        self.view.addSubview(self.appIDTextField)
        
        self.appTokenTextField = UITextField(frame: CGRectMake(20, 120, self.view.frame.size.width - 40, 44))
        self.appTokenTextField.borderStyle = UITextBorderStyle.RoundedRect
        self.appTokenTextField.placeholder = "AppToken"
        self.view.addSubview(self.appTokenTextField)
        
        self.informationLabel = UILabel(frame: CGRectMake(20, 180, self.view.frame.size.width - 40, 100))
        self.informationLabel.numberOfLines = 0
        self.informationLabel.textAlignment = NSTextAlignment.Center
        self.informationLabel.text = "You can find your API App ID and API App Token in the Account Settings section of the Estimote Cloud."
        self.view.addSubview(self.informationLabel)
    }
    
    func donePressed() {
        
        if (!self.appIDTextField.text.isEmpty && !self.appTokenTextField.text.isEmpty) {
            self.appIDTextField.resignFirstResponder()
            self.appTokenTextField.resignFirstResponder()
            
            ESTConfig.setupAppID(self.appIDTextField.text, andAppToken: self.appTokenTextField.text)
            
            self.delegate.authorizationEnded(nil)
        }
        else {
            self.delegate.authorizationEnded(NSError())
        }
        
        self.dismissViewControllerAnimated(true, completion: nil)
    }
}
