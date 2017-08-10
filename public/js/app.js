const socket = io();
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the service for our `positions` endpoint
const positions = client.service('positions');

$('.power-button button').click(function(){
  $.get('/movecam/q?data=power::' + document.getElementById('videosource').value);
});

$('.menu-button button').click(function(){
  $.get('/movecam/c?data=menuToggle::' + document.getElementById('videosource').value);
});

$(".menu-ok button").click(function(){
  $.get('/movecam/c?data=menuOK::' + document.getElementById('videosource').value);
});

$(".menu-back button").click(function(){
  $.get('/movecam/c?data=menuBack::' + document.getElementById('videosource').value);
});

$('.up-button button').bind('mousedown touchstart', function(){
  $.get('/movecam/c?data=moveUp::' + document.getElementById('videosource').value);
}).bind('mouseup touchend', function(){
  $.get('/movecam/c?data=moveStop::' + document.getElementById('videosource').value);
});

$('.left-button button').bind('mousedown touchstart', function(){
  $.get('/movecam/c?data=moveLeft::' + document.getElementById('videosource').value);
}).bind('mouseup touchend', function(){
  $.get('/movecam/c?data=moveStop::' + document.getElementById('videosource').value);
});

$('.right-button button').bind('mousedown touchstart', function(){
  $.get('/movecam/c?data=moveRight::' + document.getElementById('videosource').value);
}).bind('mouseup touchend', function(){
  $.get('/movecam/c?data=moveStop::' + document.getElementById('videosource').value);
});

$('.down-button button').bind('mousedown touchstart', function(){
  $.get('/movecam/c?data=moveDown::' + document.getElementById('videosource').value);
}).bind('mouseup touchend', function(){
  $.get('/movecam/c?data=moveStop::' + document.getElementById('videosource').value);
});

$('.zoom-tele button').bind('mousedown touchstart', function(){
  $.get('/movecam/c?data=zoomTeleStd::' + document.getElementById('videosource').value);
}).bind('mouseup touchend', function(){
  $.get('/movecam/c?data=zoomStop::' + document.getElementById('videosource').value);
});

$('.zoom-wide button').bind('mousedown touchstart', function(){
  $.get('/movecam/c?data=zoomWideStd::' + document.getElementById('videosource').value);
}).bind('mouseup touchend', function(){
  $.get('/movecam/c?data=zoomStop::' + document.getElementById('videosource').value);
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
  const videoSource = document.querySelector('[name="videosource"]');
  const subjectName = document.querySelector('[name="subjectname"]');

  client.service('positions').create({
    videoSource: videoSource.value,
    subjectName: subjectName.value
  });

  subjectName.value = '';
  ev.preventDefault();
});

document.getElementById('videoinput-mem').addEventListener('submit', function(ev) {
  const sourceName = document.querySelector('[name="sourcename"]');
  const mixerIP = document.querySelector('[name="mixerip"]');
  const sourceInput = document.querySelector('[name="sourceinput"]');
  const sourceType = document.querySelector('[name="sourcetype"]');
  const cameraNumber = document.querySelector('[name="cameranumber"]');

  client.service('positions').create({
    sourceName: sourceName.value,
    mixerIP: mixerIP.value,
    sourceInput: sourceInput.value,
    sourceType: sourceType.value,
    cameraNumber: cameraNumber.value
  });

  sourceName.value = '';
  mixerIP.value = '';
  sourceInput.value = '';
  sourceType.value = '';
  cameraNumber.value = '';
  ev.preventDefault();
});

$(document).on('click', 'button[type=memory-button]', function() {
  if (this.value.split('::')[2] === '0') {
    $.get('/tbd/p?data=0'); // this needs own service to call atom switcher
  } else {
    $.get('/movecam/p?data="' + this.value + '"');
  }
});
