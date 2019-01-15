
var webRtcCtx = {
    //video_url: "rtsp://srv13.arkasis.nl:80/498/default.stream", // Curaçao test
    video_url: "rtsp://10.0.0.70/stream1", // TODO: From settings
    audio_url: null,
    options: "rtptransport=udp&timeout=9000",
    enabled: false,
    port: 3038, // TODO: Port from settings?
    server: null
}

function reconnectWebRTCVideoConnection()
{
    webRtcCtx.enabled = false;
    webRtcCtx.server.disconnect();
    webRtcCtx.server.connect(webRtcCtx.video_url, webRtcCtx.audio_url, webRtcCtx.options);
    webRtcCtx.enabled = true;
    console.log("Reconnected WebRTC video...");
}

$(document).ready(function() {
    var refreshInterval = 0;

    webRtcCtx.server = new WebRtcStreamer("camvideo", location.protocol+"//"+window.location.hostname+":"+webRtcCtx.port);

    // //window.onload         = function() { webRtcCtx.server.connect(webRtcCtx.video_url) }
    // Let's put this behind a separate click for now (Chrome won't autostart without user interaction)
    var vidStartButton = document.getElementById("camvideo-start");
    if (vidStartButton) {
        vidStartButton.onclick = function () {
            webRtcCtx.server.connect(webRtcCtx.video_url, webRtcCtx.audio_url, webRtcCtx.options);
            webRtcCtx.enabled = true;
            vidStartButton.style.display = "none";

            // reconnect video feed every N seconds (sometimes it stops updating for unknown reason)
            const restart_delay_seconds = 4 * 60;
            refreshInterval = setInterval(function() {
                reconnectWebRTCVideoConnection();
            }, restart_delay_seconds * 1000);

            enableCamVideoUI(); // defined in app.js
        }
    }

    window.onbeforeunload = function() {
        clearInterval(refreshInterval);
        webRtcCtx.enabled = false;
        webRtcCtx.server.disconnect();
    }
});
