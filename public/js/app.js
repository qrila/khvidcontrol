const socket = io();
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the service for our `positions` endpoint
const positions = client.service('positions');

$(".power-button button").click(function(){
  $.get("/movecam/q?data=power::" + document.getElementById('videoinput').value);
});

$(".menu-button button").click(function(){
  $.get("/movecam/c?data=menuToggle::" + document.getElementById('videoinput').value);
});

$(".menu-ok button").click(function(){
  $.get("/movecam/c?data=menuOK::" + document.getElementById('videoinput').value);
});

$(".menu-back button").click(function(){
  $.get("/movecam/c?data=menuBack::" + document.getElementById('videoinput').value);
});

$(".up-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveUp::" + document.getElementById('videoinput').value);
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop::" + document.getElementById('videoinput').value);
});

$(".left-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveLeft::" + document.getElementById('videoinput').value);
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop::" + document.getElementById('videoinput').value);
});

$(".right-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveRight::" + document.getElementById('videoinput').value);
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop::" + document.getElementById('videoinput').value);
});

$(".down-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveDown::" + document.getElementById('videoinput').value);
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop::" + document.getElementById('videoinput').value);
});

$(".zoom-tele button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=zoomTeleStd::" + document.getElementById('videoinput').value);
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=zoomStop::" + document.getElementById('videoinput').value);
});

$(".zoom-wide button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=zoomWideStd::" + document.getElementById('videoinput').value);
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=zoomStop::" + document.getElementById('videoinput').value);
});

function addCameraPosition(position) {
  const camPos = document.querySelector('.memoutput');
  camPos.insertAdjacentHTML('beforeend', `
    <div class="col-sm-3 memory-button"><span>${position.name}</span><br>
      <button type="memory-button" value="${position.pantilt}::${position.zoom}::${position.videoSource}" class="btn btn-primary">
        <span class="glyphicon glyphicon-facetime-video" aria-hidden="true"></span>
      </button>
    </div>
  `);
}

positions.find().then(page => page.data.forEach(addCameraPosition));
positions.on('created', addCameraPosition);

document.getElementById('position-mem').addEventListener('submit', function(ev) {
  const videoSource = document.querySelector('[name="videoSource"]');
  const sourceName = document.querySelector('[name="name"]');

  client.service('positions').create({
    videoSource: videoSource.value,
    name: sourceName.value
  });

  camName.value = "";
  ev.preventDefault();
});

$(document).on('click', 'button[type=memory-button]', function() {
  if (this.value.split("::")[2] === "0") {
    $.get("/tbd/p?data=0"); // this needs own service to call atom switcher
  } else {
    $.get("/movecam/p?data=\"" + this.value + "\"");
  }
});
