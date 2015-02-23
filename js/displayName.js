/**
 * @file
 *   This will return a city and state based on zip code. This uses an API
 *   from http://www.zippopotam.us/. Another popular API is http://www.getziptastic.com/
 *   but it doesn't return lat and long. We need that if we want to set the timezone.
 */
(function ($) {
  Drupal.behaviors.wizardDisplayname = {
    attach: function (context, settings) {
      // Make sure we have a mail field available. This is needed since
      // we have to load this file on the terms of agreement page before the
      // modal fires. It's loaded on each step of the wizard.
      var first = $('input#edit-first-name').length;
      var last = $('input#edit-last-name').length;
      // Make sure the element exists. This will mean we are on the address form.
      if (first && last) {
        // Bind to the mail field so we can trigger input as the field is being completed.
        $('input#edit-last-name').bind('input propertychange', function() {
          var lastname = $(this).val();
          var firstname = $('input#edit-first-name').val();
          // As the user types an email address it sets the value in the username field.
          if (firstname.length > 0 && lastname.length > 0) {
            $("input#edit-display-name").val(firstname + ' ' + lastname);
          }
          else {
            $("input#edit-display-name").val('');
          }
        });
      }
    }
  };
})(jQuery);
