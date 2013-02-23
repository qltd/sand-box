<?php
/**
 * @file
 * sand_box.features.inc
 */

/**
 * Implements hook_node_info().
 */
function sand_box_node_info() {
  $items = array(
    'linux_distributions' => array(
      'name' => t('Linux Distributions'),
      'base' => 'node_content',
      'description' => t('Information about linux distributions.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
