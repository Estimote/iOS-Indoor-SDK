Pod::Spec.new do |s|
  s.name        = "EstimoteIndoorSDK"
  s.version      = "2.4.0"
  s.summary      = "Indoor Location SDK allows real-time beacon-based mapping and indoor location"
  s.description  = <<-DESC
                  Map any space using Estimote Beacons and visualize your location within it in real-time.
                  DESC
  s.homepage    = "http://developer.estimote.com/indoor"

  s.license      = {
    :type => 'Copyright',
    :text => <<-LICENSE
      Copyright 2017 Estimote, Inc. All rights reserved.
      LICENSE
  }

  s.author      = { "Estimote, Inc" => "contact@estimote.com" }
  s.social_media_url  = "http://twitter.com/estimote"

  s.platform    = :ios
  s.ios.deployment_target = '9.0'

  s.source      = { :git => "https://github.com/Estimote/iOS-Indoor-SDK.git", :tag => s.version }
  s.source_files =  'EstimoteIndoorLocationSDK/Headers/*.h'

  s.resources = 'EstimoteIndoorLocationSDK/Resources/*'
  s.preserve_paths = 'EstimoteIndoorLocationSDK/libEstimoteIndoorSDK.a', 'Resources/*'
  s.vendored_libraries = 'EstimoteIndoorLocationSDK/libEstimoteIndoorSDK.a'

  s.frameworks = 'CoreMotion', 'AudioToolbox', 'MediaPlayer', 'MessageUI' 
  s.library = 'z'
  s.requires_arc = true

  s.xcconfig  =  { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/EstimoteIndoorSDK"',
                  'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/Headers/EstimoteIndoorSDK"',
                  'OTHER_LDFLAGS' => '"-lc++"',
                  'ENABLE_BITCODE' => 'NO',}

  s.dependency 'EstimoteSDK', '~> 4.14.1'
end