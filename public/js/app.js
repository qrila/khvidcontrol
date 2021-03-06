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
const overlay = client.service('overlay');

var vidCtx = {};
var selectedCameraID = '';

const camButton = (data) => {
  if (selectedCameraID !== '') {
    const call = JSON.stringify({
      command: 'cmd',
      action: data,
      cameraID: selectedCameraID
    });
    $.get(`/movecam/${call}`);
  }
};

const camMenuButton = (button, data) => {
  $(`.${button} button`).click(function () {
    camButton(data);
  });
};

const camArrowButton = (button, data) => {
  $(`[name=${button}]`).bind('mousedown touchstart', function () {
    camButton(data);
  }).bind('mouseup touchend', function () {
    camButton(data.startsWith('zoom') ? 'zoomStop' : 'moveStop');
  });
};

const menuButtons = {
  'power-button': 'power',
  'menu-button': 'menuToggle',
  'menu-ok': 'menuOK',
  'menu-back': 'menuBack'
};

$.each(menuButtons, function (button, action) {
  camMenuButton(button, action);
});

$('.dpad').html(`
  <div class="position-control container">
    <div class="dpad-area row">
      <div class="up-button">
        <button type="button" name="up-button-slow" class="btn btn-secondary">
          <span class="material-icons">keyboard_arrow_up</span>
        </button>
        <button type="button" name="up-button" class="btn btn-primary">
          <span class="material-icons">arrow_upwards</span>
        </button>
      </div>
      <div class="left-button">
        <button type="button" name="left-button-slow" class="btn btn-secondary">
          <span class="material-icons">keyboard_arrow_left</span>
        </button>
        <button type="button" name="left-button" class="btn btn-primary">
          <span class="material-icons">arrow_back</span>
        </button>
      </div>
      <div class="right-button">
        <button type="button" name="right-button" class="btn btn-primary">
          <span class="material-icons">arrow_forward</span>
        </button>
        <button type="button" name="right-button-slow" class="btn btn-secondary">
          <span class="material-icons">keyboard_arrow_right</span>
        </button>
      </div>
      <div class="down-button">
        <button type="button" name="down-button" class="btn btn-primary">
          <span class="material-icons">arrow_downwards</span>
        </button>
        <button type="button" name="down-button-slow" class="btn btn-secondary">
          <span class="material-icons">keyboard_arrow_down</span>
        </button>
      </div>
    </div>
  </div>
  <div class="zoom-control container">
    <div class="zpad-area row">
      <button type="zoom-button" name="zoom-tele" class="btn btn-primary">
        <span class="material-icons">zoom_in</span>
      </button>
      <button type="zoom-button" name="zoom-wide" class="btn btn-primary">
        <span class="material-icons">zoom_out</span>
      </button>
    </div>
  </div>`
);

const arrowButtons = {
  'up-button': 'moveUp',
  'left-button': 'moveLeft',
  'right-button': 'moveRight',
  'down-button': 'moveDown',
  'up-button-slow': 'moveUpSlow',
  'left-button-slow': 'moveLeftSlow',
  'right-button-slow': 'moveRightSlow',
  'down-button-slow': 'moveDownSlow',
  'zoom-tele': 'zoomTeleStd',
  'zoom-wide': 'zoomWideStd'
};

$.each(arrowButtons, function (button, action) {
  camArrowButton(button, action);
});

function cameraPositionsButtons(positions) {
  let listString = '';
  positions.forEach(position => listString = listString.concat(
    `<div type="memory-div" class="col-6 col-sm-4 col-lg-3 col-xl-2" style="display:${position.visibilityMode && position.visibilityMode == 'poly' ? 'none' : 'block'} data-positionid="${position._id}">
    <button type="memory-button" value="${position._id}" class="mem-button btn btn-primary">
      <span aria-hidden="true">${position.subjectName}</span>
    </button>
  </div>`));
  document.querySelector('.memoutput').innerHTML = listString;
}

