<?php

/**
 * Implements hook_views_plugins().
 */
function owlcarousel2_views_plugins() {
  return array(
    'style' => array(
      'owlcarousel2' => array(
        'title' => t('Owl Carousel Slideshow or Carousel'),
        'help' => t('Display the results as a slideshow or carousel.'),
        'handler' => 'views_owlcarousel2_plugin_style_owlcarousel2',
        'theme' => 'owlcarousel2_views',
        'theme path' => drupal_get_path('module', 'owlcarousel2') . '/theme',
        'theme file' => 'owlcarousel2.theme.inc',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'uses row class' => TRUE,
        'uses fields' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
        'use pager' => FALSE,
      )
    )
  );
}