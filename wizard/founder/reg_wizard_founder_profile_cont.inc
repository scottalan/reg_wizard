<?php

/**
 * Generates the first form for founder registration.
 *
 */
function reg_wizard_founder_profile_cont($form, &$form_state) {

  global $user;

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  // Attach the user form fields.
  field_attach_form('user', $user, $form, $form_state);

  // This hides fields we don't want but also returns the ones we do as well.
  $fields = reg_wizard_set_fields($form, reg_wizard_founder_profile_cont_define_fields());

  $form['field_user_about'][LANGUAGE_NONE][0]['#default_value'] = isset($object['field_user_about']) ? $object['field_user_about'][LANGUAGE_NONE][0]['value'] : '';
  $form['field_user_skills_strengths'][LANGUAGE_NONE]['#default_value'] = isset($object['field_user_skills_strengths']) ? $object['field_user_skills_strengths'][LANGUAGE_NONE] : '';

  // Don't show the default account field for username.
  $form['account']['name']['#access'] = FALSE;

  // Set the master template.
  $form['#theme'] = 'reg_wizard_page';

  return $form;
}

/**
 * Handles submit of the first form.
 */
function reg_wizard_founder_profile_cont_submit($form, &$form_state) {

  reg_wizard_step_submit($form, $form_state);
}

/**
 * Defines the fields we need for this step.
 *
 * @return array
 */
function reg_wizard_founder_profile_cont_define_fields() {
  return array(
    'field_user_about',
    'field_user_skills_strengths',
  );
}
