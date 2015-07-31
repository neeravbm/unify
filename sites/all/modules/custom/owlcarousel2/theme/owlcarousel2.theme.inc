<?php

function theme_owlcarousel2_views($vars) {
  $output = array(
    '#theme' => 'owlcarousel2',
    '#items' => $vars['rows'],
    '#options' => $vars['options'],
    '#id' => 'views-' . $vars['view']->name . '-' . $vars['view']->current_display,
  );

  return drupal_render($output);
}

/**
 * Theme function for rendering owlcarousel.
 */
function theme_owlcarousel2($vars) {
  $output = array(
    '#prefix' => '<div class="owl-carousel" name="' . $vars['id'] . '">',
    '#suffix' => '</div>',
  );

  foreach ($vars['items'] as $key => $item) {
    $output[$key] = array(
      '#markup' => $item,
      '#prefix' => '<div>',
      '#suffix' => '</div>',
    );
  }

  $options = $vars['options'];

  module_load_include('inc', 'owlcarousel2', 'owlcarousel2.pages');
  $js_settings[$vars['id']] = owlcarousel2_get_options_from_settings($options);

  $module_path = drupal_get_path('module', 'owlcarousel2');

  $output['#attached']['js'][] = array(
    'data' => array('owlcarousel2' => $js_settings),
    'type' => 'setting',
  );

  $output['#attached']['library'][] = array('owlcarousel2', 'owlcarousel2');

  $output['#attached']['js'][$module_path . '/js/owlcarousel2.view.js'] = array(
    'scope' => 'footer',
  );
  $output['#attached']['css'][$module_path . '/css/owlcarousel2.css'] = array(
    'scope' => 'footer',
  );

  return drupal_render($output);
}

function theme_owlcarousel2_item_form_table($element) {
  $rows = $element['element'];

  $output = array(
    '#theme' => 'table',
    '#header' => array(t('Width'), t('Number of visible items')),
    '#rows' => array(),
    '#attached' => array(
      'css' => array(
        drupal_get_path(
          'module',
          'owlcarousel2'
        ) . '/css/owlcarousel2.form.css' => array(),
      ),
    ),
  );

  foreach (element_children($rows) as $index) {
    $row = array();
    $row[] = drupal_render($rows[$index]['width-' . $index]);
    $row[] = drupal_render($rows[$index]['item-' . $index]);

    $output['#rows'][] = $row;
  }

  return drupal_render($output);
}