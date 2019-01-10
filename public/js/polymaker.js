var _polymaker = {
	makingPolygon: false,
	svgPt: null, // used by _polymaker_onClick, only a single object is needed
	currPts: "",
	callback: null,
};

function _polymaker_onClick(evt)
{
	//console.log("_polymaker_onClick", evt);
	if (!_polymaker.makingPolygon)
		return; // only react to clicks when we're making a new polygon
	if (evt === null || evt.target === null)
		return;
	var svg = evt.target;
	if (!svg instanceof SVGSVGElement)
		return;
	if (_polymaker.svgPt === null)
		_polymaker.svgPt = svg.createSVGPoint();
	var svgPt = _polymaker.svgPt;
	svgPt.x = evt.clientX;
	svgPt.y = evt.clientY;
	var cursorpt = svgPt.matrixTransform(svg.getScreenCTM().inverse());
	_polymaker_addPoint(cursorpt.x, cursorpt.y);
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
	$('#polymaker-poly').attr("points", points);
}

function _polymaker_addPoint(x, y)
{
	if (_polymaker.currPts.length > 0)
		_polymaker.currPts += ' ';
	_polymaker.currPts += x + ',' + y;
	_polymaker_updatePoly(_polymaker.currPts);
}

function _polymaker_start()
{
	_polymaker.makingPolygon = true;
	_polymaker.currPts = "";
	$('#svg-polymaker').attr("style", "visibility:visible");
	_polymaker_updatePoly(_polymaker.currPts);
}

function _polymaker_finish()
{
	var resultPoints = getPolymakerPoly();
	_polymaker_cancel();
	if (_polymaker.callback)
	{
		_polymaker.callback(resultPoints);
	}
}

function _polymaker_cancel()
{
	_polymaker.makingPolygon = false;
	$('#svg-polymaker').attr("style", "visibility:hidden");
	_polymaker_updatePoly("");
}

function getPolymakerPoly()
{
	return _polymaker.currPts;
}

function initPolymaker(callback)
{
	_polymaker.callback = callback;
	_polymaker_addPolySVG('.svg-container');

	var createButton = document.getElementById("polymaker-create");
	var cancelButton = document.getElementById("polymaker-cancel");
	var finishButton = document.getElementById("polymaker-finish");
	if (createButton && cancelButton && finishButton) {
		createButton.onclick = function() {
			createButton.style.visibility = "hidden";
			cancelButton.style.visibility = "visible";
			finishButton.style.visibility = "visible";
			_polymaker_start();
		}
		cancelButton.onclick = function() {
			createButton.style.visibility = "visible";
			cancelButton.style.visibility = "hidden";
			finishButton.style.visibility = "hidden";
			_polymaker_cancel();
		}
		finishButton.onclick = function() {
			createButton.style.visibility = "visible";
			cancelButton.style.visibility = "hidden";
			finishButton.style.visibility = "hidden";
			_polymaker_finish();
		}
	}

	//test
	//$('#polymaker-poly').attr("points", "1e2,1e2 1.4e2,0.298e3 1.90e2,278 210,178");
}

//initPolymaker();
