Pod::Spec.new do |s|
  s.name        = "EstimoteIndoorSDK"
  s.version      = "1.2.0"
  s.summary      = "Indoor Location SDK allows real-time beacon-based mapping and indoor location"
  s.description  = <<-DESC
                  Map any space using Estimote Beacons and visualize your location within it in real-time.
                  DESC
  s.homepage    = "http://estimote.com/indoor"

  s.license      = {
    :type => 'Copyright',
    :text => <<-LICENSE
      Copyright 2015 Estimote, Inc. All rights reserved.
      LICENSE
  }

  s.author      = { "Estimote, Inc" => "contact@estimote.com" }
  s.social_media_url  = "http://twitter.com/estimote"

  s.platform    = :ios
  s.ios.deployment_target = '7.0'

  s.source      = { :git => "https://github.com/Estimote/iOS-Indoor-SDK.git", :tag => "1.2.0" }
  s.source_files =  'EstimoteIndoorLocationSDK/Headers/*.h'

  s.resources = 'EstimoteIndoorLocationSDK/Resources/**/*'
  s.preserve_paths = 'EstimoteIndoorLocationSDK/libEstimoteIndoorSDK.a', 'Resources/**/*'
  s.vendored_libraries = 'EstimoteIndoorLocationSDK/libEstimoteIndoorSDK.a'

  s.frameworks = 'UIKit', 'Foundation', 'SystemConfiguration', 'MobileCoreServices', 'CoreLocation', 'CoreGraphics', 'CoreBluetooth', 'CoreMotion', 'MessageUI', 'MediaPlayer', 'AVFoundation', 'AudioToolbox'
  s.requires_arc = true

  s.xcconfig  =  { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/EstimoteIndoorSDK"',
                  'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/Headers/EstimoteIndoorSDK"',
                  'OTHER_LDFLAGS' => '"-lc++"'}


  s.dependency "EstimoteSDK", "~> 2.4.0"
end