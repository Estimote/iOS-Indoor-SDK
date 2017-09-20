//  Copyright © 2017 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

@class EILLocationPin;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block object to be executed when the request finishes.
 */
typedef void(^EILRequestFetchLocationPinsBlock)(NSArray<EILLocationPin *> * _Nullable locationPins, NSError * _Nullable error);

/**
 * Request to fetch location pins for location with specified identifier.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestFetchLocationPins : NSObject

/**
 * Returns a new request object for fetching pins for the location with specified identifier.
 *
 * @param An identifier of the location which pins are to be fetched.
 * @return A request initialized with location identifier.
 */
- (instancetype)initWithLocationIdentifier:(NSString *)identifier;

/**
 * Sends a request to Estimote Cloud with completion block.
 * 
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestFetchLocationPinsBlock)completion;

@end

NS_ASSUME_NONNULL_END
