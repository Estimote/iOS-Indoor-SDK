//  Copyright (c) 2015 Estimote Inc. All rights reserved.

import UIKit

class ListViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    
    private var manager:ESTIndoorLocationManager
    private var ownLocationsArray:NSMutableArray
    private var publicLocationsArray:NSMutableArray
    private var tableView:UITableView
    private var refreshControl:UIRefreshControl
    private var sectionsBeingRefreshed:Int
    private var errorCell:UITableViewCell
    private var hadError:Bool
    
    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: NSBundle?) {
        self.manager = ESTIndoorLocationManager()
        self.ownLocationsArray = NSMutableArray()
        self.publicLocationsArray = NSMutableArray()
        self.tableView = UITableView()
        self.refreshControl = UIRefreshControl()
        self.sectionsBeingRefreshed = Int()
        self.errorCell = UITableViewCell()
        self.hadError = Bool()
        
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
    }
    
    required init(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.title = "List of locations"
        
        var tableViewController:UITableViewController = UITableViewController(style: UITableViewStyle.Plain)
        tableViewController.tableView.contentInset = UIEdgeInsetsMake(0, 0, 96, 0)
        tableViewController.tableView.estimatedRowHeight = 44;
        tableViewController.tableView.dataSource = self
        tableViewController.tableView.delegate = self
        tableViewController.tableView.allowsMultipleSelectionDuringEditing = false;
        tableViewController.tableView.registerNib(UINib(nibName: "LocationCell", bundle: nil), forCellReuseIdentifier: "LocationCell")
        
        self.refreshControl = UIRefreshControl()
        self.refreshControl.addTarget(self, action: "refreshLocations", forControlEvents: UIControlEvents.ValueChanged)
        tableViewController.refreshControl = self.refreshControl
        self.tableView = tableViewController.tableView
        self.tableView.frame = self.view.frame
        self.view.addSubview(self.tableView)
        
        self.errorCell = UITableViewCell(style: UITableViewCellStyle.Default, reuseIdentifier: "ErrorCell")
        self.errorCell.textLabel?.textColor = UIColor.blackColor()
        self.errorCell.textLabel?.attributedText = NSAttributedString(string: ""/*"Error while refreshing data…"*/, attributes: [NSBaselineOffsetAttributeName: -2])
        self.errorCell.textLabel?.font = UIFont(name: "SlatePro-Bk", size: 16)
        self.errorCell.backgroundColor = UIColor.lightGrayColor()
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        self.tableView.setContentOffset(CGPointMake(0, self.tableView.contentOffset.y - self.refreshControl.frame.size.height), animated: true)
        self.refreshControl.beginRefreshing()
        self.refreshLocations()
    }
    
    func refreshLocations() {
        self.sectionsBeingRefreshed = 1;
        self.fetchOwnLocations()
        self.refreshNearbyLocations()
    }
    
    func fetchOwnLocations() {
        weak var weakSelf:ListViewController? = self
        var onSuccess:(AnyObject!) -> (Void) =
        { (locations:AnyObject!) in
            weakSelf!.ownLocationsArray = locations as! NSMutableArray
            weakSelf!.tableView.reloadData()
            weakSelf!.hadError = false;
            self.finishedSectionRefresh()
        }
        var onFailure: (NSError!) -> Void =
        { (error: NSError!) in
            NSLog("Error while fetching user locations list: %@", error)
            self.tableView.beginUpdates()
            weakSelf!.hadError = true
            self.tableView.endUpdates()
            self.finishedSectionRefresh()
            weakSelf!.tableView.reloadData()
        }
        
        self.manager.fetchUserLocationsWithSuccess(onSuccess, failure: onFailure)
    }
    
    func refreshNearbyLocations() {
        weak var weakSelf:ListViewController? = self
        var onSuccess:(AnyObject!) -> (Void) =
        { (locations:AnyObject!) in
            weakSelf!.publicLocationsArray = locations as! NSMutableArray
            weakSelf!.tableView.reloadData()
            weakSelf!.hadError = false;
            self.finishedSectionRefresh()
        }
        var onFailure: (NSError!) -> Void =
        { (error: NSError!) in
            NSLog("Error while fetching public locations list: %@", error)
            self.tableView.beginUpdates()
            weakSelf!.hadError = true
            self.tableView.endUpdates()
            self.finishedSectionRefresh()
            weakSelf!.tableView.reloadData()
        }

        self.manager.fetchNearbyPublicLocationsWithSuccess(onSuccess, failure: onFailure)
    }
    
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        if (self.publicLocationsArray.count > 0)
        {
            return 3
        }
        else
        {
            return 2
        }

    }
    
    func finishedSectionRefresh() {
        if (--self.sectionsBeingRefreshed == 0)
        {
            self.refreshControl.endRefreshing()
        }
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if (section == 0)
        {
            return 1
        }
        else if (section == 1)
        {
            return self.publicLocationsArray.count
        }
        else
        {
            return self.ownLocationsArray.count
        }
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        if (indexPath.section == 1 || indexPath.section == 2)
        {
            var cell:LocationCell = tableView.dequeueReusableCellWithIdentifier("LocationCell") as! LocationCell
            cell.accessoryType = UITableViewCellAccessoryType.None
            var location:ESTLocation = self.locationForIndexPath(indexPath)!
            cell.locationNameLabel.text = location.name
            cell.userInteractionEnabled = false
            
            return cell
        }
        else
        {
            return self.errorCell
        }
    }
    
    func locationForIndexPath(indexPath:NSIndexPath) -> ESTLocation? {
        if (indexPath.section == 0)
        {
            return nil
        }
        else if (indexPath.section == 1)
        {
            return self.publicLocationsArray[indexPath.row] as? ESTLocation
        }
        else
        {
            return self.ownLocationsArray[indexPath.row] as? ESTLocation
        }
    }
    
    func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        if (section == 0)
        {
            return nil
        }
        else if (section == 1)
        {
            return "Public locations"
        }
        else
        {
            return "My locations"
        }
    }
    
    func tableView(tableView: UITableView, willDisplayHeaderView view: UIView, forSection section: Int) {
        var header:UITableViewHeaderFooterView = view as! UITableViewHeaderFooterView
        header.textLabel.font = UIFont(name: "SlatePro_bk", size: 16)
        header.textLabel.attributedText = NSAttributedString(string: self.tableView(self.tableView, titleForHeaderInSection: section)!)
        header.textLabel.textAlignment = NSTextAlignment.Left
    }
    
    func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
        if (indexPath.row == 0 && indexPath.section == 0)
        {
            return (self.hadError ? 32 : 0)
        }
        else
        {
            return 44
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}
