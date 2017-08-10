const socket = io();
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the services for our endpoints
const positions = client.service('positions');
const videoinputs = client.service('videoinputs');

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
    <div class="col-sm-3 memory-button"><span>${position.subjectName}</span><br>
      <button type="memory-button" value="${position.pantilt}::${position.zoom}::${position.videoSource}" class="btn btn-primary">
        <span class="glyphicon glyphicon-facetime-video" aria-hidden="true"></span>
      </button>
    </div>
  `);
}

positions.find().then(page => page.data.forEach(addCameraPosition));
positions.on('created', addCameraPosition);

document.getElementById('position-mem').addEventListener('submit', function(ev) {
  ev.preventDefault();
  var videoSource = this.videosource.value;
  var subjectName = this.subjectname.value;

  positions.create({
    videoSource: videoSource,
    subjectName: subjectName
  });

  $('#position-mem').find('input[type=text]').val('');
});

function addMediaSources(media) {
  const mediaSource = document.querySelector('.mediaoutput');
  mediaSource.insertAdjacentHTML('beforeend',`
    <div class="col-sm-3 memory-button"<span>${media.sourceName}</span><br>
      <button type="memory-button" value="media::${media.mixerIP}::${media.sourceInput}" class="btn btn-primary">
        <span class="glyphicon glyphicon-play" aria-hidden="true"></span>
      </button>
    </div>
  `);
}

videoinputs.find({
  query: {
    sourceType: 'media'
  }
}).then(page => page.data.forEach(addMediaSources));

videoinputs.on('created', function(source){
  if (source.sourceType === 'media') {
    addMediaSources(source);
  }
});

document.getElementById('videoinput-mem').addEventListener('submit', function(ev) {
  ev.preventDefault();
  var sourceName = this.sourcename.value;
  var mixerIP = this.mixerip.value;
  var sourceInput = this.sourceinput.value;
  var sourceType = this.sourcetype.value;
  var cameraNumber = this.cameranumber.value;

  videoinputs.create({
    sourceName: sourceName,
    mixerIP: mixerIP,
    sourceInput: sourceInput,
    sourceType: sourceType,
    cameraNumber: cameraNumber
  });

  $('#videoinput-mem').find('input[type=text]').val('');
});

$(document).on('click', 'button[type=memory-button]', function() {
  if (this.value.split('::')[0] === 'media') {
    $.get('/tbd/p?data="' + this.value + '"'); // this needs own service to call atom switcher
  } else {
    $.get('/movecam/p?data="' + this.value + '"');
  }
});
