//
//  AppDelegate.swift
//  IndoorInBackground
//

import UIKit
import UserNotifications

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, EILBackgroundIndoorLocationManagerDelegate {

    var window: UIWindow?
    
    var backgroundIndoorLocationManager: EILBackgroundIndoorLocationManager!
    var fetchLocationTask: UIBackgroundTaskIdentifier = UIBackgroundTaskInvalid

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        
        // TODO: put your App ID and App Token here
        // You can get them by adding your app on https://cloud.estimote.com/#/apps
        ESTConfig.setupAppID("<#App ID#>", andAppToken:"<#App Token#>")
        
        self.backgroundIndoorLocationManager = EILBackgroundIndoorLocationManager()
        self.backgroundIndoorLocationManager.delegate = self
        
        // TODO: Double-check if the "Uses Bluetooth LE accessories" Background Mode is enabled. This is required for Indoor to work properly in the background.
        
        self.requestNecessaryPermissions()
        self.fetchLocationAndStartPositioninig()
        
        return true
    }
    
    func requestNecessaryPermissions() {
        
        // In order to relaunch the application (if it is killed by operating system or user) as the user enters the location “Always in use” Location Services authorization is required.
        self.backgroundIndoorLocationManager.requestAlwaysAuthorization()
        
        // In this example notifications are used for showing the current position, but are not required for Indoor Location to work
        let notificationOptions: UNAuthorizationOptions = [.alert, .sound];
        UNUserNotificationCenter.current().requestAuthorization(options: notificationOptions) { (granted, error) in
            if !granted {
                print("notification permission not granted")
            }
        }
    }
    
    func fetchLocationAndStartPositioninig() {
        
        UIApplication.shared.beginBackgroundTask {
            print("can't fetch location")
            UIApplication.shared.endBackgroundTask(self.fetchLocationTask)
            self.fetchLocationTask = UIBackgroundTaskInvalid
        }
        
        // TODO: replace with an identifier of your own location
        // You will find the identifier on https://cloud.estimote.com/#/locations
        // The Indoor Location SDK can work fully offline. Locations can be fetched only once (or bundled with the app) and later stored in NSUserDefault or similar storage as they conform to NSCoding
        let fetchLocation = EILRequestFetchLocation(locationIdentifier: "<#my-location#>")
        fetchLocation.sendRequest { (location, error) in
            if let location = location {
                self.backgroundIndoorLocationManager.startPositionUpdates(for: location)
            } else {
                print("can't fetch location: \(error!)")
            }
            UIApplication.shared.endBackgroundTask(self.fetchLocationTask)
            self.fetchLocationTask = UIBackgroundTaskInvalid
        }
    }
    
    func backgroundIndoorLocationManager(_ locationManager: EILBackgroundIndoorLocationManager, didFailToUpdatePositionWithError error: Error) {
        print("failed to update position: \(error)")
    }
    
    func backgroundIndoorLocationManager(_ locationManager: EILBackgroundIndoorLocationManager, didUpdatePosition position: EILOrientedPoint, with positionAccuracy: EILPositionAccuracy, in location: EILLocation) {
        let content = UNMutableNotificationContent()
        content.title = "Position updated"
        content.body = "\(position)"
        content.sound = UNNotificationSound.default()
        let trigger = UNTimeIntervalNotificationTrigger(timeInterval: 0.1, repeats: false)
        let identifier = "PositionNotification"
        let request = UNNotificationRequest(identifier: identifier, content: content, trigger: trigger)
        UNUserNotificationCenter.current().add(request, withCompletionHandler: {
            (error) in
        })
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

