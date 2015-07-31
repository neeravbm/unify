<?php

/**
 * Returns options array that can be used for owl carousel from form settings.
 *
 * @param array $settings
 *   Settings array set in the form.
 *
 * @return array
 *   Options array.
 */
function owlcarousel2_get_options_from_settings($settings) {
  $options = array();

  if (!sizeof($settings)) {
    return $options;
  }

  $multiple_item = $settings['multiple_item'];
  if ($multiple_item) {
    $rows = $settings['items']['rows'];
    $responsive = array();
    foreach ($rows as $index => $row) {
      $width = $row['width-' . $index];
      $item = $row['item-' . $index];
      if (!isset($width) || !isset($item)) {
        continue;
      }
      $responsive[$width] = array(
        'items' => intval($item),
      );
    }
    $options['responsive'] = $responsive;
    $options['responsiveClass'] = TRUE;
  }
  else {
    $options['items'] = 1;
  }

  $options += array(
    'loop' => $settings['loop'] ? TRUE : FALSE,
    'margin' => intval($settings['margin']),
    'stagePadding' => intval($settings['stagePadding']),
    'nav' => ($settings['nav'] && !$settings['nav_in_block_heading']) ? TRUE : FALSE,
    'dots' => $settings['dots'] ? TRUE : FALSE,
    'autoplay' => $settings['autoplay'] ? TRUE : FALSE,
    'autoplayHoverPause' => $settings['autoplayHoverPause'] ? TRUE : FALSE,
  );

  if ($settings['nav'] && !$settings['nav_in_block_heading']) {
    $navText = $settings['nav'] ? array(
      $settings['nav_prev_text'],
      $settings['nav_next_text']
    ) : FALSE;
    $options['navText'] = $navText;
  }

  return $options;
}

/**
 * Returns owl carousel settings for a node.
 *
 * @param int $nid
 *   Node id.
 *
 * @return array|mixed
 *   Owl carousel form settings.
 */
function owlcarousel2_get_settings($nid) {
  $result = db_select('owlcarousel2_settings', 'o')
    ->condition('o.nid', $nid)
    ->fields('o', array('settings'))
    ->execute()
    ->fetchField();

  if (!$result) {
    return array();
  }

  return unserialize($result);
}