<?php

/**
 * An array of data from the wizard.
 *
 * @param $object
 */
function reg_wizard_supporter_complete($object) {

  global $language;

  $mail = $object['mail'];

  // Register this new user.
  $userinfo = array(
    'name' => 'email_registration_' . user_password(),
    'pass' => user_password(16),
    'mail' => $mail,
    'init' => $mail,
    'status' => 0,
    'access' => REQUEST_TIME,
    'wizard' => 'supporter',
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

  $user->timezone =  $object['timezone'];

  // Save the final user.
  user_save($user);

  // Now that we are done make sure the ctools object cache for this session
  // is cleared.
  ctools_object_cache_clear($object['cache']['obj'], $object['cache']['name']);

  // Send the new user a message.
  drupal_mail('reg_wizard', 'supporter_register', $mail, $language, array('account' => $user));

  // Send the user a message.
  reg_wizard_supporter_registration_complete_message($user);

  drupal_goto('<front>');

}
