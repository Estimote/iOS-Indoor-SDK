//  Copyright © 2017 Estimote. All rights reserved.

#import <Foundation/Foundation.h>

@class EILLocationPin;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block object to be executed when the request finishes.
 */
typedef void (^EILRequestUpdateLocationPinBlock)(EILLocationPin * _Nullable locationPin, NSError * _Nullable error);

/**
 * Request for updating already existing location pin in Estimote Cloud.
 *
 * Note that in order to have request working you need to be authenticated in Estimote Cloud.
 * To do that you have to call -[ESTConfig setupAppID:andAppToken:] first.
 * You can find your API App ID and API App Token in the Apps: http://cloud.estimote.com/#/apps
 * section of the Estimote Cloud: http://cloud.estimote.com/.
 */
@interface EILRequestUpdateLocationPin : NSObject

/**
 * Returns a new request object for updating location pin in Estimote Cloud.
 *
 * @param pin Updated pin.
 * @param pinIdentifier Updated pin identifier.
 * @return A request initialized with location pin and its identifier.
 */
- (instancetype)initWithPin:(EILLocationPin *)pin
              pinIdentifier:(NSNumber *)pinIdentifier;

/**
 * Sends request to Estimote Cloud with completion block.
 *
 * param completion Completion block to be executed when the request finishes.
 */
- (void)sendRequestWithCompletion:(EILRequestUpdateLocationPinBlock)completion;

@end

NS_ASSUME_NONNULL_END
