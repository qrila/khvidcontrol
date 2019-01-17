var _polymaker = {
  makingPolygon: false,
  svgPt: null, // used by _polymaker_onClick, only a single object is needed
  currPts: '',
  pointCount: 0,
  cancelCallback: null,
  finishCallback: null,
  lastPt: {x:0, y:0},
};

function _polymaker_onClick(evt)
{
  //console.log("_polymaker_onClick", evt);
  if (!_polymaker.makingPolygon)
    return; // only react to clicks when we're making a new polygon
  if (evt === null || evt.target === null)
    return;
  var svg = evt.target;
  // uncomment to disallow concave polygons:
  //if (!(svg instanceof SVGSVGElement))
  //  return;
  if (_polymaker.svgPt === null)
    _polymaker.svgPt = svg.createSVGPoint();
  var svgPt = _polymaker.svgPt;
  svgPt.x = evt.clientX;
  svgPt.y = evt.clientY;
  var cursorpt = svgPt.matrixTransform(svg.getScreenCTM().inverse());
  var x = Math.round(cursorpt.x);
  var y = Math.round(cursorpt.y);
  if (x !== _polymaker.lastPt.x && y !== _polymaker.lastPt.y) {
    _polymaker_addPoint(x, y);
    _polymaker.lastPt.x = x;
    _polymaker.lastPt.y = y;

    if (_polymaker.pointCount == 3)
    {
      // minimum 3 points was just reached, enable finish button
      var finishButton = document.getElementById('polymaker-finish');
      finishButton.style.visibility = 'visible';
    }
  }
}

function _polymaker_addPolySVG(selector)
{
  const pos = document.querySelector(selector);
  pos.insertAdjacentHTML('beforeend',
    `<svg id="svg-polymaker" viewBox="0 0 1920 1080" onclick="_polymaker_onClick(evt)" style="visibility:hidden">
       <polygon vector-effect="non-scaling-stroke" id="polymaker-poly" class="polymaker-poly"/>
     </svg>`);
  //<polygon points="100,100 140,298 190,278 210,178" vector-effect="non-scaling-stroke" id="ptest1"/>
}

function _polymaker_updatePoly(points)
{
  $('#polymaker-poly').attr('points', points);
}

function _polymaker_addPoint(x, y)
{
  if (_polymaker.currPts.length > 0)
    _polymaker.currPts += ' ';
  _polymaker.currPts += x + ',' + y;
  ++_polymaker.pointCount;
  _polymaker_updatePoly(_polymaker.currPts);
}

function _polymaker_start()
{
  _polymaker.makingPolygon = true;
  _polymaker.currPts = '';
  _polymaker.pointCount = 0;
  $('#svg-polymaker').attr('style', 'visibility:visible');
  _polymaker_updatePoly(_polymaker.currPts);
}

function _polymaker_finish()
{
  var resultPoints = getPolymakerPoly();
  var resultPointCount = getPolymakerPolyPointCount();
  _polymaker_cancel();
  if (_polymaker.finishCallback)
  {
    _polymaker.finishCallback(resultPoints, resultPointCount);
  }
}

function _polymaker_cancel()
{
  _polymaker.makingPolygon = false;
  $('#svg-polymaker').attr('style', 'visibility:hidden');
  _polymaker_updatePoly('');
  if (_polymaker.cancelCallback)
  {
    _polymaker.cancelCallback();
  }
}

function getPolymakerPoly()
{
  return _polymaker.currPts;
}

function getPolymakerPolyPointCount()
{
  return _polymaker.pointCount;
}

function initPolymaker(cancelCallback, finishCallback)
{
  _polymaker.cancelCallback = cancelCallback;
  _polymaker.finishCallback = finishCallback;
  _polymaker_addPolySVG('.svg-container');

  var tools = document.getElementById('polymaker-tools');
  var cancelButton = document.getElementById('polymaker-cancel');
  var finishButton = document.getElementById('polymaker-finish');
  if (tools && cancelButton && finishButton) {
    cancelButton.onclick = function() {
      tools.style.display = 'none';
      cancelButton.style.visibility = 'hidden';
      finishButton.style.visibility = 'hidden';
      _polymaker_cancel();
    };
    finishButton.onclick = function() {
      tools.style.display = 'none';
      cancelButton.style.visibility = 'hidden';
      finishButton.style.visibility = 'hidden';
      _polymaker_finish();
    };
  }
}

function startPolymaker()
{
  var tools = document.getElementById('polymaker-tools');
  var cancelButton = document.getElementById('polymaker-cancel');
  if (tools && cancelButton) {
    tools.style.display = 'block';
    cancelButton.style.visibility = 'visible';
    _polymaker_start();
  }
}
