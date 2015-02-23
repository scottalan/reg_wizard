<?php

/**
 * Generates the user address form for founder registration.
 *
 */
function reg_wizard_founder_basic($form, $form_state) {

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

//  $object = $_SESSION[$form_state['wizard_info']['object name']];

  // Attach the user form fields.
//  field_attach_form('user', $user, $form, $form_state);

  // This does combine the #submit and #validate arrays but causes issues.
//  $form = array_merge_recursive($form, drupal_get_form('user_register_form'));
//  $form = array_merge($form, drupal_get_form('user_register_form'));

  // This is better but we have to validate each field manually if it needs it.
  $form = $form + drupal_get_form('user_register_form');

  // This hides fields we don't want but also returns the ones we do as well.
  $fields = reg_wizard_set_fields($form, reg_wizard_founder_basic_define_fields());

  $form['field_user_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#default_value' => '',
    '#weight' => -12,
  );

  $form['field_user_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => '',
    '#weight' => -11,
  );

  // Show the default account field for mail. This is set to false by default.
  // @see reg_wizard_form_user_register_form_alter().
  $form['account']['mail']['#access'] = TRUE;
  $form['account']['name']['#access'] = TRUE;

  $form['account']['name']['#weight'] = $form['account']['mail']['#weight'] + 1;
  $form['account']['name']['#disabled'] = TRUE;

  // Set default values on our custom fields. These fields will be used to create
  // another field on the user profile.
  // @todo What field will the first and last name be used to create?
  $form['account']['mail']['#value'] = isset($object['mail']) ? $object['mail'] : '';
  $form['field_user_first_name']['#default_value'] = isset($object['field_user_first_name']) ? $object['field_user_first_name'] : '';
  $form['field_user_last_name']['#default_value'] = isset($object['field_user_last_name']) ? $object['field_user_last_name'] : '';

  return $form;
}

/**
 * This can be used to limit access on a certain step during the wizard.
 * @param array $wizard
 */
//function reg_wizard_founder_basic_access($wizard) {
//
//}

/**
 * Handles validation of the user basic form.
 */
function reg_wizard_founder_basic_validate($form, &$form_state) {

  reg_wizard_validate_email($form, &$form_state, 'mail');
}

/**
 * Handles submit of the user basic form.
 */
function reg_wizard_founder_basic_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}

/**
 * Every step requires a similar function.
 * Defines the fields we need for this step.
 *
 * @return array
 */
function reg_wizard_founder_basic_define_fields() {
  return array(
    'mail',
    'name',
    'timezone',
    'field_user_first_name',
    'field_user_last_name',
  );
}
