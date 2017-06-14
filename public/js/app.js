$(".up-button").mousedown(function(){
  $.get("/pantilt/moveUp");
}).mouseup(function(){
  $.get("/pantilt/moveStop");
});

$(".left-button").mousedown(function(){
  $.get("/pantilt/moveLeft");
}).mouseup(function(){
  $.get("/pantilt/moveStop");
});

$(".right-button").mousedown(function(){
  $.get("/pantilt/moveRight");
}).mouseup(function(){
  $.get("/pantilt/moveStop");
});

$(".down-button").mousedown(function(){
  $.get("/pantilt/moveDown");
}).mouseup(function(){
  $.get("/pantilt/moveStop");
});

$(".zoom-tele").mousedown(function(){
  $.get("/pantilt/zoomTeleStd");
}).mouseup(function(){
  $.get("/pantilt/zoomStop");
});

$(".zoom-wide").mousedown(function(){
  $.get("/pantilt/zoomWideStd");
}).mouseup(function(){
  $.get("/pantilt/zoomStop");
});
