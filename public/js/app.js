const appPath = `${window.location}`;
const socket = io(appPath);
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the services for our endpoints
const positions = client.service('positions');
const videoinputs = client.service('videoinputs');
const videomixer = client.service('videomixer');
const cameras = client.service('cameras');

const camButton = (data) => {
  $.get(`/movecam/{"command":"cmd","action":"${data}","cameraID":"${document.getElementById('movecamera').value}"}`);
};

const camMenuButton = (button, data) => {
  $(`.${button} button`).click(function(){
    camButton(data);
  });
};

const camArrowButton = (button, data) => {
  $(`.${button} button`).bind('mousedown touchstart', function(){
    camButton(data);
  }).bind('mouseup touchend', function(){
    camButton(data.startsWith('zoom') ? 'zoomStop' : 'moveStop');
  });
};

const menuButtons = {
  'power-button'  :   'power',
  'menu-button'   :   'menuToggle',
  'menu-ok'       :   'menuOK',
  'menu-back'     :   'menuBack'
};

$.each(menuButtons, function(button, action) {
  camMenuButton(button, action);
});

const arrowButtons = {
  'up-button'     :   'moveUp',
  'left-button'   :   'moveLeft',
  'right-button'  :   'moveRight',
  'down-button'   :   'moveDown',
  'zoom-tele'     :   'zoomTeleStd',
  'zoom-wide'     :   'zoomWideStd'
};

$.each(arrowButtons, function(button, action) {
  camArrowButton(button, action);
});

function addCameraPosition(position) {
  const camPos = document.querySelector('.memoutput');
  camPos.insertAdjacentHTML('beforeend', `
    <div class="col-sm-4 col-md-4 col-xl-3">
      <button type="memory-button" value="${position._id}" class="mem-button btn btn-primary">
        <span aria-hidden="true">${position.subjectName}</span>
      </button>
    </div>
  `);
}

positions.find().then(camerabuttons => {
  _.sortBy(camerabuttons.data, ['sortNumber']).forEach(addCameraPosition);
});
positions.on('created', addCameraPosition);

document.getElementById('position-mem').addEventListener('submit', function(ev) {
  ev.preventDefault();
  const cameraID = this.cameraid.value;
  const subjectName = this.subjectname.value;

  $.get(`/movecam/{"command":"save","cameraID":"${cameraID}","subjectName":"${subjectName}"}`);

  $('#position-mem').find('input[type=text]').val('');
});

function addMediaSources(media) {
  const mediaSource = document.querySelector('.mediaoutput');
  mediaSource.insertAdjacentHTML('beforeend',`
    <div class="col-sm-4 col-md-4 col-xl-3">
      <button type="memory-button" value="media::${media.mixerIP}::${media.sourceInput}" class="mem-button btn btn-primary">
        <span aria-hidden="true">${media.sourceName}</span>
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

videomixer.find().then( mixers => {
  if(mixers.total > 0) {
    $('.add-video-mixer').addClass('hidden');
    $('#auxmode').removeClass('hidden');
    $('#auxprogram').text(mixers.data[0].auxProgram);
    $('#auxsource').text(mixers.data[0].auxSource);
  }
});

document.getElementById('video-mixer').addEventListener('submit', function(ev) {
  ev.preventDefault();

  videomixer.create({
    videomixerIP: this.videomixer.value,
    auxProgram: this.auxprogram.value,
    auxSource: this.auxsource.value,
  });

  $('#video-mixer').find('input[type=text]').val('');
  $('.add-video-mixer').addClass('hidden');
  $('#auxsource').removeClass('hidden');
});

document.getElementById('add-camera').addEventListener('submit', function(ev) {
  ev.preventDefault();
  const cameraName = this.name.value;
  const cameraIP = this.cameraip.value;
  const mixerInput = this.mixerinput.value;

  cameras.create({
    cameraName: cameraName,
    cameraIP: cameraIP,
    mixerInput: mixerInput
  });

  $('#add-camera').find('input[type=text]').val('');
  populateCameraList();
});

function populateCameraList() {
  $('#movecamera option').remove();
  $('#cameraid option').remove();
  cameras.find().then( cameras => {
    _.forEach(cameras.data, camera => {
      $('#movecamera').append(`<option value=${camera._id}>${camera.cameraName}</option>`);
      $('#cameraid').append(`<option value=${camera._id}>${camera.cameraName}</option>`);
    });
  });
}
populateCameraList();

// Initialize aux source selection buttons
$(document).on('click', 'button[type=mixeraux]', function() {
  $.get(`/mixerinputs/{"mixerAUX": "${this.value}"}`);
});

// Initialize saved camera position buttons
$(document).on('click', 'button[type=memory-button]', function() {
  $.get(`/movecam/{"command":"preset","positionID":"${this.value}"}`);
  positions.get(this.value).then( (position) => {
    cameras.get(position.cameraID).then( (camera) => {
      $.get(`/mixerinputs/{"mixerInput":${camera.mixerInput}}`);
    });
  });
});

$('select[name="cameranumber"]').prop('disabled', true);
$('select[name="sourcetype"]').change(function() {
  if($('select[name="sourcetype"]').val() === 'camera') {
    $('select[name="cameranumber"]').prop('disabled', false);
  } else {
    $('select[name="cameranumber"]').val('');
    $('select[name="cameranumber"]').prop('disabled', true);
  }
});
