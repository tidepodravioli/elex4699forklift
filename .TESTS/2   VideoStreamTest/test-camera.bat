gst-launch-1.0 -v udpsrc port=5808 caps="application/x-rtp, media=video, encoding-name=H264, payload=96" ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink
