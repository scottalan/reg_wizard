<?php

/**
 *
 */

/**
 * An array of data from the wizard.
 *
 * @param $object
 */
function reg_wizard_society_complete($object) {

  // 4000000000000341 - Will create customer but will fail when charged.
  // 4242424242424242 - A good Visa.
  // 4000000000000341 - Attaching this card to a Customer object will succeed, but attempts to charge the customer will fail.
  // 4000000000000002 - Charges with this card will always be declined with a card_declined code.
  // 4000000000000127 - Charge will be declined with an incorrect_cvc code.
  // 4000000000000069 - Charge will be declined with an expired_card code.
  // 4000000000000119 - Charge will be declined with a processing_error code.

  // The email of the person trying to register.
  $mail = $object['mail'];

  // See if we can successfully register a customer using Stripe.
  $customer = cedi_stripe_customer_create($object['token'], $object['mail'], 'Society Member');
//  $customer = cedi_stripe_customer_retrieve('cus_5eEvkTEfweFe1d');

  // If creating the customer was successful we should have an id.
  if (isset($customer->id)) {
    // Try to charge the customer now.
    $charge = cedi_stripe_customer_charge($customer, 7500);

    $code = $charge->getCode();

    // Only continue if we don't get an error code.
    if (!isset($code)) {
      $charge_id = $charge->id; // ch_15RinPIpI37tftaIAHnZd5rz
      $time_billed = $charge['_values']['created'];

      $card_vals = $charge['_values']['card']['_values'];
      $card_id = $card_vals->id; // card_15RiaJIpI37tftaIVwfuccbi
      $last4 = $card_vals->last4;
      $brand = $card_vals->brand;
      $exp_month = $card_vals->exp_month;
      $exp_year = $card_vals->exp_year;

      $object['stripe'] = array(
        'charge_id' => $charge_id,
        'time_billed' => $time_billed,
        'card_id' => $card_id,
        'last4' => $last4,
        'brand' => $brand,
        'exp_month' => $exp_month,
        'exp_year' => $exp_year,
      );

      $wizard = wizard_helper_load(SOCIETY_REGISTRATION);
      wizard_helper_cache_set($wizard, $object);

      global $language;

      // Register this new user.
      $userinfo = array(
        'name' => 'email_registration_' . user_password(),
        'pass' => user_password(16),
        'mail' => $mail,
        'init' => $mail,
        'status' => 0,
        'access' => REQUEST_TIME,
        'wizard' => 'society',
        // These are temporary. We need these in hook_email_registration_name().
        'first' => $object['first_name'],
        'last' => $object['last_name'],
      );
      // Save the account.
      $account = user_save(drupal_anonymous_user(), $userinfo);

      // Remove the names from the account.
      unset($account->first);
      unset($account->last);

      // Load the new user.
      $user = user_load($account->uid);

      // This allows us to easily set user fields.
      $wrapper = entity_metadata_wrapper('user', $user);
      $wrapper->field_user_first_name = $object['first_name'];
      $wrapper->field_user_last_name = $object['last_name'];
      $wrapper->field_user_address->postal_code = $object['postal_code'];
      $wrapper->field_user_address->locality = $object['locality'];
      $wrapper->field_user_address->administrative_area = $object['administrative_area'];

      $user->timezone = $object['timezone'];

      // Save the final user.
      user_save($user);

      // Now that we are done make sure the ctools object cache for this session
      // is cleared.
      ctools_object_cache_clear($object['cache']['obj'], $object['cache']['name']);

      // Send the new user a message.
      drupal_mail('reg_wizard', 'supporter_register', $mail, $language, array('user' => $user));

      // Send the user a message.
      reg_wizard_supporter_registration_complete_message($user);

      drupal_goto('<front>');
    }
    // There is an error charging the card.
    else {

      // The error.
      $error = $charge->jsonBody['error'];

      // We couldn't charge the card on Stripe. Clear the ctools object cache
      // for this registration and let them know what happened.

      // Delete the customer that was created since we can't charge them.
      cedi_stripe_customer_delete($customer);
      // Let them know there was a problem.
      // @todo: Log this in the db.
      drupal_set_message(
        t('%message Your account has not been created. Please try again later.', array('%message' => $error['message']))
      );
      // Log this error to watchdog.
      cedi_stripe_charge_error($charge, $mail, 'society_charge');
      // @todo: This is not clearing, check the args.
      ctools_object_cache_clear($object['cache']['obj'], $object['cache']['name']);
      // Take them to the register page.
      drupal_goto('register');

    }
  }
  // Something went wrong creating the customer.
  else {
    $error = $customer->jsonBody['error'];
    // Log this error to watchdog.
    cedi_stripe_customer_error('society_customer', $error, $mail);
    // @note: if this happens then we have a problem somewhere else. We should
    // never get here.
  }

}
