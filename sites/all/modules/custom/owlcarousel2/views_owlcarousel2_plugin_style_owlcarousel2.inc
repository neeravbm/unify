<?php


class views_owlcarousel2_plugin_style_owlcarousel2 extends views_plugin_style {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();


    $options['instance'] = array('default' => 'default');
    return $options;
  }

  /**
   * Show a form to edit the style options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options;

    form_load_include($form_state, 'inc', 'owlcarousel2', 'owlcarousel2.form');
    owlcarousel2_base_form($form, $form_state, $options);
  }

  /**
   * Validate options form.
   */
  function options_validate(&$form, &$form_state) {
    owlcarousel2_base_form_validate($form, &$form_state);
  }

  /**
   * Additionally format saved instance.
   */
  function options_submit(&$form, &$form_state) {
    $settings = $form_state['values']['style_options'];
    $config = array_merge($settings['settings']);

    // Keep default value structure.
    $form_state['values']['style_options'] = $config;
  }

  /**
   * Make sure that pager is not enabled.
   */
  function validate() {
    $errors = parent::validate();
    if ($this->display->handler->use_pager()) {
      $errors[] = t(
        'The Owl Carousel style cannot be used with a pager. Disable the "Use pager" option for this display.'
      );
    }
    return $errors;
  }
}