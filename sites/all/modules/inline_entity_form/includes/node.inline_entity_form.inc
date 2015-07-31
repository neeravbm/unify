<?php

/**
 * @file
 * Defines the inline entity form controller for Nodes.
 */

class NodeInlineEntityFormController extends EntityInlineEntityFormController {

  /**
  * Overrides EntityInlineEntityFormController::defaultLabels().
   */
  public function defaultLabels() {
    $labels = array(
      'singular' => t('node'),
      'plural' => t('nodes'),
    );
    return $labels;
  }

  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  public function tableFields($bundles) {
    $fields = parent::tableFields($bundles);
    $fields['status'] = array(
      'type' => 'property',
      'label' => t('Status'),
      'weight' => 100,
    );

    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $node = $entity_form['#entity'];
    $type = node_type_get_type($node);
    $extra_fields = field_info_extra_fields('node', $node->type, 'form');

    // Do some prep work on the node, similarly to node_form().
    if (!isset($node->title)) {
      $node->title = NULL;
    }
    node_object_prepare($node);

    $entity_form['title'] = array(
      '#type' => 'textfield',
      '#title' => check_plain($type->title_label),
      '#required' => TRUE,
      '#default_value' => $node->title,
      '#maxlength' => 255,
      // The label might be missing if the Title module has replaced it.
      '#weight' => !empty($extra_fields['title']) ? $extra_fields['title']['weight'] : -5,
    );
    $entity_form['status'] = array(
      '#type' => 'radios',
      '#access' => user_access('administer nodes'),
      '#title' => t('Status'),
      '#default_value' => $node->status,
      '#options' => array(1 => t('Published'), 0 => t('Unpublished')),
      '#required' => TRUE,
      '#weight' => 99,
    );

    $langcode = entity_language('node', $node);
    field_attach_form('node', $node, $entity_form, $form_state, $langcode);

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormValidate().
   * Validates the entity form by calling node_validate.
   */
  public function entityFormValidate($entity_form, &$form_state) {
    parent::entityFormValidate($entity_form, $form_state);

    // When saving a node we need to properly instantiate node_validate and hook_node_validate
    // These function assume they are validating an entire form, but in this instance they are acutally only validating a form-element
    // To ensure proper behavior we need to reset the static errors and validation-limits (see form_set_error function)
    // Once node_validate has done it's work we then merge any validation errors back into the overall error set.

    // Reset the validation limits
    $validation_limits = &drupal_static('form_set_error:limit_validation_errors');
    $saved_validation_limits = $validation_limits;
    $validation_limits = NULL;

    // Reset the static errors array
    $form_errors = &drupal_static('form_set_error', array());
    $saved_form_errors = $form_errors;
    $form_errors = array();

    // Run the form-validators
    $child_form_state = form_state_defaults();
    $child_form_state['values'] = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);
    node_validate($entity_form['#entity'], $entity_form, $child_form_state);

    // Get the form errors and correct their path to point to the proper element within the subform
    $errors = form_get_errors();
    if (!empty($errors)) {
      $parents_path = implode('][', $entity_form['#parents']);
      foreach ($errors as $errpath => $error) {
        $form_errors[$parents_path . '][' . $errpath] = $error;
      }
    }

    // Put saved errors back in place
    $form_errors = array_merge($form_errors, $saved_form_errors);

    // Put saved validation limits back in place
    $validation_limits = $saved_validation_limits;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);

    node_submit($entity_form['#entity']);
    $child_form_state = form_state_defaults();
    $child_form_state['values'] = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);
    foreach (module_implements('node_submit') as $module) {
      $function = $module . '_node_submit';
      $function($entity_form['#entity'], $entity_form, $child_form_state);
    }
  }
}