function positionsEditList(positions) {
  let listString = '';
  positions.forEach((position, idx) => listString = listString.concat(
    `<li class="list-group-item">
    <div class="container">
      <div class="row justify-content-between">
        <div id="${position._id}-name">${position.subjectName}</div>
        <div id="${position._id}-input" class="hide"><input id="${position._id}-input-value" value="${position.subjectName}"></input></div>
        <div id="${position._id}-edit" class="button-group btn-group-sm" role="group">
          <button type="position-orderup-button" value="${position._id}" class="btn btn-secondary ${idx < 2 ? 'disabled' : ''}"><span class="material-icons">keyboard_arrow_up</span></button>
          <button type="position-orderdown-button" value="${position._id}" class="btn btn-secondary ${idx === 0 || idx === positions.length - 1 ? 'disabled' : ''}"><span class="material-icons">keyboard_arrow_down</span></button>
          <button type="position-edit-button" value="${position._id}" class="btn btn-secondary"><span class="material-icons">edit</span></button>
          <button type="position-reframe-button" value="${position._id}::${position.cameraID}" class="btn btn-secondary"><span class="material-icons">control_camera</span></button>
          <button type="position-delete-button" value="${position._id}" class="btn btn-secondary ${idx === 0 ? 'disabled' : ''}"><span class="material-icons">delete_forever</span></button>
        </div>
        <div id="${position._id}-save" class="button-group btn-group-sm hide" role="group">
          <button type="position-save-button" value="${position._id}" class="btn btn-secondary"><span class="material-icons">save</span></button>
          <button type="position-cancel-button" value="${position._id}" class="btn btn-secondary"><span class="material-icons">cancel</span></button>
        </div>
      </div>
    </div>
  </li>`
  ));
  document.querySelector('#saved-positions > .list-group').innerHTML = listString;
}

$(document).on('click', 'button[type=position-orderup-button]', function () {
  const call = JSON.stringify({
    command: 'edit',
    positionID: this.value,
    sortdir: 'up'
  });
  $.get(`/movecam/${call}`);
});

$(document).on('click', 'button[type=position-orderdown-button]', function () {
  const call = JSON.stringify({
    command: 'edit',
    positionID: this.value,
    sortdir: 'down'
  });
  $.get(`/movecam/${call}`);
});

$(document).on('click', 'button[type=position-edit-button]', function () {
  document.getElementById(`${this.value}-name`).classList.add('hide');
  document.getElementById(`${this.value}-edit`).classList.add('hide');
  document.getElementById(`${this.value}-input`).classList.remove('hide');
  document.getElementById(`${this.value}-save`).classList.remove('hide');
});

$(document).on('click', 'button[type=position-reframe-button]', function () {
  const positionInfo = this.value.split('::');

  if (positionInfo != '') {
    selectedCameraID = positionInfo[1];
    $('button[type=position-reframe-save]').attr('value', this.value);
  }
  else { setCameraSelection(); }

  $('.position-edit').toggle();
});

$(document).on('click', 'button[type=position-reframe-save]', function () {
  const positionInfo = this.value.split('::');
  setCameraSelection();

  const call = JSON.stringify({
    command: 'edit',
    positionID: positionInfo[0],
    cameraID: positionInfo[1]
  });
  $.get(`/movecam/${call}`);

  $('.position-edit').toggle();
});

function setCameraSelection() {
  document.getElementsByName('camera-toggle').forEach((c) => {
    if (c.checked) { selectedCameraID = c.value; }
  });
}

$(document).on('click', 'button[type=position-delete-button]', function () {
  let confirmation = confirm('oletko ihan varma?');
  if (confirmation) {
    const call = JSON.stringify({
      command: 'remove',
      positionID: this.value
    });
    $.get(`/movecam/${call}`);
  }
});

$(document).on('click', 'button[type=position-cancel-button]', function () {
  document.getElementById(`${this.value}-name`).classList.remove('hide');
  document.getElementById(`${this.value}-edit`).classList.remove('hide');
  document.getElementById(`${this.value}-input`).classList.add('hide');
  document.getElementById(`${this.value}-save`).classList.add('hide');
});

