<?php

function reg_wizard_society_info() {
  return array(
    'title' => 'Society Member Registration',
    'id' => 'society',
    'form id' => SOCIETY_REGISTRATION,
    'register' => TRUE,
    'cache type' => 'ctools',
    'save cache' => TRUE,
    'cancel message' => t('Registration has been cancelled.'),
    'pages' => array(
      'tos' => t('Terms of Service'),
      'basic' => t('Basic Info'),
      'verify' => t('Verify Email'),
      'address' => t('Address'),
      'stripe' => t('Payment'),
      'results' => t('Finish'),
    ),
    'theme' => 'reg_wizard_page',
    'cancel path' => 'register/start',
    'complete path' => '<front>',
    'wizard path' => 'wizard/society',
    'wizard callback' => 'reg_wizard_register_page',
    'wizard finish' => 'reg_wizard_society_complete',
    'redirect' => '<front>',
  );
}
