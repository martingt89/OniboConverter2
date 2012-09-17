converterdir=$(datadir)/@PACKAGE@/
converter_DATA=	\
./expg.png \
./converter.glade \
./dialogs.glade \
./user_settings.glade \
./audio_video_settings.xml

ffpresetsdir=$(datadir)/@PACKAGE@/ffpresets/
ffpresets_DATA= \
./ffpresets/libvpx-720p.ffpreset \
./ffpresets/libx264-veryfast.ffpreset \
./ffpresets/libx264-faster_firstpass.ffpreset \
./ffpresets/libvpx-1080p.ffpreset \
./ffpresets/libx264-placebo.ffpreset \
./ffpresets/libx264-superfast_firstpass.ffpreset \
./ffpresets/libx264-lossless_slow.ffpreset \
./ffpresets/libx264-slower_firstpass.ffpreset \
./ffpresets/libx264-ultrafast_firstpass.ffpreset \
./ffpresets/libx264-superfast.ffpreset \
./ffpresets/libx264-lossless_ultrafast.ffpreset \
./ffpresets/libx264-ultrafast.ffpreset \
./ffpresets/libvpx-360p.ffpreset \
./ffpresets/libx264-faster.ffpreset \
./ffpresets/libx264-veryslow_firstpass.ffpreset \
./ffpresets/libx264-baseline.ffpreset \
./ffpresets/libx264-ipod640.ffpreset \
./ffpresets/libx264-fast.ffpreset \
./ffpresets/libx264-lossless_max.ffpreset \
./ffpresets/libx264-medium_firstpass.ffpreset \
./ffpresets/libx264-main.ffpreset \
./ffpresets/libx264-veryfast_firstpass.ffpreset \
./ffpresets/libx264-ipod320.ffpreset \
./ffpresets/libx264-slower.ffpreset \
./ffpresets/libx264-slow.ffpreset \
./ffpresets/libx264-fast_firstpass.ffpreset \
./ffpresets/libx264-medium.ffpreset \
./ffpresets/libx264-lossless_fast.ffpreset \
./ffpresets/libx264-lossless_medium.ffpreset \
./ffpresets/libx264-placebo_firstpass.ffpreset \
./ffpresets/libvpx-720p50_60.ffpreset \
./ffpresets/libvpx-1080p50_60.ffpreset \
./ffpresets/libx264-lossless_slower.ffpreset \
./ffpresets/libx264-veryslow.ffpreset \
./ffpresets/libx264-slow_firstpass.ffpreset

profilesdir=$(datadir)/@PACKAGE@/profiles/
#profiles_DATA

desktopdir = $(datadir)/applications
desktop_DATA = OniboConverter2.desktop

UPDATE_DESKTOP = update-desktop-database $(datadir)/applications || :

install-data-hook: 
	$(UPDATE_DESKTOP)
uninstall-hook: 
	$(UPDATE_DESKTOP)

EXTRA_DIST = $(profiles_DATA) $(ffpresets_DATA) $(converter_DATA)
