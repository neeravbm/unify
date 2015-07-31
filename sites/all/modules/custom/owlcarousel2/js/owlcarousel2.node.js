(function ($) {
  Drupal.behaviors.owlcarousel2_node = {
    attach: function (context, settings) {
      $('.node-owl-carousel-slideshow').each(function (index, value) {
        var id = $(value).attr('id');
        var options = settings.owlcarousel2[id];
        $(value).find('.field-name-field-owl-carousel-slide').children('.field-items').owlCarousel(options);
      });
    }
  };
}(jQuery));