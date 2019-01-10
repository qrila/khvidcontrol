// Prepare camera 
$(document).ready(function() {
	//var video_url = "rtsp://srv13.arkasis.nl:80/498/default.stream"; // Curaçao test
	var video_url = "rtsp://10.0.0.70/stream1"; // TODO: From settings
	var audio_url = null;
	var port = 3038; // TODO: Port from settings?
	var options = "rtptransport=udp&timeout=9000";
	var webRtcServer = new WebRtcStreamer("camvideo", location.protocol+"//"+window.location.hostname+":"+port);

	// //window.onload         = function() { webRtcServer.connect(video_url) }
	// // Let's put this behind a separate click for now (Chrome won't autostart without user interaction)
	// document.getElementById("camvideo-start").onclick = function () {
		// webRtcServer.connect(video_url, audio_url, options);
		// document.getElementById("camvideo-start").style.visibility = "hidden";
	// }

	// autostart using interval (chrome won't accept window.onload)
	var startInterval = setInterval(function() {
		webRtcServer.connect(video_url, audio_url, options);
		clearInterval(startInterval);
	}, 100);

	// restart video feed every N seconds (it tends to stop updating for some reason)
	const restart_delay_seconds = 5 * 60;
	var refreshInterval = setInterval(function() {
		webRtcServer.disconnect();
		webRtcServer.connect(video_url, audio_url, options);
	}, restart_delay_seconds * 1000);

	window.onbeforeunload = function() {
		clearInterval(refreshInterval);
		webRtcServer.disconnect();
	}
});
