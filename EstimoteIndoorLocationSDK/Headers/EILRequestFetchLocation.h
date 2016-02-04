//  Copyright © 2015 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <EstimoteSDK/EstimoteSDK.h>

@class EILLocation;

NS_ASSUME_NONNULL_BEGIN

/** 
 * A block object to be executed when the request finishes.
 */
typedef void(^EILRequestFetchLocationBlock)(EILLocation * _Nullable location, NSError * _Nullable error);

/**
 * Request to fetch location identified by its identifier.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestFetchLocation : ESTRequestGetJSON

/**
 * Returns a new request object for fetching location identified by its identifier.
 *
 * @param identifier An identifier of location to be fetched.
 * @return A request initialized with location identifier.
 */
- (instancetype)initWithLocationIdentifier:(NSString *)identifier;

/**
 * Sends request to Estimote Cloud with completion block.
 * 
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestFetchLocationBlock)completion;

@end

NS_ASSUME_NONNULL_END
