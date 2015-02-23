<?php

/**
 * References hook_preprocess_hook().
 *
 * @see reg_wizard_preprocess_reg_wizard_founder_start()
 */
function reg_wizard_founder_start_preprocess(&$vars) {
  $vars['agree_button'] = drupal_render($vars['form']['agree_button']);
}

function reg_wizard_founder_start($form, $form_state, $target, $code) {

  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();

  $links[] = ctools_modal_text_button(t('I Agree'), 'register/' . $target . '/basic/nojs', NULL, 'btn btn-default btn-primary agree-submit disabled');

  $button = theme('item_list', array('items' => $links));

  $form['agree_button'] = array(
    '#markup' => $button,
  );

  // Add javascript for terms of service submit.
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/tos.js';

  // Add a class to tos forms.
  $form['#attributes']['class'][] = 'reg-wizard-tos-form';

  // Store the registration code so we have access to it later.
  $_SESSION[FOUNDER_REGISTRATION]['regcode'] = $code;

  return $form;
}
