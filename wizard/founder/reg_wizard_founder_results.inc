<?php

/**
 * Returns form results.
 *
 * @param object $object
 *   object with form values.
 *
 * @return array
 *   returns a renderable array for multi-step form result output.
 */
function reg_wizard_founder_results($form, &$form_state) {

  global $user;

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  // An array of keys we want to ignore when rendering results.
  $ignore = array('step_trail', 'regcode', 'step', 'form_build_id', 'form_id', 'js', 'ajax_html_ids', 'ajax_page_state', 'ajax_iframe_upload', 'op');

  $rows = array();

  foreach ($object as $name => $info) {
    if (!in_array($name, $ignore)) {
      if ($name == 'mail') {
        $title = 'E-mail';
      }
      if ($name == 'auto_timezone') {
        $title = t('Timezone');
      }
      if ($name == 'timezone') {
        continue;
      }
      if ($name == 'field_user_skills_strengths') {
        $title = t('Skills/Strengths');
      }
      if (strpos($name, 'field_user_') !== FALSE && $name != 'field_user_skills_strengths') {
        $parts = explode('field_user_', $name);
        $title = ucwords(str_replace('_', ' ', $parts[1]));
      }
      // Referrer fields.
      if (strpos($name, 'referrer_') !== FALSE) {
        $parts = explode('_', $name);
        $title = ucwords(str_replace('_', ' ', $name));
      }
      if (is_array($info)) {
        if (isset($info[LANGUAGE_NONE][0]['value'])) {
          $value = $info[LANGUAGE_NONE][0]['value'];
        }
        // This should be the address.
        else if (isset($info[LANGUAGE_NONE][0]['postal_code'])) {
          // Allow themeing of the address specifically.
          $value = theme('reg_wizard_address_format', array('address' => $info[LANGUAGE_NONE][0]));
        }
        else if ($name == 'field_user_skills_strengths') {
          $title = t('Skills/Strengths');
          $skills = array_filter($info[LANGUAGE_NONE]);
          $value = str_replace('_', '/', implode(' - ', $skills));
        }
        else {
          $value = 'Something is wrong...';
        }
      }
      // This covers custom form elements added to a step that are not a part of
      // the user registration form by default.
      else {
        $value = $info;
      }
      $rows[] = array(array('data' => $title), array('data' => $value));
    }
  }

  if ($rows) {

    // Add the fields to the array.
    $form['fields'] = array(
      '#markup' => '<div>' . theme('table', array('header' => array(), 'rows' => $rows)) . '</div>',
    );
  }

  return $form;
}
