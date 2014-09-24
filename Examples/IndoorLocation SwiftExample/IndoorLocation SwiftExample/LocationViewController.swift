//  Copyright (c) 2014 Estimote Inc. All rights reserved.

import UIKit

class LocationViewController: UIViewController, ESTIndoorLocationManagerDelegate {
    
    @IBOutlet var indoorLocationView:ESTIndoorLocationView!
    @IBOutlet var showTraceSwitch:UISwitch!
    @IBOutlet var rotateOnUpdateSwitch:UISwitch!
    
    @IBOutlet var positionLabel:UILabel!

    var location:ESTLocation?
    private var manager:ESTIndoorLocationManager
    
    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: NSBundle?) {
        self.manager = ESTIndoorLocationManager()
        
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
        
        self.manager.delegate = self
    }

    required init(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.title = self.location?.name
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        self.indoorLocationView.drawLocation(self.location)
        self.manager.startIndoorLocation(self.location)
    }
    
    override func viewWillDisappear(animated: Bool) {
        super.viewWillDisappear(animated)
        
        self.manager.stopIndoorLocation()
    }
    
    //MARK: UISwitch events
    @IBAction func showTraceSwitchChanged() {
        self.indoorLocationView.clearTrace()
        self.indoorLocationView.showTrace = self.showTraceSwitch.on
    }
    
    @IBAction func rotateOnUpdateSwitchChanged() {
        self.indoorLocationView.rotateOnPositionUpdate = self.rotateOnUpdateSwitch.on
    }
    
    //MARK: ESTIndoorLocationManager delegate
    func indoorLocationManager(manager: ESTIndoorLocationManager!, didUpdatePosition position: ESTOrientedPoint!, inLocation location: ESTLocation!) {
        
        self.positionLabel.text = NSString(format: "x: %.2f   y: %.2f    α: %.2f",
            position.x,
            position.y,
            position.orientation)

        self.indoorLocationView.updatePosition(position)
    }
    
    func indoorLocationManager(manager: ESTIndoorLocationManager!, didFailToUpdatePositionWithError error: NSError!) {
        
        self.positionLabel.text = "It seems you are outside the location."
        NSLog(error.localizedDescription)
    }
}
