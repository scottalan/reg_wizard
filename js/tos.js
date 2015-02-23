(function ($) {
  $( document ).tooltip();
  //$('.agree-submit').tooltip();
  Drupal.behaviors.termsOfService = {
    attach: function(context, settings) {

      // This is the continue button on the member terms of service
      $('.reg-wizard-tos-form .next-button #edit-next').addClass('disabled');

      $('#terms-of-service').scroll(function () {
        if ($(this).scrollTop() == $(this)[0].scrollHeight - $(this).height()) {
          // This is the continue button on the member terms of service
          $('.reg-wizard-tos-form .next-button #edit-next').removeClass('disabled');
          // This is the agree button on founder terms of service.
          $('.agree-submit').removeClass('disabled');
        }
      });

    }
  };
})(jQuery);
