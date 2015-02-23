<?php

/**
 * @file
 * Builds placeholder replacement tokens for user-related data.
 */

/**
 * Implements hook_token_info().
 */
function reg_wizard_token_info() {
  $info['tokens']['user']['verify-wizard-email'] = array(
    'name' => t('Verify-email URL'),
    'description' => t('The URL to verify the user e-mail during the registration wizard.'),
    'restricted' => TRUE,
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function reg_wizard_tokens($type, $tokens, $data = array(), $options = array()) {

  $replacements = array();

  if ($type == 'user' && !empty($data['user'])) {

    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Basic user account information.
        case 'verify-wizard-email':
          // In the case of hook user_presave uid is not set yet.
          $replacements[$original] = $original;
          break;
      }
    }
  }

  return $replacements;
}
