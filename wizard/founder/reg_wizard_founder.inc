<?php

function reg_wizard_founder_info() {
  return array(
    'title' => 'Founder Registration',
    'id' => 'founder',
    'form id' => FOUNDER_REGISTRATION,
    'register' => TRUE,
    'cancel message' => t('You can register anytime by following the link we sent you by email.'),
    'pages' => array(
      'basic' => t('Basic Info'),
      'address' => t('Address'),
      'profile' => t('Profile'),
      'profile_cont' => t('Profile Continued'),
      'referred_by' => t('Referred By'),
      'results' => t('Results'),
    ),
    'theme' => 'reg_wizard_page',
    'cancel path' => '<front>',
    'return path' => '<front>',
    'access callback' => 'reg_wizard_founder_access',
    'wizard path' => 'wizard/founder',
    'wizard callback' => 'reg_wizard_register_page',
    'wizard finish' => 'reg_wizard_founder_complete',
    'redirect' => '<front>',
  );
}

/**
 * Access callback for menus.
 *
 * @return bool
 */
function reg_wizard_founder_access() {
  // Set access to false initially.
  $access = FALSE;

  // User must be anonymous to register.
  if ($can_register = user_is_anonymous()) {
    switch($_GET['q']) {
      case 'register':
        if (isset($_GET['regcode']) && isset($_GET['target'])) {
          $access = reg_wizard_validate_regcode($_GET['regcode']);
        }
        break;
      default:
        if ($parts = explode('/', $_GET['q'])) {
          $code = end($parts);
          if (reg_wizard_validate_regcode($code) || $code == 'ajax') {
            $access = TRUE;
          }
          else {
            drupal_set_message(t('It appears you do not have access to register. If you clicked on the link in the email please contact us. If you copied and pasted please make sure you copied the entire link.'));
          }
        }
        break;
    }
  }
  // @todo Change back to $access
  return TRUE;
}
