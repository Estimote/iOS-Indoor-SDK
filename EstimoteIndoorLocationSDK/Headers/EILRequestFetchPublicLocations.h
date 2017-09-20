//  Copyright © 2017 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

@class EILLocation;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block object to be executed when the request finishes.
 */
typedef void(^EILRequestFetchPublicLocationsBlock)(NSArray<EILLocation *> * _Nullable locations, NSError * _Nullable error);

/**
 * Request to fetch public nearby locations and parsing response.
 * In order to determine nearby public locations, scan for nearby beacons.
 * All the locations that contain at least one of the given beacons (identified
 * by their identifiers) will be fetched.
 */
@interface EILRequestFetchPublicLocations : NSObject

/**
 * Returns a new request object for fetching public locations for given beacons.
 *
 * @param identifiers An array containing identifiers of beacons that are used for fetching nearby public locations.
 * @return A request initialized with identifiers of beacons.
 */
- (instancetype)initWithBeaconIdentifiers:(NSArray<NSString *> *)identifiers;

/**
 * Sends request to Estimote Cloud with completion block.
 *
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestFetchPublicLocationsBlock)completion;

@end

NS_ASSUME_NONNULL_END
