<?php
/**
 * @file
 * This module works by employing a single hook to wrap up a CTools
 * wizard implementation.  The hook is defined as follows.
 */

/**
 * Define what wizards your module implements.
 *
 * @return array
 *    An array of wizards with the information for each wizard witin each array
 *    entry.  The key for the array should be actual hook_menu paths that will
 *    be defined to handle the form submissions of your wizard.  The menu "title",
 *    "access callback", and "access arguments" can be defined within each entry.
 *    The parameters that can be provided by each wizard is defined as follows.
 *
 *      - pages (required): The pages to show within the wizard.
 *      - title (optional):  The menu title and wizard title for this wizard.
 *      - access callback (optional): The menu access callback for this wizard.
 *      - access arguments (optional): The menu access arguments for this wizard.
 *      - wizard callback (optional): Allows you to alter the wizard info at runtime.
 *      - id (optional): A unique ID for this wizard.  If none provided, then
 *        the path will be used as the unique ID ( all '/' replaced with '_' ).
 *      - object name (optional): The name of the object within the $form_state
 *        to pass around to each of the wizard pages.
 *      - path (optional): The path to the directory that contains your wizard.  This
 *        defaults to a folder within your module whose name is the "id" above.
 *      - form id (optional): The form id name to provide for the wizard form.
 *      - cancel message (optional): The message to display when the user cancels
 *        the wizard.
 *      - show trail (optional): The CTools wizard 'show trail' setting.
 *      - show back (optional): The CTools wizard 'show back' setting.
 *      - show cancel (optional): The CTools wizard 'show cancel' setting.
 *      - show return (optional): The CTools wizard 'show return' setting.
 *      - next text (optional): The CTools wizard 'next text' setting.
 *
 *    After you have defined your wizards, you then will need to create a folder
 *    in which your wizard will reside.  Each page of the wizard will get its
 *    own file within the wizard which should be named {MODULE}_{PAGE}.inc.
 *    Please see the sample module for more information.
 */
function hook_reg_wizard_info() {
  return array(
    'wizard_menu_path' => array(
      'title' => 'My Wizard',
      'object name' => 'my_wizard',
      'cancel message' => 'You just canceled me... Why did you do that!?',
      'pages' => array(
        'account' => t('Account Settings'),
        'role' => t('Role Settings'),
        'review' => t('Review'),
        'finish' => t('Finish')
      )
    ),
    'another_wizard_menu_path' => array(
      'title' => 'Another Wizard',
      'object name' => 'another_wizard',
      'cancel message' => 'You just canceled me... Why did you do that!?',
      'pages' => array(
        'account' => t('Account Settings'),
        'role' => t('Role Settings'),
        'review' => t('Review'),
        'finish' => t('Finish')
      )
    ),
  );
}
