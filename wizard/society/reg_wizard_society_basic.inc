<?php

/**
 * Generates the user address form for society registration.
 *
 */
function reg_wizard_society_basic($form, $form_state) {

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

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
//    '#weight' => $form['first_name']['#weight'] + .1,
  );
  // Get the user's display name.
  $form['display_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Name'),
    '#description' => t('Full name to be displayed to other users'),
    '#default_value' => reg_wizard_default('display_name', $object),
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
  // Attach js to the form.
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/zip.js';
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/displayName.js';

  return $form;
}

/**
 * This can be used to limit access on a certain step during the wizard.
 * @param array $wizard
 */
//function reg_wizard_society_basic_access($wizard) {
//
//}

/**
 * Handles validation of the user basic form.
 */
function reg_wizard_society_basic_validate($form, &$form_state) {

  // Validate the user display name.
  reg_wizard_validate_display_name($form, &$form_state);
  // Validate the user email.
  reg_wizard_validate_email($form, &$form_state);
}

/**
 * Handles submit of the user basic form.
 */
function reg_wizard_society_basic_submit($form, &$form_state) {

  // Only send an email if we don't have the hmac yet. The user could be going
  // back in the form. We don't want to send another email.
  if (!isset($form_state[SOCIETY_REGISTRATION]['hmac'])) {
    $language = language_default();
    $to = $form_state['input']['mail'];
    $message = drupal_mail('reg_wizard', 'verify', $to, $language);

    $form_state['input']['hmac'] = isset($message['hmac']) ? $message['hmac'] : FALSE;
  }

  reg_wizard_step_submit($form, $form_state);
}
