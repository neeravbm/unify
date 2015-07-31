(function ($) {
  Drupal.behaviors.owlcarousel2_nav = {
    attach: function (context, settings) {
      $('.owl-block-prev').click(function (e) {
        var target = e.currentTarget;
        name = $(target).attr('name');
        $(target).closest('.block-views').find('.owl-carousel[name=' + name + ']').trigger('prev.owl.carousel');
        $(target).closest('.block-nodeblock').find('#' + name + '.node').find('.owl-carousel').trigger('prev.owl.carousel');
      });
      $('.owl-block-next').click(function (e) {
        var target = e.currentTarget;
        name = $(target).attr('name');
        $(target).closest('.block-views').find('.owl-carousel[name=' + name + ']').trigger('next.owl.carousel');
        $(target).closest('.block-nodeblock').find('#' + name + '.node').find('.owl-carousel').trigger('next.owl.carousel');
      });
    }
  }
})(jQuery);