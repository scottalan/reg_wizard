<div class="payment-errors"></div>
<div class="payment-success"></div>

<?php print drupal_render($form); ?>
<!---->
<!--<button type="submit" id="stripe-submit">Submit Payment</button>-->

<?php if (!$form['status']['#value']): ?>
  <div class="info">
    <?php print t('By clicking "Process Payment" you are authorizing CEDI Society to
    charge your card. We will open a secure payment portal to process your payment.
    We will not store your credit card number. When the payment is complete please
    click "Continue"".'); ?>
  </div>
<?php else: ?>
  <div class="payment-status"><h2><?php print t('Thank you for your payment!'); ?></h2></div>
<?php endif; ?>

<form action="" method="POST" id="stripe-button">
  <script
    src="https://checkout.stripe.com/checkout.js" class="stripe-button"
    data-key="pk_test_GRoL2rf3UuhOo5bRHyGEizor"
    data-amount="7500"
    data-name="Society Member"
    data-description="12 month subscription"
    data-zip-code="true"
    data-email="<?php print isset($_SESSION[SOCIETY_REGISTRATION]['mail']) ? $_SESSION[SOCIETY_REGISTRATION]['mail'] : ''; ?>"
    data-label="Process Payment"
    data-allow-remember-me="false"
    data-image=<?php print $GLOBALS['base_url'] . "/sites/default/files/society-logo.jpg"; ?>>
  </script>
</form>
