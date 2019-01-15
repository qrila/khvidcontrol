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

var vidCtx = {}

$(document).on('click', 'button[name=settings-button]', () => {
  $('.body-under-settings').toggleClass('hidden');
  $('#main-settings').toggleClass('hidden');
});

const camButton = (data) => {
  const call = JSON.stringify({
    command: 'cmd',
    action: data,
    cameraID: document.getElementById('cameraid').value
  });
  $.get(`/movecam/${call}`);
};

const camMenuButton = (button, data) => {
  $(`.${button} button`).click(function(){
    camButton(data);
  });
};

const camArrowButton = (button, data) => {
  $(`[name=${button}]`).bind('mousedown touchstart', function(){
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
  const isHidden = position.visibilityMode && position.visibilityMode == "poly";
  const displayAttr = 'style="display:' + (isHidden ? 'none"' : 'block"');
  camPos.insertAdjacentHTML('beforeend', `
    <div type="memory-div" class="col-xs-6 col-sm-4 col-md-3 col-xl-3" ${displayAttr} data-positionid="${position._id}">
      <button type="memory-button" value="${position._id}" class="mem-button btn btn-primary">
        <span aria-hidden="true">${position.subjectName}</span>
      </button>
    </div>
  `);
}

function modifyCameraPosition(position) {
  // currently only modification supported is changing visibilityMode:
  const isHidden = position.visibilityMode && position.visibilityMode == "poly";
  $(`div[type="memory-div"][data-positionid="${position._id}"]`).css("display", isHidden ? "none" : "block");
}


positions.find({
                query:{
                    visibilityMode: 
                        { $ne: "poly"}}})
    .then(camerabuttons => {
  _.sortBy(camerabuttons.data, ['sortNumber']).forEach(addCameraPosition);
});
positions.on('created', addCameraPosition);
positions.on('patched', modifyCameraPosition);

// Test code for changing visibilityMode:
// setTimeout(function() {
    // const call = JSON.stringify({
        // command: 'edit',
        // positionID: 'ThYbPsVbwj2ct51z',
        // visibilityMode: 'poly'
    // });
    // $.get(`/movecam/${call}`);
    // console.log("performed call: ", call);
// }, 2000);

document.getElementById('position-mem').addEventListener('submit', function(ev) {
  ev.preventDefault();
  const call = JSON.stringify({
    command: 'save',
    cameraID: this.cameraid.value,
    subjectName: this.subjectname.value
  });
  $.get(`/movecam/${call}`);

  $('#position-mem').find('input[type=text]').val('');
});

function addMediaSources(media) {
  const mediaSource = document.querySelector('.mediaoutput');
  mediaSource.insertAdjacentHTML('beforeend',`
    <div class="col-sm-4 col-md-4 col-xl-3">
      <button type="media-button" value="${media._id}" class="mem-button btn btn-primary">
        <span aria-hidden="true">${media.sourceName}</span>
      </button>
    </div>
  `);
}

videoinputs.find().then(mediabuttons => {
  mediabuttons.data.forEach(addMediaSources);
});
videoinputs.on('created', addMediaSources);

document.getElementById('add-media').addEventListener('submit', function(ev) {
  ev.preventDefault();

  videoinputs.create({
    sourceName: this.mediainput.value,
    mixerInput: this.mixerinputmedia.value,
  });

  $('#add-media').find('input[type=text]').val('');
});

videomixer.find().then( mixer => {
  if(mixer.total > 0) {
    $('.add-video-mixer').addClass('hidden');
    $('#auxmode').removeClass('hidden');
    $('#auxprogram span').text(mixer.data[0].auxProgram);
    $('#auxsource span').text(mixer.data[0].auxSource);  }
});

document.getElementById('video-mixer').addEventListener('submit', function(ev) {
  ev.preventDefault();
  const auxProgram = this.auxprogram.value;
  const auxSource = this.auxsource.value;

  videomixer.create({
    videomixerIP: this.videomixer.value,
    auxProgram: auxProgram,
    auxSource: auxSource,
  });

  $('#video-mixer').find('input[type=text]').val('');
  $('.add-video-mixer').addClass('hidden');
  $('#auxmode').removeClass('hidden');
  $('#auxprogram span').text(auxProgram);
  $('#auxsource span').text(auxSource);
});

document.getElementById('add-camera').addEventListener('submit', function(ev) {
  ev.preventDefault();
  const cameraName = this.name.value;
  const cameraIP = this.cameraip.value;
  const mixerInput = this.mixerinputcamera.value;

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
  const call = JSON.stringify({
    mixerAUX: this.value
  });
  $.get(`/mixerinputs/${call}`);
});

// Initialize saved camera position buttons
$(document).on('click', 'button[type=memory-button]', function() {
  changeCamPos(this.value);
});

// Initialize media input buttons
$(document).on('click', 'button[type=media-button]', function() {
  videoinputs.get(this.value).then( (media) => {
    const callMixer = JSON.stringify({
      mixerAUX: false,
      mixerInput: media.mixerInput
    });
    $.get(`/mixerinputs/${callMixer}`);
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

const svgNS = "http://www.w3.org/2000/svg";
const overlaysvg = "overlay";
const overlaygid = "overlay-g";
const overlaygcamposid = "cam-pos-id"

function addOverlay(camPosId){
  overlay.find({ query :{ positionId : camPosId } }).then( (overlayElements) => {
    var group = document.createElementNS(svgNS, "g");
    group.setAttribute(overlaygcamposid, camPosId);
    group.setAttribute("class", overlaygid); 
    overlayElements.data.forEach(elementData => {
      addPolygon(group, elementData);
    });
    document.getElementById(overlaysvg).appendChild(group);
    });
}

function addPolygon(group, elementData){
  var polygon = document.createElementNS(svgNS, "polygon");
  polygon.setAttribute("points", elementData.points);
  polygon.addEventListener('click', function() { changeCamPos(elementData.targetPosition, elementData.positionId) });
  group.appendChild(polygon);
}

function changeCamPos(targetPos, currentPos) {
  //console.log("AAF!:", targetPos + " " + currentPos);
  if (targetPos !== 'undefined') {
    if (!currentPos) {
        var groups = document.getElementById(overlaysvg).getElementsByClassName(overlaygid);
        Array.from(groups).forEach(overlayGroup => {
            overlayGroup.style.visibility = "hidden";
        });
    } else {
        $(`g[${overlaygcamposid}='${currentPos}']`)[0].style.visibility = "hidden";
    }
    
    var gexisting = $(`g[${overlaygcamposid}='${targetPos}']`);
    if (gexisting !== 'undefined' && gexisting.length > 0) {
        gexisting[0].style.visibility = "visible";
    } else {
        addOverlay(targetPos);
    }

    //vidCtx.prevPos = vidCtx.currentPos;
    vidCtx.currentPos = targetPos;

    // fill new current position to polymaker poly owner name
    positions.find({query:{_id:vidCtx.currentPos}}).then(
        positions => {
            if (positions && Array.isArray(positions.data) && positions.data.length > 0)
            {
                //console.log(positions.data[0].subjectName);
                var currentPosName = positions.data[0].subjectName;
                $('#poly-owner-name').text(currentPosName);
                var disabled = false;
                if (positions.data[0].sortNumber == 0)
                {
                    $('#poly-cb-hide-button').prop('checked', false);
                    disabled = true;
                }
                $('#poly-cb-hide-button').prop('disabled', disabled);
            }
        });

    // -- Code moved from Initialize saved camera position buttons
    const callCam = JSON.stringify({
      command: 'preset',
      positionID: targetPos
    });
    $.get(`/movecam/${callCam}`);
    positions.get(targetPos).then( (position) => {
      cameras.get(position.cameraID).then( (camera) => {
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
$('#camvideo-start').on('click', function() {
    positions
        .find({  query :{ sortNumber: 0 }  })
            .then((position) => 
    {
    if (!Array.isArray(position.data)) {
      console.error("No default camera position defined! (positions.find did not return array, positions will need one entry with sortNumber 0)");
    } else {
      // console.log("ASDF!!:", position.data[0]._id);
        changeCamPos(position.data[0]._id);
    }
  });
});

function createNewPoly() {
    var createButton = document.getElementById("polymaker-create");
    createButton.style.display = "none";

    // $('button[type=memory-button]').each(function(index) {
        // console.log(index + ": " + $(this).attr('value'));
    // });

    // clear all options first
    $('#poly-target-name').html('');

    // populate poly target names
    positions.find( /*{ query: { visibilityMode: { $ne: "poly" }} }*/ )
        .then(camerabuttons => { _.sortBy(camerabuttons.data, ['sortNumber']).forEach(position => {
                $('#poly-target-name').append(`<option value="${position._id}">${position.subjectName}</option>`);
                });
              });

    startPolymaker();
}

// see polymaker.js
function polymakerCancel() {
    $("#polymaker-create").show();
}

// see polymaker.js
function polymakerFinish(points, pointCount) {
    var createButton = document.getElementById("polymaker-create");
    createButton.style.display = "block";
    
    overlay.create({
        positionId: vidCtx.currentPos,
        targetPosition: $('#poly-target-name').val(),
        points: points
    })
        .then(createdData => { 
                //console.log(createdData);
                var gexisting = $(`g[${overlaygcamposid}='${createdData.positionId}']`);
            if (gexisting !== 'undefined' && gexisting.length > 0) {
                addPolygon(gexisting[0], createdData);
                //console.log("existing g" + gexisting[0]);
            } else {
                addOverlay(createdData.positionId);
                //console.log("not existing g, add " + createdData.positionId);
            }
            })
        .catch(function(err){console.error("Could not create polygon data " + err);});
    alert("" + pointCount + " polygon points: " + points);
}

$("#polymaker-create").click(function() {
    $("#polymaker-create").hide();
    createNewPoly();
});

initPolymaker(polymakerCancel, polymakerFinish);


