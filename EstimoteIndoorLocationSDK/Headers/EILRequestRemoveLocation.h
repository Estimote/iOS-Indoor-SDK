//  Copyright © 2015 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <EstimoteSDK/EstimoteSDK.h>

@class EILLocation;

NS_ASSUME_NONNULL_BEGIN

/** 
 * A block object to be executed when the request finishes.
 */
typedef void(^EILRequestRemoveLocationBlock)(EILLocation * _Nullable location, NSError * _Nullable error);

/**
 * Request for removing a new location from Estimote Cloud.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestRemoveLocation : ESTRequestPostJSON

/**
 * Returns a new request object for removing location from Estimote Cloud.
 *
 * @param location Location to be removed from Estimote Cloud.
 * @return A request initialized with location.
 */
- (instancetype)initWithLocation:(EILLocation *)location;

/**
 * Sends request to Estimote Cloud with completion block.
 *
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestRemoveLocationBlock)completion;

@end

NS_ASSUME_NONNULL_END
