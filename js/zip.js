/**
 * @file
 *   This will return a city and state based on zip code. This uses an API
 *   from http://www.zippopotam.us/. Another popular API is http://www.getziptastic.com/
 *   but it doesn't return lat and long. We need that if we want to set the timezone.
 */
(function ($) {
  Drupal.behaviors.wizardAddress = {
    attach: function (context, settings) {
      // Make sure we have a postal code field available. This is needed since
      // we have to load this file on the terms of agreement page before the
      // modal fires. It's loaded on each step of the wizard.
      var el = $('input#edit-postal-code').length;
      // Make sure the element exists. This will mean we are on the address form.
      if (el) {
        // Bind to the postal-code so we can trigger input when a complete postal
        // code has been entered.
        $('input#edit-postal-code').bind('input propertychange', function() {
          var value = $(this).val();
          // If the zip code is complete and is numeric.
          if ((value.length == 5) && ($.isNumeric(value))) {
            // Fire an ajax callback to get the information we need from the API.
            // Parameters: /country/zipcode
            $.ajax({
              url: "http://api.zippopotam.us/us/" + value,
              cache: false,
              dataType: "json",
              type: "GET",
              success: function(result, success) {

                if (result) {
                  // Auto-completes the city based on zip code.
                  $("input#edit-locality").val(result.places[0]['place name']);
                  // Auto-completes the state based on zip code.
                  $("select#edit-administrative-area").val(result.places[0]['state abbreviation']);

                  // @todo: Is there a better way to initiate the second ajax callback? (promise?)
                  setTimezone(result);
                }
              },
              error: function(result, success) {
                // We don't really need an error. If the API isn't working
                // then user won't even know. The only thing that will happen
                // is the City and State won't auto-fill.
              }
            });
          }
          if (value.length < 5) {
            $("input#edit-locality").val('');
            $("select#edit-administrative-area").val('');
          }
        });
      }
    }
  };

  /**
   * A function used to return the timezone using data from the ajax call above.
   *
   *
   * @link https://developers.google.com/maps/documentation/timezone/
   *
   * @param zipResult
   *   The result from the ajax call above.
   */
  function setTimezone(zipResult) {

    // Get a timestamp as required by googles api. Date.now() is in milliseconds
    // so this gives us a timestamp in seconds.
    var timestamp = Math.floor(Date.now() / 1000);
    // The latitude from the previous api call for zip code.
    var latitude = zipResult.places[0].latitude;
    // The longitude from the previous api call for zip code.
    var longitude = zipResult.places[0].longitude;

    // The url needed for our api call to get the timezone.
    // Parameters: location=latitude,longitude&timestamp=unix-timestamp
    var url = "https://maps.googleapis.com/maps/api/timezone/json?location=" + latitude + "," + longitude + "&timestamp=" + timestamp;

    // Fire an ajax callback to get the information we need from the API.
    $.ajax({
      url: url,
      cache: false,
      dataType: "json",
      type: "GET",
      success: function(result, success) {

        if (result) {
          $("select#edit-timezone").val(result.timeZoneId);
        }

      },
      error: function(result, success) {
        // We don't really need an error. If the API isn't working
        // then user won't even know. The only thing that will happen
        // is the City and State won't auto-fill.
      }
    });
  }
})(jQuery);
