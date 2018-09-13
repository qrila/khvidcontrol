const appPath = `${window.location}`;
const socket = io(appPath);
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));

// Get the services for our endpoints
const positions = client.service('positions');
const videoinputs = client.service('videoinputs');

const camButton = (data) => {
  $.get(`/movecam/c?data=${data}::${document.getElementById('videosource').value}`);
}

const camMenuButton = (button, data) => {
  $(`.${button} button`).click(function(){
    camButton(data);
  });
};

const camArrowButton = (button, data) => {
  $(`.${button} button`).bind('mousedown touchstart', function(){
    camButton(data);
  }).bind('mouseup touchend', function(){
    camButton('moveStop');
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
    <div class="col-sm-5 col-md-4 col-xl-3">
      <button type="memory-button" value="${position.pantilt}::${position.zoom}::${position.cameraNumber}" class="mem-button btn btn-primary">
        <span aria-hidden="true">${position.subjectName}</span>
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
    <div class="col-sm-5 col-md-4 col-xl-3">
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
}).then(auxbuttons => addAUXSource(auxbuttons.data[0]));

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
  if (buttonValue[0] === 'media') {
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
        cameraNumber: buttonValue[2]
      }
    }).then(page =>
      getSourceInput({
        mixerIP: page.data[0].mixerIP,
        sourceInput: page.data[0].sourceInput
      })
    );
  }
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
