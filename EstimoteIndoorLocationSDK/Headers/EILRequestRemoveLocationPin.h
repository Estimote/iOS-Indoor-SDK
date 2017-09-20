//  Copyright © 2017 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

@class EILLocationPin;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block object to be executed when the request finishes.
 */
typedef void (^EILRequestRemoveLocationPinBlock)(EILLocationPin * _Nullable locationPin, NSError * _Nullable error);

/**
 * Request for removing a new location from Estimote Cloud.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestRemoveLocationPin : NSObject

/**
 * Returns a new request object for removing specified pin inside specified location from Estimote Cloud
 *
 * @param locationPin A location pin to be removed from specified location from Estimote Cloud.
 * @return A request initialized with location pin.
 */
- (instancetype)initWithPin:(EILLocationPin *)locationPin;

/**
 * Returns a new request object for removing specified pin inside specified location from Estimote Cloud
 *
 * @param locationPin A location pin to be removed from specified location from Estimote Cloud.
 * @return A request initialized with location pin identifier.
 */
- (instancetype)initWithPinIdentifier:(NSNumber *)identifier;

/**
 * Sends request to Estimote Cloud with completion block.
 *
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestRemoveLocationPinBlock)completion;

@end

NS_ASSUME_NONNULL_END
