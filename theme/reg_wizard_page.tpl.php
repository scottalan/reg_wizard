<?php
/**
 * Available variables:
 *
 * $ctools_trail:
 *
 * $sub_theme:
 *
 * $next:
 *
 * $previous:
 *
 * $cancel:
 */
?>

<div class="container">
  <div class="row form-group">
    <div class="col-xs-12">
      <ul class="nav nav-pills nav-justified thumbnail setup-panel">
        <?php foreach ($variables['trail'] as $key => $info): ?>
        <li class="<?php print $info['state']; ?>">
          <a href="#">
            <h4 class="list-group-item-heading"><?php print $info['title']; ?></h4>
            <p class="list-group-item-text"><?php print $info['description']; ?></p>
          </a>
        </li>
        <?php endforeach; ?>
      </ul>
    </div>
  </div>
</div>

<div class="container">
  <div class="reg-wizard col-xs-12">
    <div class="reg-wizard-content">
      <?php
      // Now print the theme...
      print theme($inner_template, $form);
      ?>
    </div>
  </div>
</div>

<?php if ($next || $previous || $cancel || $finish): ?>
  <div class="container">
    <div class="col-xs-6">
      <div class="pull-left">
        <span class="next-button"><?php print $next; ?></span>
        <span class="previous-button"><?php print $previous; ?></span>
        <span class="previous-button"><?php print $finish; ?></span>
      </div>
      <div class="pull-right">
        <span class="cancel-button"><?php print $cancel; ?></span>
      </div>
    </div>
  </div>
<? endif; ?>
