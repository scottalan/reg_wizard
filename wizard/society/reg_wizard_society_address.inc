<?php

/**
 * Generates the user address form for founder registration.
 *
 * @todo Look into https://www.drupal.org/project/addressfield_autocomplete
 *
 */
function reg_wizard_society_address($form, $form_state) {

  global $user;

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  $form['address'] = array(
    '#type' => 'fieldset',
    '#title' => t('Address'),
    '#required' => TRUE,
  );
  $form['address']['address_1'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 1'),
    '#default_value' => reg_wizard_default('address_1', $object),
    '#required' => TRUE,
  );
  $form['address']['address_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address 2'),
    '#default_value' => reg_wizard_default('address_2', $object),
  );
  $form['address']['postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('ZIP Code'),
    '#maxlength'=> 5,
    '#size' => 5,
    '#default_value' => reg_wizard_default('postal_code', $object),
    '#required' => TRUE,
  );
  $form['address']['locality'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 5,
    '#default_value' => reg_wizard_default('locality', $object),
    '#required' => TRUE,
    '#states' => array(
      // Hide the city field when the zipcode field is empty.
      'invisible' => array(
        ':input[name="postal_code"]' => array('value' => ''),
      ),
    ),
  );
  module_load_include('inc', 'webform', '/includes/webform.options');
  // This requires args but doesn't use them.
  $states = webform_options_united_states(NULL,NULL,NULL);
  array_unshift($states, '-- Choose --');
  $form['address']['administrative_area'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#options' => $states,
    '#default_value' => reg_wizard_default('administrative_area', $object),
    '#required' => TRUE,
    '#states' => array(
      // Hide the states select field when the zipcode field is empty.
      'invisible' => array(
        ':input[name="postal_code"]' => array('value' => ''),
      ),
    ),
  );

  // Get timezones
  $timezones = system_time_zones(TRUE);

  // Remove most that aren't in the US.
  foreach ($timezones as $k => $v) {
    if ($k != '' && $k != 'UTC') {
      $parts = explode('/', $k);
      if ($parts[0] != 'America') {
        unset($timezones[$k]);
      }
    }
  }

  // Select list of timezones.
  $form['timezone'] = array(
    '#type' => 'select',
    '#title' => t('Timezone'),
    '#options' => $timezones,
    '#default_value' => reg_wizard_default('timezone', $object),
    '#states' => array(
      // Hide the timezone select field when the zipcode field is empty.
      'invisible' => array(
        ':input[name="postal_code"]' => array('value' => ''),
      ),
    ),
  );

  // Attach js to the form.
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/zip.js';


  return $form;
}

/**
 * Handles validation of the user address form.
 */
function reg_wizard_society_address_validate($form, &$form_state) {

  // Validate the zip code.
  reg_wizard_validate_zip_code($form, &$form_state);
}

/**
 * Handles submit of the user address form.
 */
function reg_wizard_society_address_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}
