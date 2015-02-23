<?php

/**
 * Generates the basic form for supporter registration.
 *
 */
function reg_wizard_supporter_verify($form, $form_state) {

  $form['hmac'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Code'),
    '#default_value' => '',
  );

  return $form;
}

/**
 * This can be used to limit access on a certain step during the wizard.
 *
 * @param array $wizard
 *
 * @return bool
 */
//function reg_wizard_supporter_verify_access($wizard) {}

/**
 * Handles validation of the user basic form.
 */
function reg_wizard_supporter_verify_validate($form, &$form_state) {
  if (isset($form_state[SUPPORTER_REGISTRATION]['hmac'])) {

    // Check the email verification code against what we stored.
    if ($form_state[SUPPORTER_REGISTRATION]['hmac'] === $form_state['input']['hmac']) {
      return TRUE;
    }

  }
  form_set_error('hmac', t('Please check your email again. The code seems to be invalid.'));
}

/**
 * Handles submit of the user basic form.
 */
function reg_wizard_supporter_verify_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}