$(document).on('click', 'button[type=position-save-button]', function () {
  document.getElementById(`${this.value}-name`).classList.remove('hide');
  document.getElementById(`${this.value}-edit`).classList.remove('hide');
  document.getElementById(`${this.value}-input`).classList.add('hide');
  document.getElementById(`${this.value}-save`).classList.add('hide');
  const newName = document.getElementById(`${this.value}-input-value`).value;

  const call = JSON.stringify({
    command: 'edit',
    positionID: this.value,
    subjectName: newName
  });
  $.get(`/movecam/${call}`);
});

async function drawPositions() {
  document.getElementById('memoutput').innerHTML = '';
  positions.find({
    query: {
      visibilityMode: 'button'
    }
  }).then(camerabuttons => {
    camerabuttons.data.sort((a, b) => a.sortNumber - b.sortNumber);
    positionsEditList(camerabuttons.data);
    cameraPositionsButtons(camerabuttons.data);
  });
}
positions.on('created', drawPositions);
positions.on('patched', drawPositions);
positions.on('removed', drawPositions);

drawPositions();

document.getElementById('position-mem').addEventListener('submit', function (ev) {
  ev.preventDefault();
  const call = JSON.stringify({
    command: 'save',
    cameraID: selectedCameraID,
    subjectName: this.subjectname.value
  });
  $.get(`/movecam/${call}`);

  $('#position-mem').find('input[type=text]').val('');
});

function inputsButtons(mediabuttons) {
  let listString = `
    <div type="memory-div" class="col-6 col-sm-4 col-lg-3 col-xl-2">
      <button class="mem-button btn btn-secondary mixercut" type="button">Cut</button>
    </div>
    <div type="memory-div" class="col-6 col-sm-4 col-lg-3 col-xl-2">
      <button class="mem-button btn btn-secondary fadetoblack" type="button">Fade To Black</button>
    </div>`;

  mediabuttons.forEach(media => listString = listString.concat(`
    <div class="col-6 col-sm-4 col-lg-3 col-xl-2">
      <button type="media-button" value="${media._id}" class="mem-button btn btn-primary">
        <span aria-hidden="true">${media.sourceName}</span>
      </button>
    </div>`));
  document.querySelector('.mediaoutput').innerHTML = listString;
}

async function drawInputs() {
  videoinputs.find().then(mediabuttons => {
    inputsButtons(mediabuttons.data);
  });
}
drawInputs();

videoinputs.on('created', drawInputs);

document.getElementById('add-media').addEventListener('submit', function (ev) {
  ev.preventDefault();

  videoinputs.create({
    sourceName: this.mediainput.value,
    mixerInput: this.mixerinputmedia.value,
  });

  $('#add-media').find('input[type=text]').val('');
});

videomixer.find().then(mixer => {
  if (mixer.total > 0) {
    $('.add-video-mixer').addClass('d-none');
    $('#auxprogram, #auxsource').removeClass('d-none');
    $('#auxprogram').text(mixer.data[0].auxProgram);
    $('#auxsource').text(mixer.data[0].auxSource);
  }
});

document.getElementById('video-mixer').addEventListener('submit', function (ev) {
  ev.preventDefault();
  const auxProgram = this.auxprogram.value;
  const auxSource = this.auxsource.value;

  videomixer.create({
    videomixerIP: this.videomixer.value,
    auxProgram: auxProgram,
    auxSource: auxSource,
  });

  $('#video-mixer').find('input[type=text]').val('');
  $('.add-video-mixer').addClass('d-none');
  $('#auxprogram, #auxsource').removeClass('d-none');
  $('#auxprogram').text(auxProgram);
  $('#auxsource').text(auxSource);
});

