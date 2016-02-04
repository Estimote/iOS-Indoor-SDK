//  Copyright © 2015 Estimote. All rights reserved.

#import <EstimoteSDK/EstimoteSDK.h>

@class EILLocation;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block object to be executed when the request finishes.
 */
typedef void(^EILRequestModifyLocationBlock)(EILLocation * _Nullable location, NSError * _Nullable error);

/**
 * Request for modifying already existing location in Estimote Cloud.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestModifyLocation : ESTRequestPutJSON

/**
 * Returns a new request object for modifying location in Estimote Cloud.
 *
 * @param location Modified location.
 * @param locationIdentifier Identifier of location in Estimote Cloud that is to be modified.
 * @return A request initialized with location and location identifier.
 */
- (instancetype)initWithLocation:(EILLocation *)location
              locationIdentifier:(NSString *)locationIdentifier;

/**
 * Sends request to Estimote Cloud with completion block.
 *
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestModifyLocationBlock)completion;

@end

NS_ASSUME_NONNULL_END
