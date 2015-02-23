<?php

function reg_wizard_supporter_info() {
  return array(
    'title' => 'Supporter Registration',
    'id' => 'supporter',
    'form id' => SUPPORTER_REGISTRATION,
    'register' => TRUE,
    'cache type' => 'ctools',
    'save cache' => TRUE,
    'cancel message' => t('Registration has been cancelled.'),
    'pages' => array(
      'tos' => t('Terms of Service'),
      'basic' => t('Basic Info'),
      'verify' => t('Verify Email'),
      'results' => t('Results'),
    ),
    'theme' => 'reg_wizard_page',
    'cancel path' => 'register/start',
    'complete path' => '<front>',
    'wizard path' => 'wizard/supporter',
    'wizard callback' => 'reg_wizard_register_page',
    'wizard finish' => 'reg_wizard_supporter_complete',
    'redirect' => '<front>',
  );
}
