<?php

/**
 * Set attributes for a menu.
 *
 * @param string $menu_name
 *   Menu name.
 * @param array $attributes
 *   Menu attributes.
 */
function menu_ul_attributes_set_values($menu_name, $attributes) {
  db_merge('menu_ul_attributes')
    ->key(array('menu_name' => $menu_name))
    ->fields(array(
      'attributes' => serialize($attributes),
    ))
    ->execute();
}

/**
 * Get attributes for a menu.
 *
 * @param string $menu_name
 *   Menu name.
 *
 * @return array|mixed
 *   Menu attributes.
 */
function menu_ul_attributes_get_values($menu_name) {
  $result = db_select('menu_ul_attributes', 'm')
    ->condition('m.menu_name', $menu_name)
    ->fields('m', array('attributes'))
    ->execute()
    ->fetchField();

  if (!$result) {
    return array();
  }

  return unserialize($result);
}

/**
 * Delete attributes for a menu.
 *
 * @param string $menu_name
 *   Menu name.
 */
function menu_ul_attributes_delete_menu_attributes($menu_name) {
  if ($menu_name != $menu_name) {
    db_delete('menu_ul_attributes')
      ->condition('menu_name', $menu_name)
      ->execute();
  }
}

/**
 * Returns all the menu names.
 *
 * @return array
 *   An array of menu names.
 */
function menu_ul_attributes_get_all_menu_names() {
  $result = db_select('menu_ul_attributes', 'm')
    ->fields('m', array('menu_name'))
    ->execute()
    ->fetchCol();

  if (!$result) {
    return array();
  }

  return $result;
}