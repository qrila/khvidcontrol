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
      <button type="memory-button" value="${position.pantilt}::${position.zoom}::${position.cameraNumber}" class="btn btn-primary">
        <span class="glyphicon glyphicon-facetime-video" aria-hidden="true"></span>
      </button>
    </div>
  `);
}

positions.find().then(camerabuttons => camerabuttons.data.forEach(addCameraPosition));
positions.on('created', addCameraPosition);

document.getElementById('position-mem').addEventListener('submit', function(ev) {
  ev.preventDefault();
  var cameraNumber = this.videosource.value;
  var subjectName = this.subjectname.value;

  positions.create({
    cameraNumber: cameraNumber,
    subjectName: subjectName
  });

  $('#position-mem').find('input[type=text]').val('');
});

function addMediaSources(media) {
  const mediaSource = document.querySelector('.mediaoutput');
  mediaSource.insertAdjacentHTML('beforeend',`
    <div class="col-sm-3 memory-button"><span>${media.sourceName}</span><br>
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
}).then(mediabuttons => mediabuttons.data.forEach(addMediaSources));

videoinputs.on('created', function(source){
  if (source.sourceType === 'media') {
    addMediaSources(source);
  }
});

function addAUXSource(auxsource) {
  const mediaSource = document.querySelector('#auxsource');
  mediaSource.insertAdjacentHTML('beforeend',`
    <div class="col-xs-offset-1 col-xs-5">
      <button type="memory-button" value="auxsource::deaf::${auxsource.mixerIP}" class="aux-button btn btn-primary">
        <span aria-hidden="true">Kuurot</span>
      </button>
    </div>
    <div class="col-xs-offset-1 col-xs-5">
      <button type="memory-button" value="auxsource::hearing::${auxsource.mixerIP}"" class="aux-button btn btn-primary">
        <span aria-hidden="true">Kuulevat</span>
      </button>
    </div>
  `);
}

videoinputs.find({
  query: {
    $limit: 1
  }
}).then(auxbuttons => addAUXSource(auxbuttons.data[0]))

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

function getSourceInput(input) {
  if(input.mixerAUX){
    $.get(`/mixerinputs/${input.mixerIP}::${input.mixerAUX}`);
  } else {
    $.get(`/mixerinputs/${input.mixerIP}::${input.sourceInput}`);
  }
}

$(document).on('click', 'button[type=memory-button]', function() {
  const buttonValue = this.value.split('::');
  if (this.value.split('::')[0] === 'media') {
    getSourceInput({
      mixerIP: buttonValue[1],
      sourceInput: buttonValue[2]
    });
  } else if (buttonValue[0] === 'auxsource') {
    getSourceInput({
      mixerAUX: buttonValue[1] == 'deaf' ? 'program' : 'source',
      mixerIP: buttonValue[2],
      sourceInput: null // Hearing media connection set to input source 1 in atemctrl.py
    });
  } else {
    $.get(`/movecam/p?data=${this.value}`);
    videoinputs.find({
      query: {
        $limit: 1,
        sourceType: 'camera',
        cameraNumber: this.value.split('::')[2]
      }
    }).then(page =>
      getSourceInput({
        mixerIP: page.data[0].mixerIP,
        sourceInput: page.data[0].sourceInput
      })
    );
  }
});

$('select[name="cameranumber"]').prop("disabled", true);
$('select[name="sourcetype"]').change(function() {
  if($('select[name="sourcetype"]').val() === 'camera') {
    $('select[name="cameranumber"]').prop("disabled", false);
  } else {
    $('select[name="cameranumber"]').val("");
    $('select[name="cameranumber"]').prop("disabled", true);
  }
});
