<?php

/**
 * Implements hook_css_alter().
 */
function corporate_crackle_css_alter(&$css) {
  // Remove Drupal core css
  $exclude = array(
    'modules/aggregator/aggregator.css' => FALSE,
    'modules/block/block.css' => FALSE,
    'modules/book/book.css' => FALSE,
    'modules/comment/comment.css' => FALSE,
    'modules/dblog/dblog.css' => FALSE,
    'modules/field/theme/field.css' => FALSE,
    'modules/file/file.css' => FALSE,
    'modules/filter/filter.css' => FALSE,
    'modules/forum/forum.css' => FALSE,
    'modules/help/help.css' => FALSE,
    'modules/menu/menu.css' => FALSE,
    'modules/node/node.css' => FALSE,
    'modules/openid/openid.css' => FALSE,
    'modules/poll/poll.css' => FALSE,
    'modules/profile/profile.css' => FALSE,
    'modules/search/search.css' => FALSE,
    'modules/statistics/statistics.css' => FALSE,
    'modules/syslog/syslog.css' => FALSE,
    'modules/system/admin.css' => FALSE,
    'modules/system/maintenance.css' => FALSE,
    'modules/system/system.css' => FALSE,
    'modules/system/system.admin.css' => FALSE,
    'modules/system/system.base.css' => FALSE,
    'modules/system/system.maintenance.css' => FALSE,
    'modules/system/system.messages.css' => FALSE,
    'modules/system/system.menus.css' => FALSE,
    'modules/system/system.theme.css' => FALSE,
    'modules/taxonomy/taxonomy.css' => FALSE,
    'modules/tracker/tracker.css' => FALSE,
    'modules/update/update.css' => FALSE,
    'modules/user/user.css' => FALSE,
    'misc/vertical-tabs.css' => FALSE,
    // Remove contrib module CSS
    drupal_get_path('module', 'views') . '/css/views.css' => FALSE,
  );
  $css = array_diff_key($css, $exclude);
}

function corporate_crackle_breadcrumb($vars) {
  dsm($vars);
  return 'Hi';
}

/**
 * Implements hook_preprocess_page().
 */
function corporate_crackle_preprocess_page(&$vars) {
  $page = $vars['page'];
  if (!empty($page['sidebar_first']) && !empty($page['sidebar_second'])) {
    $vars['sidebar_first_width_classes'] = 'col-md-3';
    $vars['sidebar_second_width_classes'] = 'col-md-3';
    $vars['content_width_classes'] = 'col-md-6';
  }
  elseif (empty($page['sidebar_first']) && empty($page['sidebar_second'])) {
    $vars['content_width_classes'] = 'col-md-12';
  }
  elseif (!empty($page['sidebar_first'])) {
    $vars['sidebar_first_width_classes'] = 'col-md-4';
    $vars['content_width_classes'] = 'col-md-8';
  }
  elseif (!empty($page['sidebar_second'])) {
    $vars['sidebar_second_width_classes'] = 'col-md-4';
    $vars['content_width_classes'] = 'col-md-8';
  }
}