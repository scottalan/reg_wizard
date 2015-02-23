<?php
/**
 * @file
 * We use the Stripe payment system
 */

/**
 * References hook_preprocess_hook().
 *
 * @see reg_wizard_preprocess_reg_wizard_society_stripe().
 */
function reg_wizard_society_stripe_preprocess(&$vars) {
  $vars['form']['status'] = array(
    '#type' => 'hidden',
    '#value' => FALSE,
  );

  if (isset($_SESSION[SOCIETY_REGISTRATION]['mail'])) {
    $vars['form']['mail'] = array(
      '#type' => 'hidden',
      '#value' => $_SESSION[SOCIETY_REGISTRATION]['mail'],
    );
  }
  // This will not exist the first time the form is loaded.
  if (isset($_SESSION[SOCIETY_REGISTRATION]['token'])) {
    $vars['form']['status']['#value'] = TRUE;
    // Pass a good payment to JS.
    $settings = array(
      'payment' => 1,
    );
    drupal_add_js(array('cedi_stripe' => $settings), 'setting');

  }
}

function reg_wizard_society_stripe($form, $form_state) {

  // Get the current state of the cache.
  $object = wizard_helper_cache_get($form_state['wizard_info']);

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'cedi_stripe') . '/js/cedi-stripe.js' => array(
      'type' => 'file',
    ),
  );

  // Add the tokenn to the object if it doesn't already exist. This is a
  // separate form submit via ajax so we won't have access to this in the form
  // submit here.
  if (isset($form_state['input']['stripeToken']) && !isset($object['token'])) {
    $object['token'] = $form_state['input']['stripeToken'];
    $wizard = wizard_helper_load('register/society');
    wizard_helper_cache_set($wizard, $object);
    // Save this now for our preprocess function.
    $_SESSION[SOCIETY_REGISTRATION]['token'] = $object['token'];

  }
  return $form;

}

function reg_wizard_society_stripe_validate($form, &$form_state) {
  if ($form) {

  }
}

function reg_wizard_society_stripe_submit(&$form, &$form_state) {
  reg_wizard_step_submit($form, $form_state);
}
