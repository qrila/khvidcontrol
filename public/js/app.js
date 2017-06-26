const socket = io();
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the service for our `positions` endpoint
const positions = client.service('positions');

$(".power-button button").click(function(){
  $.get("/movecam/c?data=power");
});

$(".menu-button button").click(function(){
  $.get("/movecam/c?data=menuToggle");
});

$(".menu-ok button").click(function(){
  $.get("/movecam/c?data=menuOK");
});

$(".menu-back button").click(function(){
  $.get("/movecam/c?data=menuBack");
});

$(".up-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveUp");
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop");
});

$(".left-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveLeft");
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop");
});

$(".right-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveRight");
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop");
});

$(".down-button button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=moveDown");
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=moveStop");
});

$(".zoom-tele button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=zoomTeleStd");
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=zoomStop");
});

$(".zoom-wide button").bind("mousedown touchstart", function(){
  $.get("/movecam/c?data=zoomWideStd");
}).bind("mouseup touchend", function(){
  $.get("/movecam/c?data=zoomStop");
});

function addCameraPosition(position) {
  const camPos = document.querySelector('.memoutput');
  camPos.insertAdjacentHTML('beforeend', `
    <div class="col-sm-3 memory-button"><span>${position.name}</span><br>
      <button type="memory-button" value="${position.pantilt}::${position.zoom}" class="btn btn-primary">
        <span class="glyphicon glyphicon-facetime-video" aria-hidden="true"></span>
      </button>
    </div>
  `);
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

  camName.value = "";
  ev.preventDefault();
});

$(document).on('click', 'button[type=memory-button]', function() {
  console.log(this.value);
  $.get("/movecam/p?data=\"" + this.value + "\"");
});