document.getElementById('add-camera').addEventListener('submit', function (ev) {
  ev.preventDefault();
  const cameraName = this.name.value;
  const cameraIP = this.cameraip.value;
  const mixerInput = this.mixerinputcamera.value;
  const rtspURL = this.rtspurl.value;

  cameras.create({
    cameraName: cameraName,
    cameraIP: cameraIP,
    mixerInput: mixerInput,
    rtspURL: rtspURL
  });

  $('#add-camera').find('input[type=text]').val('');
  populateCameraList();
});

async function populateCameraList() {
  $('#cameraid option').remove();
  const cameraInputs = await cameras.find();
  const sorted = cameraInputs.data.sort((a, b) => parseInt(a.mixerInput) - parseInt(b.mixerInput));

  sorted.forEach((camera, idx) => {
    $('#cameraid').append(`
      <input style="display:none" type="radio" id="camera-in-${camera._id}" name="camera-toggle" value="${camera._id}" ${idx === 0 ? 'checked' : ''}></input>
      <label class="btn btn-secondary" for="camera-in-${camera._id}">${camera.mixerInput}</label>
    `);
    if (webRtcCtx.video_url === null &&
      camera.rtspURL !== null &&
      camera.rtspURL !== undefined &&
      camera.rtspURL.length > 0) {
      webRtcCtx.video_url = camera.rtspURL; // only first found rtsp url is used
    }
    if (idx === 0) {
      selectedCameraID = camera._id;
    }
  });

  $('#cameraid > input:radio').on('click', function (e) {
    selectedCameraID = e.currentTarget.value;
  });
}
populateCameraList();

// Initialize aux source selection buttons
$(document).on('click', 'button.mixeraux', function () {
  const call = JSON.stringify({
    mixerAUX: this.value,
    cut: false,
    fadeToBlack: false
  });
  $.get(`/mixerinputs/${call}`);
});

// Initialize cut button
$(document).on('click', 'button.mixercut', function () {
  const call = JSON.stringify({
    mixerAUX: false,
    cut: true,
    fadeToBlack: false
  });
  $.get(`/mixerinputs/${call}`);
});

// Initialize fade to black button
$(document).on('click', 'button.fadetoblack', function () {
  const call = JSON.stringify({
    mixerAUX: false,
    cut: false,
    fadeToBlack: true
  });
  $.get(`/mixerinputs/${call}`);
});

// Initialize saved camera position buttons
$(document).on('click', 'button[type=memory-button]', function () {
  changeCamPos(this.value);
});

// Initialize media input buttons
$(document).on('click', 'button[type=media-button]', function () {
  videoinputs.get(this.value).then((media) => {
    const callMixer = JSON.stringify({
      mixerAUX: false,
      mixerInput: media.mixerInput,
      cut: false,
      fadeToBlack: false
    });
    $.get(`/mixerinputs/${callMixer}`);
  });
});

const svgNS = 'http://www.w3.org/2000/svg';
const overlaysvg = 'overlay';
const overlaygid = 'overlay-g';
const overlaygcamposid = 'cam-pos-id';

function addOverlay(camPosId) {
  overlay.find({ query: { positionId: camPosId } }).then((overlayElements) => {
    var group = document.createElementNS(svgNS, 'g');
    group.setAttribute(overlaygcamposid, camPosId);
    group.setAttribute('class', overlaygid);
    overlayElements.data.forEach(elementData => {
      addPolygon(group, elementData);
    });
    document.getElementById(overlaysvg).appendChild(group);
  });
}

function clickPolygon(overlayId, targetPosition, positionId) {
  if (vidCtx.inDeletePolygonMode) {
    deletePolygon(overlayId, targetPosition);
    exitPolyDeleteMode();
    return;
  }
  changeCamPos(targetPosition, positionId);
}

function addPolygon(group, elementData) {
  var polygon = document.createElementNS(svgNS, 'polygon');
  polygon.setAttribute('points', elementData.points);
  polygon.setAttribute('data-overlayid', elementData._id);
  polygon.addEventListener('click', function () {
    clickPolygon(elementData._id, elementData.targetPosition, elementData.positionId);
  });
  group.appendChild(polygon);
}

