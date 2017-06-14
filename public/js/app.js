$(".up-button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveUp");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".left-button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveLeft");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".right-button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveRight");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".down-button").bind("mousedown touchstart", function(){
  $.get("/movecam/moveDown");
}).bind("mouseup touchend", function(){
  $.get("/movecam/moveStop");
});

$(".zoom-tele").bind("mousedown touchstart", function(){
  $.get("/movecam/zoomTeleStd");
}).bind("mouseup touchend", function(){
  $.get("/movecam/zoomStop");
});

$(".zoom-wide").bind("mousedown touchstart", function(){
  $.get("/movecam/zoomWideStd");
}).bind("mouseup touchend", function(){
  $.get("/movecam/zoomStop");
});
