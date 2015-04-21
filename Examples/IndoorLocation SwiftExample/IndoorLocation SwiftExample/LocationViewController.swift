//  Copyright (c) 2014 Estimote Inc. All rights reserved.

import UIKit

class LocationViewController: UIViewController, ESTIndoorLocationManagerDelegate {
    
    @IBOutlet var indoorLocationView:ESTIndoorLocationView!
    @IBOutlet var showTraceSwitch:UISwitch!
    @IBOutlet var rotateOnUpdateSwitch:UISwitch!
    
    @IBOutlet var positionLabel:UILabel!

    var location:ESTLocation?
    private var manager:ESTIndoorLocationManager
    var positionView:ESTPositionView?
    
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

        self.positionView = ESTPositionView(image: UIImage(named: "navigation_guy"), location: self.location, forViewWithBounds: self.indoorLocationView.bounds)
        self.positionView?.hidden = true
        self.indoorLocationView.positionView = self.positionView
        
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
    func indoorLocationManager(manager: ESTIndoorLocationManager!, didUpdatePosition position: ESTOrientedPoint!, withAccuracy accuracy: ESTPositionAccuracy, inLocation location: ESTLocation!) {
        
        self.positionView?.hidden = false
        self.positionLabel.text = NSString(format: "x: %.2f   y: %.2f    α: %.2f",
            position.x,
            position.y,
            position.orientation) as String

        self.positionView?.updateAccuracy(accuracy)
        self.indoorLocationView.updatePosition(position)
    }
    
    func indoorLocationManager(manager: ESTIndoorLocationManager!, didFailToUpdatePositionWithError error: NSError!) {
        
        self.positionView?.hidden = true
        if (error.code == ESTIndoorErrorCode.PositionOutsideLocationError.rawValue) {
            self.positionLabel.text = "It seems you are outside the location."
        }
        else if (error.code == ESTIndoorErrorCode.MagnetometerInitializationError.rawValue) {
            self.positionLabel.text = "It seems your magnetometer is not working.";
        }

        NSLog(error.localizedDescription)
    }
}
