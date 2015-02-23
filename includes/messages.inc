<?php

function reg_wizard_supporter_registration_complete_message($user) {
  $home = l('homepage', '<front>');
  $user_name = token_replace('[user:name]', array('user' => $user));
  $cancel_url = l('here', 'unsubscribe');

  drupal_set_message(
    t('Welcome, %user, to the CEDI Society! You are successfully registered as a
    CEDI Supporter! We’re thrilled that you’ve joined our team! To learn more
    about CEDI Society, visit our !home. You’ll also be receiving our CEDI
    newsletter, as well as regular updates about other CEDI activities and
    events. If you registered by mistake, you can simply un-subscribe !cancel.',
      array('%user' => $user_name, '!home' => $home, '!cancel' => $cancel_url)));
}
