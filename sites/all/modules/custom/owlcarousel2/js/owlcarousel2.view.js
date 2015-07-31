(function ($) {
  Drupal.behaviors.owlcarousel2_view = {
    attach: function (context, settings) {
      $('.view-content').children('.owl-carousel').each(function(index, value) {
        var name = $(value).attr('name');
        var options = settings.owlcarousel2[name];
        $(value).owlCarousel(options);
      });
    }
  };
}(jQuery));