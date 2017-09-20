//  Copyright © 2017 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

@class EILLocation;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block object to be executed when the request finishes. Returns an array of `EILIndoorLocation` objects.
 */
typedef void(^EILRequestFetchLocationsBlock)(NSArray<EILLocation *> * _Nullable locations, NSError * _Nullable error);

/**
 * Request to fetch all locations from Estimote Cloud for currently authorised user.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestFetchLocations : NSObject

/**
 * Sends request to Estimote Cloud with completion block.
 *
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestFetchLocationsBlock)completion;

@end

NS_ASSUME_NONNULL_END
