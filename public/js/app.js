const socket = io();
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the service for our `positions` endpoint
const positions = client.service('positions');

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

function addCameraPosition(position) {
  const camPos = document.querySelector('.memoutput');
  camPos.insertAdjacentHTML('beforeend', `<span>camera: ${position.name}</span><br>
    <span style="padding-left:5px">pantilt: ${position.pantilt}</span><br>
    <span style="padding-left:5px">zoom: ${position.zoom}</span><br>`);
}

positions.find().then(page => page.data.forEach(addCameraPosition));
positions.on('created', addCameraPosition);

document.getElementById('position-mem').addEventListener('submit', function(ev) {
  const camInput = document.querySelector('[name="camera"]');
  const camName = document.querySelector('[name="name"]');

  client.service('positions').create({
    camera: camInput.value,
    name: camName.value
  });


  ev.preventDefault();
});
