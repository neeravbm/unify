<?php

/**
 * Base form for owl carousel settings.
 */
function owlcarousel2_base_form(&$form, $form_state, $options) {

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#weight' => 5,
    '#tree' => 'TRUE',
  );

  $form['settings']['loop'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['loop']) ? $options['loop'] : TRUE,
    '#title' => t(
      'Enable looping: show first slide/item after showing the last one'
    ),
  );

  $form['settings']['margin'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($options['margin']) ? $options['margin'] : 10,
    '#title' => t('Margin between two slides/items in pixels'),
    '#size' => 3,
    '#attributes' => array(
      'class' => array('owlcarousel2-margin'),
    )
  );

  $form['settings']['stagePadding'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($options['stagePadding']) ? $options['stagePadding'] : 0,
    '#title' => t('Padding around each item in pixels'),
    '#size' => 3,
    '#attributes' => array(
      'class' => array('owlcarousel2-stagePadding'),
    )
  );

  $form['settings']['nav'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['nav']) ? $options['nav'] : FALSE,
    '#title' => t('Show next/previous links'),
    '#attributes' => array(
      'element-name' => 'nav',
    ),
  );

  $form['settings']['nav_prev_text'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($options['nav_prev_text']) ? $options['nav_prev_text'] : '<',
    '#title' => t('Previous Text'),
    '#attributes' => array(
      'class' => array('owlcarousel2-prev-text'),
    ),
    '#size' => 5,
    '#states' => array(
      'visible' => array(
        'input[element-name=nav]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['settings']['nav_next_text'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($options['nav_next_text']) ? $options['nav_next_text'] : '>',
    '#title' => t('Next Text'),
    '#attributes' => array(
      'class' => array('owlcarousel2-next-text'),
    ),
    '#size' => 5,
    '#states' => array(
      'visible' => array(
        'input[element-name=nav]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['settings']['nav_in_block_heading'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['nav_in_block_heading']) ? $options['nav_in_block_heading'] : FALSE,
    '#title' => t(
      'Display previous/next links to the right of block heading instead of with the slideshow/carousel'
    ),
    '#states' => array(
      'visible' => array(
        'input[element-name=nav]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['settings']['dots'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['dots']) ? $options['dots'] : TRUE,
    '#title' => t('Show dots below the slideshow/carousel?'),
  );

  $form['settings']['autoplay'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['autoplay']) ? $options['autoplay'] : TRUE,
    '#title' => t('Autoplay slideshow/carousel on page load'),
    '#attributes' => array(
      'element-name' => 'autoplay',
    ),
  );

  $form['settings']['autoplayHoverPause'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['autoplayHoverPause']) ? $options['autoplayHoverPause'] : TRUE,
    '#title' => t('Pause slideshow/carousel when mouse hovers over it'),
    '#states' => array(
      'visible' => array(
        'input[element-name=autoplay]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['settings']['multiple_item'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($options['multiple_item']) ? $options['multiple_item'] : FALSE,
    '#title' => t('Show more than one slide/item at a time'),
    '#attributes' => array(
      'element-name' => 'multiple_item',
    ),
  );

  $form['settings']['items'] = array(
    '#type' => 'container',
    '#title' => t('Items to show by element width'),
    '#states' => array(
      'visible' => array(
        'input[element-name=multiple_item]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['settings']['items']['rows'] = array(
    '#type' => 'container',
    '#theme' => 'owlcarousel2_item_form_table',
    '#attributes' => array(
      'class' => array('owlcarousel2-rows'),
    ),
    '#tree' => TRUE,
  );

  foreach (range(0, 5) as $index) {
    $form['settings']['items']['rows'][$index]['width-' . $index] = array(
      '#type' => 'textfield',
      '#default_value' => isset($options['items']['rows'][$index]['width-' . $index]) ? $options['items']['rows'][$index]['width-' . $index] : ($index === 0 ? 0 : ''),
      '#title' => '',
      '#size' => 5,
      '#maxlength' => 5,
      '#suffix' => 'px',
      '#attributes' => array(
        'class' => array('width-textfield'),
      ),
    );
    $form['settings']['items']['rows'][$index]['item-' . $index] = array(
      '#type' => 'textfield',
      '#default_value' => isset($options['items']['rows'][$index]['item-' . $index]) ? $options['items']['rows'][$index]['item-' . $index] : ($index === 0 ? 3 : ''),
      '#title' => '',
      '#size' => 3,
      '#maxlength' => 3,
      '#attributes' => array(
        'class' => array('item-textfield'),
      ),
    );
  }
}

/**
 * Validation callback for the base form. Verify that margin and padding values
 * are integers. Also check that widths and number of visible items are set
 * correctly.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function owlcarousel2_base_form_validate(&$form, &$form_state) {
  $config = array();
  if (!empty($form_state['values']['style_options'])) {
    $config = $form_state['values']['style_options']['settings'];
    list($success, $element, $msg) = owlcarousel2_form_settings_validate($config);
    if (!$success) {
      form_set_error($element, $msg);
    }
  }
  elseif (!empty($form_state['values']['settings'])) {
    $config = $form_state['values']['settings'];
    list($success, $element, $msg) = owlcarousel2_form_settings_validate($config);
    if (!$success) {
      form_set_error($element, $msg);
    }
  }
  /*elseif (!empty($form_state['field'])) {
    // This is if the slideshow is within an inline entity form.
    foreach ($form_state['field'] as $field_name => $field) {
      $field_info = $field[LANGUAGE_NONE]['field'];
      $instance = $field[LANGUAGE_NONE]['instance'];
      $type = $field_info['type'];
      $widget = $instance['widget']['type'];
      if ($type == 'entityreference' && $widget == 'inline_entity_form') {
        $target_type = $field_info['settings']['target_type'];
        $target_bundles = array_keys(
          $field_info['settings']['handler_settings']['target_bundles']
        );
        if ($target_type == 'node' && in_array(
            'owl_carousel_slideshow',
            $target_bundles
          )
        ) {
          // We need to check the slideshow settings.
          $bundle = $form_state['values'][$field_name][LANGUAGE_NONE]['actions']['bundle'];
          if ($bundle == 'owl_carousel_slideshow') {
            foreach ($form_state['values'][$field_name][LANGUAGE_NONE]['entities'] as $index => $field_array) {
              $field_form = $field_array['form'];
              $config = $field_form['settings'];
              list($success, $element, $msg) = owlcarousel2_form_settings_validate(
                $config
              );
              if (!$success) {
                form_set_error('form][0][entities][und][field_owl_carousel_slideshow', $msg);
              }
            }
          }
        }
      }
    }
  }*/
}

function owlcarousel2_form_settings_validate($config) {
  $margin = $config['margin'];
  if (isset($margin) && (!ctype_digit(strval($margin)) || $margin < 0)) {
    return array(
      FALSE,
      'margin',
      t('Margin has to be an integer greater than 0.')
    );
  }

  $padding = $config['stagePadding'];
  if (isset($padding) && (!ctype_digit(strval($padding)) || $padding < 0)) {
    return array(
      FALSE,
      'stagePadding',
      t('Padding has to be an integer greater than 0.')
    );
  }

  $multiple_item = $config['multiple_item'];
  $starts_with_zero = FALSE;
  if ($multiple_item) {
    $rows = $config['items']['rows'];
    foreach ($rows as $index => $row) {
      $width = $row['width-' . $index];
      $item = $row['item-' . $index];
      if (!is_width_set($width) && !is_item_set($item)) {
        // Both width and item are not set. Skip this row.
        continue;
      }

      if (!is_width_set($width)) {
        return array(
          FALSE,
          'width-' . $index,
          t(
            'Width in row @index needs to be set.',
            array('@index' => $index + 1)
          )
        );
        continue;
      }

      if (!is_item_set($item)) {
        return array(
          FALSE,
          'item-' . $index,
          t(
            'Number of visible items in row @index needs to be set.',
            array('@index' => $index + 1)
          )
        );
        continue;
      }

      if (!ctype_digit(strval($width)) || $width < 0) {
        return array(
          FALSE,
          'width-' . $index,
          t(
            'Width in row @index has to be an integer greater than or equal to 0.',
            array('@index' => $index + 1)
          )
        );
      }

      if (!ctype_digit(strval($item)) || $item < 1) {
        return array(
          FALSE,
          'item-' . $index,
          t(
            'Number of visible items in row @index has to be an integer greater than 0.',
            array('@index' => $index + 1)
          )
        );
      }

      if (strval($width) == '0') {
        $starts_with_zero = TRUE;
      }
    }

    if (!$starts_with_zero) {
      return array(
        FALSE,
        'width-0',
        t(
          'None of the width values in any row starts with 0. One width should be set to 0.'
        )
      );
    }
  }

  return array(TRUE, '', '');
}

/**
 * Check if width is set or not.
 *
 * @param string|int $width
 *   Width.
 *
 * @return bool
 *   TRUE if width is set and FALSE otherwise.
 */
function is_width_set($width) {
  if (!empty($width) || strval($width) === '0') {
    return TRUE;
  }

  return FALSE;
}

/**
 * Check if number of visible items is set or not.
 *
 * @param string|int $item
 *   Number of visible items.
 *
 * @return bool
 *   TRUE if the number of visible items is set and FALSE otherwise.
 */
function is_item_set($item) {
  if (!empty($item)) {
    return TRUE;
  }

  return FALSE;
}