function changeCamPos(targetPos, currentPos) {
  if (targetPos !== 'undefined') {
    if (!currentPos) {
      var groups = document.getElementById(overlaysvg).getElementsByClassName(overlaygid);
      Array.from(groups).forEach(overlayGroup => {
        overlayGroup.style.visibility = 'hidden';
      });
    } else {
      $(`g[${overlaygcamposid}='${currentPos}']`)[0].style.visibility = 'hidden';
    }

    var gexisting = $(`g[${overlaygcamposid}='${targetPos}']`);
    if (gexisting !== 'undefined' && gexisting.length > 0) {
      gexisting[0].style.visibility = 'visible';
    } else {
      addOverlay(targetPos);
    }

    //vidCtx.prevPos = vidCtx.currentPos;
    vidCtx.currentPos = targetPos;

    // fill new current position to the owner name of new polygon in polymaker create state
    positions.find({
      query: {
        _id: vidCtx.currentPos
      }
    }).then(positions => {
      if (positions && Array.isArray(positions.data) && positions.data.length > 0) {
        var currentPosName = positions.data[0].subjectName;
        $('#poly-owner-name').text(currentPosName);
      }
    });

    // -- Code moved from Initialize saved camera position buttons
    const callCam = JSON.stringify({
      command: 'preset',
      positionID: targetPos
    });
    $.get(`/movecam/${callCam}`);
    positions.get(targetPos).then((position) => {
      cameras.get(position.cameraID).then((camera) => {
        const callMixer = JSON.stringify({
          mixerAUX: false,
          mixerInput: camera.mixerInput
        });
        $.get(`/mixerinputs/${callMixer}`);
      });
    });
    // -- Code moved end
  }
}

// Initialize video overlay buttons
// (see also camvideo.js)
$('#camvideo-start').on('click', function () {
  if (webRtcCtx.video_url === null || webRtcCtx.video_url.length == 0) {
    alert('Kameravideon RTSP URL puuttuu');
    return;
  }

  $('#camvideo-start').hide();
  startWebRTCVideoConnection();
  enableCamVideoUI();

  positions
    .find({ query: { sortNumber: 0 } })
    .then((position) => {
      if (!Array.isArray(position.data)) {
        console.error('No default camera position defined! (positions.find did not return array, positions will need one entry with sortNumber 0)');
      } else {
        changeCamPos(position.data[0]._id);
      }
    });
});

function getCSSStyle(className) {
  var x, sheets, classes;
  for (sheets = document.styleSheets.length - 1; sheets >= 0; --sheets) {
    classes = document.styleSheets[sheets].rules || document.styleSheets[sheets].cssRules;
    for (x = 0; x < classes.length; ++x) {
      if (classes[x].selectorText === className) {
        return (classes[x].cssText ? classes[x] : classes[x].style);
      }
    }
  }
  return false;
}

// this is called in camvideo.js, after opening camera
function enableCamVideoUI() {
  $('#camvideo-container').css('display', 'inline-block');
  $('#camvideo-container').css('height', $('#camvideo-container').css('width') * 9 / 16);
  $('#poly-mgmt-toggle').show();
  $('#poly-mgmt-toggle-cb').change(function () {
    if (this.checked)
      $('#poly-mgmt-tools').show();
    else
      $('#poly-mgmt-tools').hide();
  });
  $('#camvideo-reconnect').click(function () { reconnectWebRTCVideoConnection(); });
}

$('#poly-delete').click(function () {
  $('#poly-create').css('visibility', 'hidden');
  $('#poly-delete').hide();
  $('#poly-cancel-delete').show();

  var polygonStyle = getCSSStyle('polygon').style;
  polygonStyle.stroke = '#ff2200'; // hardcoded, should be in css?
  polygonStyle.fill = '#ee8844'; // hardcoded, should be in css?
  vidCtx.inDeletePolygonMode = true;
});

