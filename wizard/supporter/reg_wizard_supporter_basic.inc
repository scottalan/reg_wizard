<?php

/**
 * Generates the basic form for supporter registration.
 *
 */
function reg_wizard_supporter_basic($form, $form_state) {

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  // This is better but we have to validate each field manually if it needs it.
//  $form = $form + drupal_get_form('user_register_form');

  // Get the user's first name.
  $form['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#default_value' => reg_wizard_default('first_name', $object),
    '#required' => TRUE,
  );
  // Get the user's last name.
  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => reg_wizard_default('last_name', $object),
    '#required' => TRUE,
  );
  // Get the user's email.
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#description' => t('A valid e-mail address. All e-mails from the system
        will be sent to this address. The e-mail address is not made public and
        will only be used to send you news or notifications by e-mail.'),
    '#default_value' => reg_wizard_default('mail', $object),
    '#required' => TRUE,
  );
  $form['address'] = array(
    '#type' => 'fieldset',
    '#title' => t('Address'),
    '#required' => TRUE,
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
      // Hide the settings when the cancel notify checkbox is disabled.
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
      // Hide the settings when the cancel notify checkbox is disabled.
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
      // Hide the settings when the cancel notify checkbox is disabled.
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
 * This can be used to limit access on a certain step during the wizard.
 *
 * @param array $wizard
 *
 * @return bool
 */
//function reg_wizard_supporter_basic_access($wizard) {}

/**
 * Handles validation of the user basic form.
 */
function reg_wizard_supporter_basic_validate($form, &$form_state) {
  // Validate that we have name fields.
//  reg_wizard_validate_names($form, $form_state);
  // Validate the user email.
  reg_wizard_validate_email($form, &$form_state);
  // Validate the zip code.
  reg_wizard_validate_zip_code($form, &$form_state);
}

/**
 * Handles submit of the user basic form.
 */
function reg_wizard_supporter_basic_submit($form, &$form_state) {

  // Only send an email if we don't have the hmac yet. The user could be going
  // back in the form. We don't want to send another email.
  if (!isset($form_state[SUPPORTER_REGISTRATION]['hmac'])) {
    $language = language_default();
    $to = $form_state['input']['mail'];
    $message = drupal_mail('reg_wizard', 'verify', $to, $language);

    $form_state['input']['hmac'] = $message['hmac'];
  }

  reg_wizard_step_submit($form, $form_state);
}
