<?php

/**
 * Generates the first form for founder registration.
 * $element = drupal_array_get_nested_value($form, $parents);
 */
function reg_wizard_founder_profile($form, &$form_state) {

  global $user;

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  // We use this to get the user fields.
  // We use drupal_get_form() to get forms so we make sure alters are called.
  $form = $form + drupal_get_form('user_register_form');
//  field_attach_form('user', $user, $form, $form_state);

  // This hides fields we don't want but also returns the ones we do as well.
  $fields = reg_wizard_set_fields($form, reg_wizard_founder_profile_define_fields());

  foreach ($fields as $name => $data) {
    // Custom handling for user picture.
    if ($name == 'field_user_picture') {
//      $form[$name][LANGUAGE_NONE][0]['#default_value'] = isset($object[$name]) ? $object[$name][LANGUAGE_NONE][0] : '';
    }
    // Custom handling for user display name.
//    else if ($name == 'field_user_display_name') {
//      $form[$name][LANGUAGE_NONE][0]['value']['#default_value'] = isset($object[$name]) ? $object[$name][LANGUAGE_NONE][0]['value'] : '';
//    }
    // Custom handling for user display name, user title, phone and employer.
    else if ($name == 'field_user_display_name' || $name == 'field_user_title' || $name == 'field_user_phone' || $name == 'field_user_employer') {
      $form[$name][LANGUAGE_NONE][0]['value']['#value'] = isset($object[$name]) ? $object[$name][LANGUAGE_NONE][0]['value'] : '';
    }
    else {
      // Set form defaults if they exist in cache.
      $form[$name]['#default_value'] = isset($object[$name]) ? $object[$name] : '';
    }
  }

//  $form['new_birthday'] = array(
//    '#type' => 'date_popup',
//    '#title' => t('Birthday'),
//    '#date_type' => DATE_FORMAT_DATE,
//    '#date_timezone' => date_default_timezone(),
//    '#date_format' => 'm-d-Y',
//    '#date_increment' => 1,
//    '#date_year_range' => '-3:+3',
//  );

//  $form['marker_fid'] = array(
//    '#title' => t('Test Image'),
//    '#type' => 'managed_file',
//    '#default_value' => isset($object['marker_fid']) ? $object['marker_fid'] : array(),
//    '#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
//    '#upload_location' => 'public://pictures/tmp',
//  );

  // Set the master template.
  $form['#theme'] = 'reg_wizard_page';

  return $form;
}

/**
 * Handles validation of the profile form.
 */
function reg_wizard_founder_profile_validate($form, &$form_state) {

  if (empty($form_state['input']['field_user_display_name'][LANGUAGE_NONE][0]['value'])) {
    form_set_error('field_user_display_name', t('Please enter the name you would like to represent you on Cedi Society.'));
  }
  // This is the country code for the US & Canada.
  $ccode = 'ca';
  $input = $form_state['input']['field_user_phone'][LANGUAGE_NONE][0]['value'];
  if (!valid_phone_number($ccode, $input)) {
    $country = phone_country_info($ccode);
    if (empty($input)) {
      form_set_error('field_user_phone', t('Please enter a phone number.'));
    }
    else {
      form_set_error('field_user_phone', t($country['error'], array('%value' => $input)));
    }
  }
}

/**
 * Handles submission of the profile form.
 */
function reg_wizard_founder_profile_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}

/**
 * Defines the fields we need for this step.
 *
 * @return array
 */
function reg_wizard_founder_profile_define_fields() {
  return array(
    'field_user_display_name',
    'field_user_title',
    'field_user_employer',
    'field_user_phone',
  );
}

// drupal_alter('date_combo_process', $element, $form_state, $context);
//function reg_wizard_date_combo_process_alter(&$element, &$form_state, $context) {
//  if ($element) {
//    $element['value']['#ajax'] = TRUE;
//  }
//}
