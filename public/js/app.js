$(".up-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveUp");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".left-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveLeft");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".right-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveRight");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".down-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveDown");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".zoom-tele button").bind("mousedown touchstart", function(){
  $.get("/movecam/zoomTeleStd");
}).bind("mouseup touchend", function(){
  $.get("/movecam/zoomStop");
});

$(".zoom-wide button").bind("mousedown touchstart", function(){
  $.get("/movecam/zoomWideStd");
}).bind("mouseup touchend", function(){
  $.get("/movecam/zoomStop");
});

$(".mem-button button").click(function() {
  // $.get(("/position"));
  $("#memoutput").text("testing");
});
