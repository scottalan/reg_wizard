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
function reg_wizard_society_results($form, &$form_state) {

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  // An array of keys we want to ignore when rendering results.
  $ignore = array('step_trail', 'step', 'cache', 'token');

  $rows = array();
  $address = array();
  $address_fields = array('address_1', 'address_2', 'postal_code', 'administrative_area', 'locality');

  foreach ($object as $name => $info) {
    if (!in_array($name, $ignore) && !is_array($info) && !in_array($name, $address_fields)) {
      if ($name == 'hmac') {
        $title = t('Email Status');
        $value = t('Verified');
      }
      else {
        $title = str_replace('_', ' ', $name);
        $title = ucwords($title);
        $value = $info;
      }
      $rows[] = array(array('data' => $title), array('data' => $value));
    }
  }

  foreach ($object as $name => $info) {
    if (!in_array($name, $ignore) && in_array($name, $address_fields)) {
      $address[$name] = $info;
    }
  }

  // Add our address elements from the address array.
  $title = t('Address');
  $value = theme('reg_wizard_address_format', array('address' => $address));
  $rows[] = array(array('data' => $title), array('data' => $value));

  if ($rows) {

    // Add the fields to the array.
    $form['fields'] = array(
      '#markup' => '<div>' . theme('table', array('header' => array(), 'rows' => $rows)) . '</div>',
    );
  }

  return $form;
}
