<?php if (isset($address)): ?>
  <div class="address">
    <?php if (isset($address['address_1'])): ?>
      <div><?php print $address['address_1'] . ' ' . $address['address_2']; ?></div>
    <?php endif; ?>
    <div><?php print $address['locality'] . ', ' . $address['administrative_area']; ?></div>
    <div><?php print $address['postal_code']; ?></div>
  </div>
<? endif ?>
