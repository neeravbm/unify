<?php

/**
 * Set mega menu dropdown status, content and text format.
 *
 * @param int $mlid
 *   Menu link id.
 * @param int $status
 *   Status: 0 or 1.
 * @param string $content
 *   Mega menu content.
 * @param string $text_format
 *   Text format.
 */
function rc_megamenu_set($mlid, $status, $content, $text_format) {
  db_merge('rc_megamenu_content')
    ->key(array('mlid' => $mlid))
    ->fields(array(
      'status' => $status,
      'content' => $content,
      'text_format' => $text_format,
    ))
    ->execute();
}

/**
 * Delete mega menu.
 *
 * @param int $mlid
 *   Menu link id.
 */
function rc_megamenu_delete($mlid) {
  db_delete('rc_megamenu_content')
    ->condition('mlid', $mlid)
    ->execute();
}

/**
 * Returns mega menu information for a menu link.
 *
 * @param int $mlid
 *   Menu link id.
 *
 * @return array
 *   An array of mega menu content.
 */
function rc_megamenu_get($mlid) {
  $result = db_select('rc_megamenu_content', 'm')
    ->condition('m.mlid', $mlid)
    ->fields('m', array('status', 'content', 'text_format'))
    ->execute()
    ->fetchAssoc();

  if (!$result) {
    return array();
  }

  return $result;
}