function initOriginalPolygonStyle() {
  var polygonStyle = getCSSStyle('polygon').style;
  if (vidCtx.orgPolygonStyle === undefined) {
    vidCtx.orgPolygonStyle = {
      stroke: polygonStyle.stroke,
      fill: polygonStyle.fill
    };
  }
}
initOriginalPolygonStyle();

function restoreOriginalPolygonStyle() {
  var polygonStyle = getCSSStyle('polygon').style;
  polygonStyle.stroke = vidCtx.orgPolygonStyle.stroke;
  polygonStyle.fill = vidCtx.orgPolygonStyle.fill;
}

function exitPolyDeleteMode() {
  $('#poly-create').css('visibility', 'visible');
  $('#poly-delete').show();
  $('#poly-cancel-delete').hide();
  restoreOriginalPolygonStyle();
  vidCtx.inDeletePolygonMode = false;
}

$('#poly-cancel-delete').click(function () {
  exitPolyDeleteMode();
});

function setPositionButtonVisibilityMode(positionId, visibilityMode) {
  const call = JSON.stringify({
    command: 'edit',
    positionID: positionId,
    visibilityMode: visibilityMode
  });
  $.get(`/movecam/${call}`);
  //console.log("setPositionButtonVisibilityMode performed call: ", call);
}

function deletePolygon(overlayId, targetPositionId) {
  setPositionButtonVisibilityMode(targetPositionId, 'button');
  overlay.remove(overlayId);
  $(`polygon[data-overlayid='${overlayId}']`).remove();
}

// switches to polymaker state, for creating a new polygon button for a camera target position
function createNewPoly() {
  $('#poly-mgmt-tools').hide();

  // first clear all options in polymaker list of targets
  $('#poly-target-name').html('');

  // populate target position names in polymaker list of targets
  positions.find( /*{ query: { visibilityMode: { $ne: "poly" }} }*/).then(camerabuttons => {
    _.sortBy(camerabuttons.data, ['sortNumber']).forEach(position => {
      $('#poly-target-name').append(`<option value="${position._id}">${position.subjectName}</option>`);
    });
    $('#poly-cb-hide-button').prop('checked', true);
    $('#poly-target-name option:last').attr('selected', 'selected');
  });

  startPolymaker(); // polymaker.js
}

$('#poly-target-name').change(function () {
  var positionId = this.value;
  positions.find({ query: { _id: positionId } }).then(
    position => {
      if (position && Array.isArray(position.data) && position.data.length > 0) {
        // disallow hiding first position button
        // (it's assumed that first button is the "overall view", and has sortNumber=0)
        var disabled = false;
        if (position.data[0].sortNumber == 0) {
          $('#poly-cb-hide-button').prop('checked', false);
          disabled = true;
        }
        $('#poly-cb-hide-button').prop('disabled', disabled);
      }
    });
});

$('#poly-create').click(function () {
  createNewPoly();
});

// callback, see polymaker.js
function polymakerCancel() {
  $('#poly-mgmt-tools').show();
}

// callback, see polymaker.js
function polymakerFinish(points) {
  var hideNormalTargetButton = $('#poly-cb-hide-button').prop('checked');

  $('#poly-mgmt-tools').show();

  var targetPositionId = $('#poly-target-name').val();
  overlay.create({
    positionId: vidCtx.currentPos,
    targetPosition: targetPositionId,
    points: points
  }).then(createdData => {
    var gexisting = $(`g[${overlaygcamposid}='${createdData.positionId}']`);
    if (gexisting !== 'undefined' && gexisting.length > 0) {
      addPolygon(gexisting[0], createdData);
    } else {
      addOverlay(createdData.positionId);
    }
    if (hideNormalTargetButton) {
      setPositionButtonVisibilityMode(targetPositionId, 'poly');
    }
  }).catch(function (err) {
    console.error('Could not create polygon data ' + err);
  });
}

initPolymaker(polymakerCancel, polymakerFinish); // in polymaker.js; need to initialize only once


