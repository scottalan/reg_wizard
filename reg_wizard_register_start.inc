<?php

/**
 * References hook_preprocess_hook().
 *
 * @see reg_wizard_preprocess_reg_wizard_register_start()
 */
function reg_wizard_register_start_preprocess(&$vars) {
  $vars['submit-buttons'] = drupal_render($vars['form']['submit_buttons']);

  // Include what we need for the modal.
  ctools_include('modal');
  ctools_include('ajax');
  // Add CTools' javascript to the page.
  ctools_modal_add_js();

  $rows = array();

  // Build the links we need to trigger the ajax wizard modals.
//  $vars['supporter_join'] = ctools_modal_text_button(t('Support'), 'register/supporter/tos/nojs', NULL, 'btn btn-default btn-lg supporter-submit icon-white icon-ok');
//  $vars['society_join'] = ctools_modal_text_button(t('Engage'), 'register/society/tos/nojs', NULL, 'btn btn-default btn-lg society-submit icon-white icon-ok');

  // Build the links we need for a standard.
  $vars['supporter_join'] = l(t('Support'), 'register/supporter/tos/nojs', array('attributes' => array('class' => 'btn btn-default btn-lg supporter-submit icon-white icon-ok')));
  $vars['society_join'] = l(t('Engage'), 'register/society/tos/nojs', array('attributes' => array('class' => 'btn btn-default btn-lg supporter-submit icon-white icon-ok')));

  // Create a table for benefit comparison.
  // The table header including links to join.
  $header = array('', t('Registered User'), t('Society Member'));

  // The rows in the table.
  $rows[] = array(t('Pricing'), t('Free'), t('$75/year'));
  $rows[] = array(t('Compare Benefits'), '', '');

  // Helper functions that return the text for each row.
  $common = reg_wizard_benefits_common();
  $society = reg_wizard_benefits_society();

  // Iterate over the results for benefits they have in common.
  foreach ($common as $row) {
    $rows[] = array(t($row), '&#x2713;', '&#x2713;');
  }

  // Iterate over the results for extra benefits you get for being a society
  // member.
  foreach ($society as $row) {
    $rows[] = array(t($row), '', '&#x2713;');
  }

  $rows[] = array('',  $vars['supporter_join'], $vars['society_join']);

  // Theme the table.
  $vars['benefits'] = theme('table', array('header' => $header, 'rows' => $rows));

}

function reg_wizard_register_start($form, $form_state) {

  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();

  // Add javascript for table coloring.
  $form['#attached']['js'][] = drupal_get_path('module', 'reg_wizard') . '/js/table.js';
  $form['#attached']['js'][] = drupal_get_path('module', 'cedi_stripe') . '/js/cedi-stripe.js';

  return $form;
}

function reg_wizard_benefits_common() {
  return array(
    'Receive CEDI newsletter',
    'Attend public CEDI events',
    'Post on CEDI Crowd Finance Page',
    'Invest on CEDI Crowd Finance Page',
    'Share CEDI via social media accounts',
    'View-only access to CEDI Platform',
  );

}

function reg_wizard_benefits_society() {
  return array(
    'Refer a New Member',
    'Vote on CEDI Platform',
    'Comment on CEDI Platform',
    'Post multimedia content (e.g., videos, photos)',
    'Participate in Polls and Surveys',
    'Receive Notifications',
    'Attend CEDI-exclusive events',
    'Bring a Guest to a CEDI event',
    'Mobile Access to CEDI account',
    'Access to Member Directory',
  );

}
