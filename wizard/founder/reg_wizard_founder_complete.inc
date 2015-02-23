<?php
//  user_save($account, $edit = array(), $category = 'account')

/**
 * @param account
 *
 * field_user_email
 *
 * username - $form['account']['name']
 * email - $form['account']['mail']
 * field_user_display_name - $form['account']['field_user_display_name']
 *
 * @param user-info
 *
 * field_user_display_name
 * field_user_picture
 * field_user_title
 * field_user_address
 * field_user_phone
 * field_user_employer
 * field_user_dob
 * field_user_skills_strengths
 *
 *  need to make sure we have: $edit['regcode_code'] so regcode is handled.
 *
 * $user->picture is just the fid.
 */


/**
 * An array of data from the wizard.
 *
 * @param $object
 */
function reg_wizard_founder_complete($object) {
  global $user;

  $fname = $object['field_user_first_name'];
  $fname = strtolower($fname);
  $fname = substr($fname, 0, 1);
  $lname = strtolower($object['field_user_last_name']);
  $username = $fname . $lname;

  // For now just set the username as the email.
  $username = $object['mail'];

  // Set the fields for the user account.
  $user->name = $username;
  $user->mail = $username;
  $user->init = $username;
  $user->regcode_code = $object['regcode'];

//  $name = db_query("SELECT * FROM {users} WHERE name = :name AND status = 1", array(':name' => $username))->fetchObject();

  // Get the registration form for the user. This will contain the fields we
  // added through the field UI.
  $form = drupal_get_form('user_register_form');

  // Create a default $form_state.
  $form_state = form_state_defaults();

  // Set default fields for the user.
  $form_state['values']['name'] = $username;
  $form_state['values']['mail'] = $username;
  $form_state['values']['timezone'] = $object['auto_timezone'];

  // This also needs to be set.
  $form_state['values']['administer_users'] = FALSE;

  // Set the registration code used so it can't be used again.
  $form_state['values']['regcode_code'] = $object['regcode'];

  // This gives us an array of fields that were created for the user bundle.
  $user_fields = field_info_instances('user', 'user');

  // Iterate over the user fields to find the fields we need in the $object.
  foreach ($user_fields as $field => $data) {
    // We have to handle the address differently.
    if ($field == 'field_user_address') {
      $form_state['values'][$field] = $object[$field];
      // @todo: See if we can set this earlier.
      $form_state['values'][$field][LANGUAGE_NONE][0]['element_key'] = 'user|user|field_user_address|und|0';
      // Country is handled automatically. We have set US to be the default country.
    }
    // We also need to handle skills differently.
    else if ($field == 'field_user_skills_strengths') {
      $options = array_filter($object[$field][LANGUAGE_NONE]);
      foreach ($options as $option) {
        $form_state['values'][$field][LANGUAGE_NONE][]['value'] = $option;
      }
    }
    else {
      // If the field exists in the $object then set its value in the form.
      if (isset($object[$field])) {
        $form_state['values'][$field] = $object[$field];
      }
    }
  }

  // Register the user using the form.
  user_register_submit($form, $form_state);
}
