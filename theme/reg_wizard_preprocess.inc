<?php
/**
 * @file
 *
 * Contains preprocess functions that can be used to manipulate variables that
 * are passed to the corresponding template files.
 *
 * Remember we are rendering 'forms' so our form exists in $vars['form'].
 *
 * When creating a new preprocess function create a function in the '.inc' file
 * that follows the naming convention: 'FILENAME_preprocess'. Then simply add
 * the 'hook_preprocess_hook' function below calling the 'FILENAME_preprocess'
 * function passing $vars to it.
 *
 */

/**
 * Implements hook_preprocess_template().
 *
 * Preprocessing for the main template for every step.
 *
 * @param array $vars
 */
function reg_wizard_preprocess_reg_wizard_page(&$vars) {

  $wizard = wizard_helper_get_info();

  foreach ($wizard['pages'] as $key => $value) {
    if ($wizard['object']['step'] == $key) {
      $state = 'active';
    }
    else {
      $state = 'disabled';
    }

    // Set some variables for the trail.
    $title = (is_array($value) && isset($value['title'])) ? $value['title'] : $value;
    $description = (is_array($value) && isset($value['description'])) ? $value['description'] : '';
    $path = (is_array($value) && isset($value['path'])) ? $value['path'] : '';

    // Build our trail.
    $vars['trail'][$key] = array(
      'title' => $title,
      'description' => $description,
      'path' => $wizard['path'] . '/' . $key . '/nojs',
      'state' => $state,
    );
  }

  $form = &$vars['form'];

  // If we don't unset #theme we get an infinite loop.
  // When the form is called again it will get reset.
  unset($form['#theme']);

  // The sub-template we are injecting into this template.
  if (isset($form['#form_id'])) {
    $vars['inner_template'] = str_replace('-', '_', $form['#form_id']);
  }

  // Buttons
  $vars['next'] = drupal_render($form['buttons']['next']);
  $vars['previous'] = drupal_render($form['buttons']['previous']);
  $vars['finish'] = drupal_render($form['buttons']['return']);
  $vars['cancel'] = drupal_render($form['buttons']['cancel']);

  // Ctools breadcrumb trail.
  $vars['ctools_trail'] = drupal_render($form['ctools_trail']);

}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
function reg_wizard_preprocess_reg_wizard_register_start(&$vars) {
  reg_wizard_register_start_preprocess($vars);
}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
function reg_wizard_preprocess_reg_wizard_founder_start(&$vars) {
  reg_wizard_founder_start_preprocess($vars);
}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
function reg_wizard_preprocess_reg_wizard_society_stripe(&$vars) {
  reg_wizard_society_stripe_preprocess($vars);
}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_supporter_tos(&$vars) {}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_founder_basic(&$vars) {}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_founder_address(&$vars) {}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_founder_profile(&$vars) {}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_founder_profile_cont(&$vars) {}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_founder_referred_by(&$vars) {}

/**
 * Implements hook_preprocess_template().
 *
 * @param array $vars
 */
//function reg_wizard_preprocess_reg_wizard_founder_results(&$vars) {}
