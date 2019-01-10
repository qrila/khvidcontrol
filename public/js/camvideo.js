// Prepare camera 
var _webrtc_enabled = false;
$(document).ready(function() {
	//var video_url = "rtsp://srv13.arkasis.nl:80/498/default.stream"; // Curaçao test
	var video_url = "rtsp://10.0.0.70/stream1"; // TODO: From settings
	var audio_url = null;
	var port = 3038; // TODO: Port from settings?
	var options = "rtptransport=udp&timeout=9000";
	var webRtcServer = new WebRtcStreamer("camvideo", location.protocol+"//"+window.location.hostname+":"+port);
	var refreshInterval = 0;

	// //window.onload         = function() { webRtcServer.connect(video_url) }
	// Let's put this behind a separate click for now (Chrome won't autostart without user interaction)
	var vidStartButton = document.getElementById("camvideo-start");
	if (vidStartButton) {
		vidStartButton.onclick = function () {
			webRtcServer.connect(video_url, audio_url, options);
			_webrtc_enabled = true;
			vidStartButton.style.visibility = "hidden";

			// restart video feed every N seconds (it tends to stop updating for some reason)
			const restart_delay_seconds = 5 * 60;
			refreshInterval = setInterval(function() {
				_webrtc_enabled = false;
				webRtcServer.disconnect();
				webRtcServer.connect(video_url, audio_url, options);
				_webrtc_enabled = true;
			}, restart_delay_seconds * 1000);

			// hack:
			document.getElementById("polymaker-create").style.visibility = "visible";
		}
	}

	window.onbeforeunload = function() {
		clearInterval(refreshInterval);
		_webrtc_enabled = false;
		webRtcServer.disconnect();
	}
});
