
var webRtcCtx = {
  auto_reconnect_delay_seconds: 4 * 60,
  //video_url: "rtsp://srv13.arkasis.nl:80/498/default.stream", // Curaçao test
  video_url: null,
  audio_url: null,
  options: 'rtptransport=udp&timeout=9000',
  enabled: false,
  port: 3038, // TODO: Port from settings?
  server: null,
  refreshInterval: null
};

function reconnectWebRTCVideoConnection()
{
  if (!webRtcCtx.enabled)
    return;

  webRtcCtx.enabled = false;
  webRtcCtx.server.disconnect();
  webRtcCtx.server.connect(webRtcCtx.video_url, webRtcCtx.audio_url, webRtcCtx.options);
  webRtcCtx.enabled = true;
  console.warn('Reconnected WebRTC video...');
}

function stopWebRTCVideoConnection()
{
  clearInterval(webRtcCtx.refreshInterval);
  webRtcCtx.refreshInterval = null;
  webRtcCtx.server.disconnect();
  webRtcCtx.enabled = false;
}

function startWebRTCVideoConnection() // eslint-disable-line no-unused-vars
{
  webRtcCtx.server = new WebRtcStreamer('camvideo', location.protocol+'//'+window.location.hostname+':'+webRtcCtx.port);
  webRtcCtx.server.connect(webRtcCtx.video_url, webRtcCtx.audio_url, webRtcCtx.options);
  webRtcCtx.enabled = true;

  // reconnect video feed every N seconds (sometimes it stops updating for unknown reason)
  webRtcCtx.refreshInterval = setInterval(function() {
    reconnectWebRTCVideoConnection();
  }, webRtcCtx.auto_reconnect_delay_seconds * 1000);

  window.onbeforeunload = function() {
    stopWebRTCVideoConnection();
  };
}
