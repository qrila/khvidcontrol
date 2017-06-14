$(".up-button").mousedown(function(){
  $.get("/movecam/moveUp");
}).mouseup(function(){
  $.get("/movecam/moveStop");
});

$(".left-button").mousedown(function(){
  $.get("/movecam/moveLeft");
}).mouseup(function(){
  $.get("/movecam/moveStop");
});

$(".right-button").mousedown(function(){
  $.get("/movecam/moveRight");
}).mouseup(function(){
  $.get("/movecam/moveStop");
});

$(".down-button").mousedown(function(){
  $.get("/movecam/moveDown");
}).mouseup(function(){
  $.get("/movecam/moveStop");
});

$(".zoom-tele").mousedown(function(){
  $.get("/movecam/zoomTeleStd");
}).mouseup(function(){
  $.get("/movecam/zoomStop");
});

$(".zoom-wide").mousedown(function(){
  $.get("/movecam/zoomWideStd");
}).mouseup(function(){
  $.get("/movecam/zoomStop");
});
