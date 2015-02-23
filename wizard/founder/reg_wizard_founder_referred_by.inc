<?php

/**
 * Generates the user referal form for founder registration.
 *
 */
function reg_wizard_founder_referred_by($form, $form_state) {

  global $user;

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  $form['referral'] = array(
    '#type' => 'fieldset',
    '#title' => t('Referral'),
  );
  $form['referral']['referrer_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#default_value' => '',
//    '#required' => TRUE,
  );
  $form['referral']['referrer_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => '',
//    '#required' => TRUE,
  );
  $form['referral']['referrer_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => '',
    '#required' => TRUE,
    '#attributes' => array(
      'type' => 'email',
    ),
  );

  // Set default values if we go back.
  $form['referral']['referrer_first_name']['#default_value'] = isset($object['referrer_first_name']) ? $object['referrer_first_name'] : '';
  $form['referral']['referrer_last_name']['#default_value'] = isset($object['referrer_last_name']) ? $object['referrer_last_name'] : '';
  $form['referral']['referrer_email']['#default_value'] = isset($object['referrer_email']) ? $object['referrer_email'] : '';

  // Set the master template.
  $form['#theme'] = 'reg_wizard_page';

  return $form;
}

/**
 * Handles validation of the user address form.
 */
function reg_wizard_founder_referred_by_validate($form, &$form_state) {
  reg_wizard_validate_email($form, &$form_state, 'referrer_email');
}

/**
 * Handles submit of the user address form.
 */
function reg_wizard_founder_referred_by_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}

/**
 * Defines the fields we need for this step.
 *
 * @return array
 */
function reg_wizard_founder_referred_by_define_fields() {
  return array(

  );
}
