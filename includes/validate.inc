<?php

function reg_wizard_validate_names($form, &$form_state) {
  if (empty($form_state['input']['first_name'])) {
    form_set_error('first_name', t('Please enter your first name'));
  }
  if (empty($form_state['input']['last_name'])) {
    form_set_error('last_name', t('Please enter your last name.'));
  }
}

function reg_wizard_validate_email($form, &$form_state) {
  // Throw an error if the field is empty.
  if (empty($form_state['input']['mail'])) {
    form_set_error('mail', 'You must enter an email address to continue.');
  }
  // If the field is not empty we need to check a couple things.
  else if ($mail = $form_state['input']['mail']) {
    // Make sure the email is a valid email first.
    if (!valid_email_address($mail)) {
      form_set_error('mail', t('Please enter a valid email address to continue.'));
    }
    // If the email is valid let's make sure it doesn't exist in our system
    // already. We can do this by trying to load the user with that email. If
    // we get a $user back then it does exist, otherwise we continue.
    else if ($user = user_load_by_mail($mail)) {
      form_set_error('mail', t('This email appears to already exist. Do you already have an account? If you have forgotten your password, !password.', array('!password' => l('request a new password', 'user/password'))));
    }
  }
}

function reg_wizard_validate_zip_code($form, &$form_state) {
  if (empty($form_state['input']['postal_code']) || $form_state['input']['postal_code'] < 5) {
    form_set_error('field_user_address[und][0][postal_code', 'You must provide a valid Zip code.'); //field_user_address[und][0][postal_code]
  }
}

function reg_wizard_validate_display_name($form, &$form_state) {
  if (empty($form_state['input']['display_name'])) {
    form_set_error('display_name', t('Please enter the name you would like to represent you on Cedi Society.'));
  }
}

/**
 * Validates the registration code that is added as a query parameter to the url
 * when the registration link is built.
 *
 * @param string $string
 *   The registration code.
 *
 * @return bool
 */
function reg_wizard_validate_regcode($string) {
  $code = check_plain($string);
  $regcode = regcode_use($code);
  if (is_object($regcode) && $code === $regcode->code) {
    return TRUE;
  }
}
