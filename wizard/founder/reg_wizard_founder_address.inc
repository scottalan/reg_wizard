<?php

/**
 * Generates the user address form for founder registration.
 *
 * @todo Look into https://www.drupal.org/project/addressfield_autocomplete
 *
 */
function reg_wizard_founder_address($form, $form_state) {

  global $user;

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  // We use this to get the user fields.
  // We use drupal_get_form() to get forms so we make sure alters are called.
  $form = $form + drupal_get_form('user_register_form');

  // This hides fields we don't want but also returns the ones we do as well.
  $fields = reg_wizard_set_fields($form, reg_wizard_founder_address_define_fields());

  // Get all timezones from the system.
  $timezones = system_time_zones(TRUE);

  // Remove all timezones that aren't in America.
  foreach ($timezones as $k => $v) {
    if ($k != '' && $k != 'UTC') {
      $parts = explode('/', $k);
      if ($parts[0] != 'America') {
        unset($timezones[$k]);
      }
    }
  }

  // Set a select list of timezones. This will be auto filled based on zip.
  $form['auto_timezone'] = array(
    '#type' => 'select',
    '#title' => t('Timezone'),
    '#options' => $timezones,
    '#default_value' => 'America/New York',
  );

  // Move the address fields to the top of the form.
  $form['field_user_address']['#weight'] = -100;

  // A shortcut to get to the address fields.
  $address_form = &$form['field_user_address'][LANGUAGE_NONE][0];
  $address_object = &$object['field_user_address'][LANGUAGE_NONE][0];

  // Set form defaults if they exist in cache.
  $address_form['street_block']['thoroughfare']['#value'] = isset($address_object['thoroughfare']) ? $address_object['thoroughfare'] : '';
  $address_form['street_block']['premise']['#value'] = isset($address_object['premise']) ? $address_object['premise'] : '';
  $address_form['locality_block']['locality']['#value'] = isset($address_object['locality']) ? $address_object['locality'] : '';
  $address_form['locality_block']['administrative_area']['#value'] = isset($address_object['administrative_area']) ? $address_object['administrative_area'] : '';
  $address_form['locality_block']['postal_code']['#value'] = isset($address_object['postal_code']) ? $address_object['postal_code'] : '';

  $form['auto_timezone']['#default_value'] = isset($object['auto_timezone']) ? $object['auto_timezone'] : '';

  // Move city and state below postal code.
  $address_form['locality_block']['locality']['#weight'] =
    $address_form['locality_block']['postal_code']['#weight'] + 1;
  $address_form['locality_block']['administrative_area']['#weight'] =
    $address_form['locality_block']['locality']['#weight'] + 1;

  // Attach js to the form.
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/zip.js';

  return $form;
}

/**
 * Handles validation of the user address form.
 */
function reg_wizard_founder_address_validate($form, &$form_state) {
  $address_form = &$form_state['input']['field_user_address'][LANGUAGE_NONE][0];
  if (isset($address_form['postal_code'])) {
    $length = strlen($address_form['postal_code']);
    if ($length < 5) {
      form_set_error('field_user_address[und][0][postal_code', 'You must provide a valid Zip code.'); //field_user_address[und][0][postal_code]
    }
  }
}

/**
 * Handles submit of the user address form.
 */
function reg_wizard_founder_address_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}

/**
 * Defines the fields we need for this step.
 *
 * @return array
 */
function reg_wizard_founder_address_define_fields() {
  return array(
    'field_user_address',
    'timezone',
  );
}
