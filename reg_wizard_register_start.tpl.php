<!--<div class="container">-->
<!--  <div class="text">-->
<!--    Please choose the type of registration below:-->
<!--  </div>-->
<!--  <div class="benefits-table">-->
<!--    --><?php //print $variables['benefits']; ?>
<!--  </div>-->
<!--  <br>-->
<!--</div>-->

<style type="text/css">
  .pricing-table {
    margin-top: 10%;
  }
  .pricing-table .price {
    font-size: 2rem;
    margin: 5%;
  }
  .pricing-table .plan {
    border-radius: 5px;
    text-align: center;
    background-color: #fff;
    -moz-box-shadow: 0 0 6px 2px #b0b2ab;
    -webkit-box-shadow: 0 0 6px 2px #b0b2ab;
    box-shadow: 0 0 6px 2px #b0b2ab;
  }

  .plan:hover {
    background-color: #fffff0;
    -moz-box-shadow: 0 0 12px 3px #b0b2ab;
    -webkit-box-shadow: 0 0 12px 3px #b0b2ab;
    box-shadow: 0 0 12px 3px #b0b2ab;
  }

  .plan {
    color: #000000;
    -moz-border-radius: 5px 5px 0 0;
    -webkit-border-radius: 5px 5px 0 0;
    border-radius: 5px 5px 0 0;
  }
  hr {
    background-color: #000000;
    border-color: #000000;
    color: #000000;
    width: 80%;
  }

</style>
<div class="pricing-table pricing-three-column row">
  <div class="plan col-xs-12 col-md-6">
    <div class="plan-name-supporter">
      <h2>Supporter</h2>
      <div class="price">FREE</div>
    </div>
    <ul>
      <?php $features = reg_wizard_benefits_common(); ?>
      <?php foreach ($features as $feature): ?>
        <?php print "<li class='plan-feature'>$feature</li><hr>" ?>
      <?php endforeach; ?>
      <?php print $variables['supporter_join']; ?>
    </ul>
  </div>
  <div style="z-index:55;" class="plan col-xs-12 col-md-6">
    <div class="plan-name-society">
      <h2>Society Member <span class="badge badge-warning">Engage!</span></h2>
      <div class="price" style="color: #008000">$75 / year</div>
      <div class="price">Supporter +</div>
    </div>
    <ul>
      <?php $features = reg_wizard_benefits_society(); ?>
      <?php foreach ($features as $feature): ?>
        <?php print "<li class='plan-feature'>$feature</li><hr>" ?>
      <?php endforeach; ?>
      <?php print $variables['society_join']; ?>
    </ul>
  </div>
</div>
