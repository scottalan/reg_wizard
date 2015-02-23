<?php

/**
 * Builds the terms of service form for society sign-up.
 *
 * @param array $form
 * @param array $form_state
 * @return mixed
 */
function reg_wizard_society_tos($form, $form_state) {

  // Add a class to tos forms.
  $form['#attributes']['class'][] = 'reg-wizard-tos-form';

  // Add javascript for terms of service submit.
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/tos.js';

  return $form;
}

/**
 * Handles validation of the terms of service form.
 */
//function reg_wizard_society_tos_validate($form, &$form_state) {}

/**
 * Handles submission of the terms of service form.
 */
function reg_wizard_society_tos_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}
