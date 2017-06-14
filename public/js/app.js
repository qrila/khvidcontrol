$(".up-button").mousedown(function(){
  $.get("/moveup", function(data){
    console.log("Data: " + data);
  });
}).mouseup(function(){
  console.log("Released up button");
});

$(".left-button").mousedown(function(){
  console.log("Pushed left button");
}).mouseup(function(){
  console.log("Released left button");
});

$(".right-button").mousedown(function(){
  console.log("Pushed right button");
}).mouseup(function(){
  console.log("Released right button");
});

$(".down-button").mousedown(function(){
  console.log("Pushed down button");
}).mouseup(function(){
  console.log("Released down button");
});

$(".zoom-tele").mousedown(function(){
  console.log("Pushed zoom-tele button");
}).mouseup(function(){
  console.log("Released zoom-tele button");
});

$(".zoom-wide").mousedown(function(){
  console.log("Pushed zoom-wide button");
}).mouseup(function(){
  console.log("Released zoom-wide button");
});
