<?php

function reg_wizard_supporter_unsubscribe($form, &$form_state) {

  $form = array();

  $form['mail'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#attributes' => array('id' => array('supporter_email')), // targeted ID via ajax
  );
  $form['mail']['email_field'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#description' => t('Enter the email used to register. You will receive an email with a validation code.'),
    '#required' => TRUE,
  );

  $form['mail']['email_submit'] = array(
    "#type" => "submit",
    "#value" => "Get Code",
    '#states' => array(
      'visible' => array(
        ':input[name="email_field"]' => array(
          array('filled' => TRUE),
        ),
      ),
    ),
    "#ajax" => array(
      "callback" => "reg_wizard_supporter_unsubscribe_send_email",
//      "wrapper" => "replace_email_fieldset",
//      'method' => 'replace',
    )
  );

  $form['code'] = array(
  '#type' => 'fieldset',
  '#title' => '',
  '#attributes' => array('id' => array('supporter_code')), // targeted ID via ajax
//    '#prefix' => '<div id="supporter_unsubscribe_code">',
//    '#suffix' => '</div>',
  );
  $form['code']['code_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Code'),
    '#description' => t('After submitting your email, enter the code sent to you here.'),
    '#required' => TRUE,
  );
  $form['code']['code_submit'] = array(
    "#type" => "submit",
    "#value" => "Un-Subscribe",
    '#states' => array(
      'visible' => array(
        ':input[name="code_field"]' => array(
          array('filled' => TRUE),
        ),
      ),
    ),
    "#ajax" => array(
      "callback" => "reg_wizard_supporter_unsubscribe_remove_user",
//      "wrapper" => "supporter_email_replace",
//      'method' => 'replace',
    )
  );

  return $form;
}

function reg_wizard_supporter_code_form($form, &$form_state) {
  $form = array();

  $form['code'] = array(
    '#type' => 'fieldset',
    '#title' => '',
    '#attributes' => array('id' => array('supporter_unsubscribe_code')), // targeted ID via ajax
//    '#prefix' => '<div id="supporter_unsubscribe_code">',
//    '#suffix' => '</div>',
  );
  $form['code']['code_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Code'),
    '#description' => t('After submitting your email, enter the code sent to you here.'),
    '#required' => TRUE,
  );
  $form['code']['code_submit'] = array(
    "#type" => "submit",
    "#value" => "Un-Subscribe",
    '#attributes' => array('id' => array('supporter_unsubscribe_code'), 'class' => array('ajax-processed')), // targeted ID via ajax
    "#ajax" => array(
      "callback" => "reg_wizard_supporter_unsubscribe_remove_user",
      "wrapper" => "supporter_email_replace",
      'method' => 'replace',
    )
  );

  return $form;
}

function reg_wizard_supporter_unsubscribe_validate(&$form, &$form_state) {

}

function reg_wizard_supporter_unsubscribe_send_email(&$form, &$form_state) {
  global $language;

  $email = $form_state['values']['email_field'];

  // Find the user with this email.
  if ($user = user_load_by_mail($email)) {

    // We actually store the code in the user object so we have it later.
    $code = reg_wizard_user_email_verification_code($user->uid, FALSE);
    // Send an email to the user with
    $message = drupal_mail('reg_wizard', 'verify', $email, $language, array('account' => $user, 'code' => $code));

    $commands[] = ajax_command_append('#supporter_email', '<span class=check-email>Check your email, you should receive a code. Copy carefully and paste it below.</span>');
  }
  else {
    ctools_include('ajax');
    $commands[] = ctools_ajax_command_redirect('unsubscribe');
    drupal_set_message(t("We couldn't find a user with that email. Please try again or contact us."));
  }

  return array('#type' => 'ajax', '#commands' => $commands);

}

function reg_wizard_replace(&$form, &$form_state) {

  $form_new = drupal_get_form('reg_wizard_supporter_code_form');

  $rendered = render($form_new);

  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace("#supporter_email_replace", $rendered),
    )
  );
}

function reg_wizard_supporter_unsubscribe_remove_user(&$form, &$form_state) {

  $hit = '';

//  return array(
//    '#type' => 'ajax',
//    '#commands' => array(
//      ajax_command_replace("#supporter_unsubscribe_code", render($form)),
//    )
//  );

}

function reg_wizard_supporter_unsubscribe_message($user) {
  global $language;

  $exists = user_load_by_mail($user->mail);
  // If we don't find a user it was a success.
  if (!$exists) {
    drupal_set_message(t('Your account was successfully removed.'));
//    drupal_mail('reg_wizard', 'successful_unsubscribe', $user->mail, $language, array('account' => $user));
  }
  // If we do find one then it didn't work.
  else {
    drupal_set_message(t('There was an error removing your account. Please contact us. Thank you!'));
  }
  ctools_include('ajax');
  $commands[] = ctools_ajax_command_redirect('<front>');
}

function reg_wizard_supporter_unsubscribe_submit(&$form, &$form_state) {
  $code = $form_state['values']['code_field'];

  $user = user_load_by_mail($form_state['values']['email_field']);
  $hmac = $user->data['verification'];

  if (isset($code) && isset($hmac)) {

    if ($code === $hmac) {

      db_delete('users')
        ->condition('uid', $user->uid)
        ->execute();

      reg_wizard_supporter_unsubscribe_message($user);
    }
    else {
      drupal_set_message('Please check to make sure you pasted the verification code properly.');
    }
  }
}
