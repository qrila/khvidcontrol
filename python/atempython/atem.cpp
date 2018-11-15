#include <Python.h>
#include <ATEMbase.h>
#include <ATEMmax.h>

ATEMmax AtemSwitcher;

static PyObject *begin(PyObject *self, PyObject *args);
static PyObject *runLoop(PyObject *self, PyObject *args);

static PyObject *setCameraControlVideomode(PyObject *self, PyObject *args);
static PyObject *setCameraControlLift(PyObject *self, PyObject *args);
static PyObject *setCameraControlGamma(PyObject *self, PyObject *args);
static PyObject *setCameraControlGainRGBY(PyObject *self, PyObject *args);
static PyObject *setCameraControlHueSaturation(PyObject *self, PyObject *args);
static PyObject *setDownConverterMode(PyObject *self, PyObject *args);
static PyObject *setVideoModeFormat(PyObject *self, PyObject *args);
static PyObject *setInputLongName(PyObject *self, PyObject *args);
static PyObject *setInputShortName(PyObject *self, PyObject *args);
static PyObject *setInputExternalPortType(PyObject *self, PyObject *args);
static PyObject *setMultiViewerPropertiesLayout(PyObject *self, PyObject *args);
static PyObject *setMultiViewerInputVideoSource(PyObject *self, PyObject *args);
static PyObject *setProgramInputVideoSource(PyObject *self, PyObject *args);
static PyObject *setPreviewInputVideoSource(PyObject *self, PyObject *args);
static PyObject *setTransitionStyle(PyObject *self, PyObject *args);
static PyObject *setTransitionNextTransition(PyObject *self, PyObject *args);
static PyObject *setTransitionPreviewEnabled(PyObject *self, PyObject *args);
static PyObject *setTransitionPosition(PyObject *self, PyObject *args);
static PyObject *setTransitionMixRate(PyObject *self, PyObject *args);
static PyObject *setTransitionDipRate(PyObject *self, PyObject *args);
static PyObject *setTransitionDipInput(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeRate(PyObject *self, PyObject *args);
static PyObject *setTransitionWipePattern(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeWidth(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeFillSource(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeSymmetry(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeSoftness(PyObject *self, PyObject *args);
static PyObject *setTransitionWipePositionX(PyObject *self, PyObject *args);
static PyObject *setTransitionWipePositionY(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeReverse(PyObject *self, PyObject *args);
static PyObject *setTransitionWipeFlipFlop(PyObject *self, PyObject *args);
static PyObject *setTransitionDVERate(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEStyle(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEFillSource(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEKeySource(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEEnableKey(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEPreMultiplied(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEClip(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEGain(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEInvertKey(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEReverse(PyObject *self, PyObject *args);
static PyObject *setTransitionDVEFlipFlop(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerSource(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerPreMultiplied(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerClip(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerGain(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerInvertKey(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerPreRoll(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerClipDuration(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerTriggerPoint(PyObject *self, PyObject *args);
static PyObject *setTransitionStingerMixRate(PyObject *self, PyObject *args);
static PyObject *setKeyerOnAirEnabled(PyObject *self, PyObject *args);
static PyObject *setKeyerType(PyObject *self, PyObject *args);
static PyObject *setKeyerFlyEnabled(PyObject *self, PyObject *args);
static PyObject *setKeyerMasked(PyObject *self, PyObject *args);
static PyObject *setKeyerTop(PyObject *self, PyObject *args);
static PyObject *setKeyerBottom(PyObject *self, PyObject *args);
static PyObject *setKeyerLeft(PyObject *self, PyObject *args);
static PyObject *setKeyerRight(PyObject *self, PyObject *args);
static PyObject *setKeyerFillSource(PyObject *self, PyObject *args);
static PyObject *setKeyerKeySource(PyObject *self, PyObject *args);
static PyObject *setKeyLumaPreMultiplied(PyObject *self, PyObject *args);
static PyObject *setKeyLumaClip(PyObject *self, PyObject *args);
static PyObject *setKeyLumaGain(PyObject *self, PyObject *args);
static PyObject *setKeyLumaInvertKey(PyObject *self, PyObject *args);
static PyObject *setKeyChromaHue(PyObject *self, PyObject *args);
static PyObject *setKeyChromaGain(PyObject *self, PyObject *args);
static PyObject *setKeyChromaYSuppress(PyObject *self, PyObject *args);
static PyObject *setKeyChromaLift(PyObject *self, PyObject *args);
static PyObject *setKeyChromaNarrow(PyObject *self, PyObject *args);
static PyObject *setKeyPatternPattern(PyObject *self, PyObject *args);
static PyObject *setKeyPatternSize(PyObject *self, PyObject *args);
static PyObject *setKeyPatternSymmetry(PyObject *self, PyObject *args);
static PyObject *setKeyPatternSoftness(PyObject *self, PyObject *args);
static PyObject *setKeyPatternPositionX(PyObject *self, PyObject *args);
static PyObject *setKeyPatternPositionY(PyObject *self, PyObject *args);
static PyObject *setKeyPatternInvertPattern(PyObject *self, PyObject *args);
static PyObject *setKeyDVESizeX(PyObject *self, PyObject *args);
static PyObject *setKeyDVESizeY(PyObject *self, PyObject *args);
static PyObject *setKeyDVEPositionX(PyObject *self, PyObject *args);
static PyObject *setKeyDVEPositionY(PyObject *self, PyObject *args);
static PyObject *setKeyDVERotation(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderEnabled(PyObject *self, PyObject *args);
static PyObject *setKeyDVEShadow(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderBevel(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderOuterWidth(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderInnerWidth(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderOuterSoftness(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderInnerSoftness(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderBevelSoftness(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderBevelPosition(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderOpacity(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderHue(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderSaturation(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBorderLuma(PyObject *self, PyObject *args);
static PyObject *setKeyDVELightSourceDirection(PyObject *self, PyObject *args);
static PyObject *setKeyDVELightSourceAltitude(PyObject *self, PyObject *args);
static PyObject *setKeyDVEMasked(PyObject *self, PyObject *args);
static PyObject *setKeyDVETop(PyObject *self, PyObject *args);
static PyObject *setKeyDVEBottom(PyObject *self, PyObject *args);
static PyObject *setKeyDVELeft(PyObject *self, PyObject *args);
static PyObject *setKeyDVERight(PyObject *self, PyObject *args);
static PyObject *setKeyDVERate(PyObject *self, PyObject *args);
static PyObject *setKeyerFlyKeyFrame(PyObject *self, PyObject *args);
static PyObject *setRunFlyingKeyKeyFrame(PyObject *self, PyObject *args);
static PyObject *setRunFlyingKeyRuntoInfiniteindex(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerFillSource(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerKeySource(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerTie(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerRate(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerPreMultiplied(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerClip(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerGain(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerInvertKey(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerMasked(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerTop(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerBottom(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerLeft(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerRight(PyObject *self, PyObject *args);
static PyObject *setDownstreamKeyerOnAir(PyObject *self, PyObject *args);
static PyObject *setFadeToBlackRate(PyObject *self, PyObject *args);
static PyObject *performFadeToBlackME(PyObject *self, PyObject *args);
static PyObject *getFadeToBlackStateFullyBlack(PyObject *self, PyObject *args);
static PyObject *setColorGeneratorHue(PyObject *self, PyObject *args);
static PyObject *setColorGeneratorSaturation(PyObject *self, PyObject *args);
static PyObject *setColorGeneratorLuma(PyObject *self, PyObject *args);
static PyObject *setAuxSourceInput(PyObject *self, PyObject *args);
static PyObject *setCameraControlIris(PyObject *self, PyObject *args);
static PyObject *setCameraControlFocus(PyObject *self, PyObject *args);
static PyObject *setCameraControlAutoFocus(PyObject *self, PyObject *args);
static PyObject *setCameraControlAutoIris(PyObject *self, PyObject *args);
static PyObject *setCameraControlGain(PyObject *self, PyObject *args);
static PyObject *setCameraControlWhiteBalance(PyObject *self, PyObject *args);
static PyObject *setCameraControlSharpeningLevel(PyObject *self, PyObject *args);
static PyObject *setCameraControlZoomSpeed(PyObject *self, PyObject *args);
static PyObject *setCameraControlColorbars(PyObject *self, PyObject *args);
static PyObject *setCameraControlLiftR(PyObject *self, PyObject *args);
static PyObject *setCameraControlGammaR(PyObject *self, PyObject *args);
static PyObject *setCameraControlGainR(PyObject *self, PyObject *args);
static PyObject *setCameraControlLumMix(PyObject *self, PyObject *args);
static PyObject *setCameraControlHue(PyObject *self, PyObject *args);
static PyObject *setCameraControlResetAll(PyObject *self, PyObject *args);
static PyObject *setCameraControlShutter(PyObject *self, PyObject *args);
static PyObject *setCameraControlLiftG(PyObject *self, PyObject *args);
static PyObject *setCameraControlGammaG(PyObject *self, PyObject *args);
static PyObject *setCameraControlGainG(PyObject *self, PyObject *args);
static PyObject *setCameraControlContrast(PyObject *self, PyObject *args);
static PyObject *setCameraControlSaturation(PyObject *self, PyObject *args);
static PyObject *setCameraControlLiftB(PyObject *self, PyObject *args);
static PyObject *setCameraControlGammaB(PyObject *self, PyObject *args);
static PyObject *setCameraControlGainB(PyObject *self, PyObject *args);
static PyObject *setCameraControlLiftY(PyObject *self, PyObject *args);
static PyObject *setCameraControlGammaY(PyObject *self, PyObject *args);
static PyObject *setCameraControlGainY(PyObject *self, PyObject *args);
static PyObject *setClipPlayerPlaying(PyObject *self, PyObject *args);
static PyObject *setClipPlayerLoop(PyObject *self, PyObject *args);
static PyObject *setClipPlayerAtBeginning(PyObject *self, PyObject *args);
static PyObject *setClipPlayerClipFrame(PyObject *self, PyObject *args);
static PyObject *setMediaPlayerSourceType(PyObject *self, PyObject *args);
static PyObject *setMediaPlayerSourceStillIndex(PyObject *self, PyObject *args);
static PyObject *setMediaPlayerSourceClipIndex(PyObject *self, PyObject *args);
static PyObject *setMediaPoolStorageClip1MaxLength(PyObject *self, PyObject *args);
static PyObject *setMacroAction(PyObject *self, PyObject *args);
static PyObject *setMacroRunChangePropertiesLooping(PyObject *self, PyObject *args);
static PyObject *setMacroStartRecordingIndex(PyObject *self, PyObject *args);
static PyObject *setMacroAddPauseFrames(PyObject *self, PyObject *args);
static PyObject *setSuperSourceFillSource(PyObject *self, PyObject *args);
static PyObject *setSuperSourceKeySource(PyObject *self, PyObject *args);
static PyObject *setSuperSourceForeground(PyObject *self, PyObject *args);
static PyObject *setSuperSourcePreMultiplied(PyObject *self, PyObject *args);
static PyObject *setSuperSourceClip(PyObject *self, PyObject *args);
static PyObject *setSuperSourceGain(PyObject *self, PyObject *args);
static PyObject *setSuperSourceInvertKey(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderEnabled(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderBevel(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderOuterWidth(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderInnerWidth(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderOuterSoftness(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderInnerSoftness(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderBevelSoftness(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderBevelPosition(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderHue(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderSaturation(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBorderLuma(PyObject *self, PyObject *args);
static PyObject *setSuperSourceLightSourceDirection(PyObject *self, PyObject *args);
static PyObject *setSuperSourceLightSourceAltitude(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersEnabled(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersInputSource(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersPositionX(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersPositionY(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersSize(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersCropped(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersCropTop(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersCropBottom(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersCropLeft(PyObject *self, PyObject *args);
static PyObject *setSuperSourceBoxParametersCropRight(PyObject *self, PyObject *args);
static PyObject *setAudioMixerInputMixOption(PyObject *self, PyObject *args);
static PyObject *setAudioMixerInputVolume(PyObject *self, PyObject *args);
static PyObject *setAudioMixerInputBalance(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMasterVolume(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMonitorMonitorAudio(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMonitorVolume(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMonitorMute(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMonitorSolo(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMonitorSoloInput(PyObject *self, PyObject *args);
static PyObject *setAudioMixerMonitorDim(PyObject *self, PyObject *args);
static PyObject *setAudioLevelsEnable(PyObject *self, PyObject *args);
static PyObject *setResetAudioMixerPeaksInputSource(PyObject *self, PyObject *args);
static PyObject *setResetAudioMixerPeaksMaster(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
	{ "begin", begin, METH_VARARGS, "desc" },
	{ "runLoop", runLoop, METH_VARARGS, "desc" },

	{"setCameraControlVideomode", setCameraControlVideomode, METH_VARARGS, "desc"},
	{"setCameraControlLift", setCameraControlLift, METH_VARARGS, "desc"},
	{"setCameraControlGamma", setCameraControlGamma, METH_VARARGS, "desc"},
	{"setCameraControlGainRGBY", setCameraControlGainRGBY, METH_VARARGS, "desc"},
	{"setCameraControlHueSaturation", setCameraControlHueSaturation, METH_VARARGS, "desc"},
	{"setDownConverterMode", setDownConverterMode, METH_VARARGS, "desc"},
	{"setVideoModeFormat", setVideoModeFormat, METH_VARARGS, "desc"},
	{"setInputLongName", setInputLongName, METH_VARARGS, "desc"},
	{"setInputShortName", setInputShortName, METH_VARARGS, "desc"},
	{"setInputExternalPortType", setInputExternalPortType, METH_VARARGS, "desc"},
	{"setMultiViewerPropertiesLayout", setMultiViewerPropertiesLayout, METH_VARARGS, "desc"},
	{"setMultiViewerInputVideoSource", setMultiViewerInputVideoSource, METH_VARARGS, "desc"},
	{"setProgramInputVideoSource", setProgramInputVideoSource, METH_VARARGS, "desc"},
	{"setPreviewInputVideoSource", setPreviewInputVideoSource, METH_VARARGS, "desc"},
	{"setTransitionStyle", setTransitionStyle, METH_VARARGS, "desc"},
	{"setTransitionNextTransition", setTransitionNextTransition, METH_VARARGS, "desc"},
	{"setTransitionPreviewEnabled", setTransitionPreviewEnabled, METH_VARARGS, "desc"},
	{"setTransitionPosition", setTransitionPosition, METH_VARARGS, "desc"},
	{"setTransitionMixRate", setTransitionMixRate, METH_VARARGS, "desc"},
	{"setTransitionDipRate", setTransitionDipRate, METH_VARARGS, "desc"},
	{"setTransitionDipInput", setTransitionDipInput, METH_VARARGS, "desc"},
	{"setTransitionWipeRate", setTransitionWipeRate, METH_VARARGS, "desc"},
	{"setTransitionWipePattern", setTransitionWipePattern, METH_VARARGS, "desc"},
	{"setTransitionWipeWidth", setTransitionWipeWidth, METH_VARARGS, "desc"},
	{"setTransitionWipeFillSource", setTransitionWipeFillSource, METH_VARARGS, "desc"},
	{"setTransitionWipeSymmetry", setTransitionWipeSymmetry, METH_VARARGS, "desc"},
	{"setTransitionWipeSoftness", setTransitionWipeSoftness, METH_VARARGS, "desc"},
	{"setTransitionWipePositionX", setTransitionWipePositionX, METH_VARARGS, "desc"},
	{"setTransitionWipePositionY", setTransitionWipePositionY, METH_VARARGS, "desc"},
	{"setTransitionWipeReverse", setTransitionWipeReverse, METH_VARARGS, "desc"},
	{"setTransitionWipeFlipFlop", setTransitionWipeFlipFlop, METH_VARARGS, "desc"},
	{"setTransitionDVERate", setTransitionDVERate, METH_VARARGS, "desc"},
	{"setTransitionDVEStyle", setTransitionDVEStyle, METH_VARARGS, "desc"},
	{"setTransitionDVEFillSource", setTransitionDVEFillSource, METH_VARARGS, "desc"},
	{"setTransitionDVEKeySource", setTransitionDVEKeySource, METH_VARARGS, "desc"},
	{"setTransitionDVEEnableKey", setTransitionDVEEnableKey, METH_VARARGS, "desc"},
	{"setTransitionDVEPreMultiplied", setTransitionDVEPreMultiplied, METH_VARARGS, "desc"},
	{"setTransitionDVEClip", setTransitionDVEClip, METH_VARARGS, "desc"},
	{"setTransitionDVEGain", setTransitionDVEGain, METH_VARARGS, "desc"},
	{"setTransitionDVEInvertKey", setTransitionDVEInvertKey, METH_VARARGS, "desc"},
	{"setTransitionDVEReverse", setTransitionDVEReverse, METH_VARARGS, "desc"},
	{"setTransitionDVEFlipFlop", setTransitionDVEFlipFlop, METH_VARARGS, "desc"},
	{"setTransitionStingerSource", setTransitionStingerSource, METH_VARARGS, "desc"},
	{"setTransitionStingerPreMultiplied", setTransitionStingerPreMultiplied, METH_VARARGS, "desc"},
	{"setTransitionStingerClip", setTransitionStingerClip, METH_VARARGS, "desc"},
	{"setTransitionStingerGain", setTransitionStingerGain, METH_VARARGS, "desc"},
	{"setTransitionStingerInvertKey", setTransitionStingerInvertKey, METH_VARARGS, "desc"},
	{"setTransitionStingerPreRoll", setTransitionStingerPreRoll, METH_VARARGS, "desc"},
	{"setTransitionStingerClipDuration", setTransitionStingerClipDuration, METH_VARARGS, "desc"},
	{"setTransitionStingerTriggerPoint", setTransitionStingerTriggerPoint, METH_VARARGS, "desc"},
	{"setTransitionStingerMixRate", setTransitionStingerMixRate, METH_VARARGS, "desc"},
	{"setKeyerOnAirEnabled", setKeyerOnAirEnabled, METH_VARARGS, "desc"},
	{"setKeyerType", setKeyerType, METH_VARARGS, "desc"},
	{"setKeyerFlyEnabled", setKeyerFlyEnabled, METH_VARARGS, "desc"},
	{"setKeyerMasked", setKeyerMasked, METH_VARARGS, "desc"},
	{"setKeyerTop", setKeyerTop, METH_VARARGS, "desc"},
	{"setKeyerBottom", setKeyerBottom, METH_VARARGS, "desc"},
	{"setKeyerLeft", setKeyerLeft, METH_VARARGS, "desc"},
	{"setKeyerRight", setKeyerRight, METH_VARARGS, "desc"},
	{"setKeyerFillSource", setKeyerFillSource, METH_VARARGS, "desc"},
	{"setKeyerKeySource", setKeyerKeySource, METH_VARARGS, "desc"},
	{"setKeyLumaPreMultiplied", setKeyLumaPreMultiplied, METH_VARARGS, "desc"},
	{"setKeyLumaClip", setKeyLumaClip, METH_VARARGS, "desc"},
	{"setKeyLumaGain", setKeyLumaGain, METH_VARARGS, "desc"},
	{"setKeyLumaInvertKey", setKeyLumaInvertKey, METH_VARARGS, "desc"},
	{"setKeyChromaHue", setKeyChromaHue, METH_VARARGS, "desc"},
	{"setKeyChromaGain", setKeyChromaGain, METH_VARARGS, "desc"},
	{"setKeyChromaYSuppress", setKeyChromaYSuppress, METH_VARARGS, "desc"},
	{"setKeyChromaLift", setKeyChromaLift, METH_VARARGS, "desc"},
	{"setKeyChromaNarrow", setKeyChromaNarrow, METH_VARARGS, "desc"},
	{"setKeyPatternPattern", setKeyPatternPattern, METH_VARARGS, "desc"},
	{"setKeyPatternSize", setKeyPatternSize, METH_VARARGS, "desc"},
	{"setKeyPatternSymmetry", setKeyPatternSymmetry, METH_VARARGS, "desc"},
	{"setKeyPatternSoftness", setKeyPatternSoftness, METH_VARARGS, "desc"},
	{"setKeyPatternPositionX", setKeyPatternPositionX, METH_VARARGS, "desc"},
	{"setKeyPatternPositionY", setKeyPatternPositionY, METH_VARARGS, "desc"},
	{"setKeyPatternInvertPattern", setKeyPatternInvertPattern, METH_VARARGS, "desc"},
	{"setKeyDVESizeX", setKeyDVESizeX, METH_VARARGS, "desc"},
	{"setKeyDVESizeY", setKeyDVESizeY, METH_VARARGS, "desc"},
	{"setKeyDVEPositionX", setKeyDVEPositionX, METH_VARARGS, "desc"},
	{"setKeyDVEPositionY", setKeyDVEPositionY, METH_VARARGS, "desc"},
	{"setKeyDVERotation", setKeyDVERotation, METH_VARARGS, "desc"},
	{"setKeyDVEBorderEnabled", setKeyDVEBorderEnabled, METH_VARARGS, "desc"},
	{"setKeyDVEShadow", setKeyDVEShadow, METH_VARARGS, "desc"},
	{"setKeyDVEBorderBevel", setKeyDVEBorderBevel, METH_VARARGS, "desc"},
	{"setKeyDVEBorderOuterWidth", setKeyDVEBorderOuterWidth, METH_VARARGS, "desc"},
	{"setKeyDVEBorderInnerWidth", setKeyDVEBorderInnerWidth, METH_VARARGS, "desc"},
	{"setKeyDVEBorderOuterSoftness", setKeyDVEBorderOuterSoftness, METH_VARARGS, "desc"},
	{"setKeyDVEBorderInnerSoftness", setKeyDVEBorderInnerSoftness, METH_VARARGS, "desc"},
	{"setKeyDVEBorderBevelSoftness", setKeyDVEBorderBevelSoftness, METH_VARARGS, "desc"},
	{"setKeyDVEBorderBevelPosition", setKeyDVEBorderBevelPosition, METH_VARARGS, "desc"},
	{"setKeyDVEBorderOpacity", setKeyDVEBorderOpacity, METH_VARARGS, "desc"},
	{"setKeyDVEBorderHue", setKeyDVEBorderHue, METH_VARARGS, "desc"},
	{"setKeyDVEBorderSaturation", setKeyDVEBorderSaturation, METH_VARARGS, "desc"},
	{"setKeyDVEBorderLuma", setKeyDVEBorderLuma, METH_VARARGS, "desc"},
	{"setKeyDVELightSourceDirection", setKeyDVELightSourceDirection, METH_VARARGS, "desc"},
	{"setKeyDVELightSourceAltitude", setKeyDVELightSourceAltitude, METH_VARARGS, "desc"},
	{"setKeyDVEMasked", setKeyDVEMasked, METH_VARARGS, "desc"},
	{"setKeyDVETop", setKeyDVETop, METH_VARARGS, "desc"},
	{"setKeyDVEBottom", setKeyDVEBottom, METH_VARARGS, "desc"},
	{"setKeyDVELeft", setKeyDVELeft, METH_VARARGS, "desc"},
	{"setKeyDVERight", setKeyDVERight, METH_VARARGS, "desc"},
	{"setKeyDVERate", setKeyDVERate, METH_VARARGS, "desc"},
	{"setKeyerFlyKeyFrame", setKeyerFlyKeyFrame, METH_VARARGS, "desc"},
	{"setRunFlyingKeyKeyFrame", setRunFlyingKeyKeyFrame, METH_VARARGS, "desc"},
	{"setRunFlyingKeyRuntoInfiniteindex", setRunFlyingKeyRuntoInfiniteindex, METH_VARARGS, "desc"},
	{"setDownstreamKeyerFillSource", setDownstreamKeyerFillSource, METH_VARARGS, "desc"},
	{"setDownstreamKeyerKeySource", setDownstreamKeyerKeySource, METH_VARARGS, "desc"},
	{"setDownstreamKeyerTie", setDownstreamKeyerTie, METH_VARARGS, "desc"},
	{"setDownstreamKeyerRate", setDownstreamKeyerRate, METH_VARARGS, "desc"},
	{"setDownstreamKeyerPreMultiplied", setDownstreamKeyerPreMultiplied, METH_VARARGS, "desc"},
	{"setDownstreamKeyerClip", setDownstreamKeyerClip, METH_VARARGS, "desc"},
	{"setDownstreamKeyerGain", setDownstreamKeyerGain, METH_VARARGS, "desc"},
	{"setDownstreamKeyerInvertKey", setDownstreamKeyerInvertKey, METH_VARARGS, "desc"},
	{"setDownstreamKeyerMasked", setDownstreamKeyerMasked, METH_VARARGS, "desc"},
	{"setDownstreamKeyerTop", setDownstreamKeyerTop, METH_VARARGS, "desc"},
	{"setDownstreamKeyerBottom", setDownstreamKeyerBottom, METH_VARARGS, "desc"},
	{"setDownstreamKeyerLeft", setDownstreamKeyerLeft, METH_VARARGS, "desc"},
	{"setDownstreamKeyerRight", setDownstreamKeyerRight, METH_VARARGS, "desc"},
	{"setDownstreamKeyerOnAir", setDownstreamKeyerOnAir, METH_VARARGS, "desc"},
	{"setFadeToBlackRate", setFadeToBlackRate, METH_VARARGS, "desc"},
  {"performFadeToBlackME", performFadeToBlackME, METH_VARARGS, "desc"},
  {"getFadeToBlackStateFullyBlack", getFadeToBlackStateFullyBlack, METH_VARARGS, "desc"},
	{"setColorGeneratorHue", setColorGeneratorHue, METH_VARARGS, "desc"},
	{"setColorGeneratorSaturation", setColorGeneratorSaturation, METH_VARARGS, "desc"},
	{"setColorGeneratorLuma", setColorGeneratorLuma, METH_VARARGS, "desc"},
	{"setAuxSourceInput", setAuxSourceInput, METH_VARARGS, "desc"},
	{"setCameraControlIris", setCameraControlIris, METH_VARARGS, "desc"},
	{"setCameraControlFocus", setCameraControlFocus, METH_VARARGS, "desc"},
	{"setCameraControlAutoFocus", setCameraControlAutoFocus, METH_VARARGS, "desc"},
	{"setCameraControlAutoIris", setCameraControlAutoIris, METH_VARARGS, "desc"},
	{"setCameraControlGain", setCameraControlGain, METH_VARARGS, "desc"},
	{"setCameraControlWhiteBalance", setCameraControlWhiteBalance, METH_VARARGS, "desc"},
	{"setCameraControlSharpeningLevel", setCameraControlSharpeningLevel, METH_VARARGS, "desc"},
	{"setCameraControlZoomSpeed", setCameraControlZoomSpeed, METH_VARARGS, "desc"},
	{"setCameraControlColorbars", setCameraControlColorbars, METH_VARARGS, "desc"},
	{"setCameraControlLiftR", setCameraControlLiftR, METH_VARARGS, "desc"},
	{"setCameraControlGammaR", setCameraControlGammaR, METH_VARARGS, "desc"},
	{"setCameraControlGainR", setCameraControlGainR, METH_VARARGS, "desc"},
	{"setCameraControlLumMix", setCameraControlLumMix, METH_VARARGS, "desc"},
	{"setCameraControlHue", setCameraControlHue, METH_VARARGS, "desc"},
	{"setCameraControlResetAll", setCameraControlResetAll, METH_VARARGS, "desc"},
	{"setCameraControlShutter", setCameraControlShutter, METH_VARARGS, "desc"},
	{"setCameraControlLiftG", setCameraControlLiftG, METH_VARARGS, "desc"},
	{"setCameraControlGammaG", setCameraControlGammaG, METH_VARARGS, "desc"},
	{"setCameraControlGainG", setCameraControlGainG, METH_VARARGS, "desc"},
	{"setCameraControlContrast", setCameraControlContrast, METH_VARARGS, "desc"},
	{"setCameraControlSaturation", setCameraControlSaturation, METH_VARARGS, "desc"},
	{"setCameraControlLiftB", setCameraControlLiftB, METH_VARARGS, "desc"},
	{"setCameraControlGammaB", setCameraControlGammaB, METH_VARARGS, "desc"},
	{"setCameraControlGainB", setCameraControlGainB, METH_VARARGS, "desc"},
	{"setCameraControlLiftY", setCameraControlLiftY, METH_VARARGS, "desc"},
	{"setCameraControlGammaY", setCameraControlGammaY, METH_VARARGS, "desc"},
	{"setCameraControlGainY", setCameraControlGainY, METH_VARARGS, "desc"},
	{"setClipPlayerPlaying", setClipPlayerPlaying, METH_VARARGS, "desc"},
	{"setClipPlayerLoop", setClipPlayerLoop, METH_VARARGS, "desc"},
	{"setClipPlayerAtBeginning", setClipPlayerAtBeginning, METH_VARARGS, "desc"},
	{"setClipPlayerClipFrame", setClipPlayerClipFrame, METH_VARARGS, "desc"},
	{"setMediaPlayerSourceType", setMediaPlayerSourceType, METH_VARARGS, "desc"},
	{"setMediaPlayerSourceStillIndex", setMediaPlayerSourceStillIndex, METH_VARARGS, "desc"},
	{"setMediaPlayerSourceClipIndex", setMediaPlayerSourceClipIndex, METH_VARARGS, "desc"},
	{"setMediaPoolStorageClip1MaxLength", setMediaPoolStorageClip1MaxLength, METH_VARARGS, "desc"},
	{"setMacroAction", setMacroAction, METH_VARARGS, "desc"},
	{"setMacroRunChangePropertiesLooping", setMacroRunChangePropertiesLooping, METH_VARARGS, "desc"},
	{"setMacroStartRecordingIndex", setMacroStartRecordingIndex, METH_VARARGS, "desc"},
	{"setMacroAddPauseFrames", setMacroAddPauseFrames, METH_VARARGS, "desc"},
	{"setSuperSourceFillSource", setSuperSourceFillSource, METH_VARARGS, "desc"},
	{"setSuperSourceKeySource", setSuperSourceKeySource, METH_VARARGS, "desc"},
	{"setSuperSourceForeground", setSuperSourceForeground, METH_VARARGS, "desc"},
	{"setSuperSourcePreMultiplied", setSuperSourcePreMultiplied, METH_VARARGS, "desc"},
	{"setSuperSourceClip", setSuperSourceClip, METH_VARARGS, "desc"},
	{"setSuperSourceGain", setSuperSourceGain, METH_VARARGS, "desc"},
	{"setSuperSourceInvertKey", setSuperSourceInvertKey, METH_VARARGS, "desc"},
	{"setSuperSourceBorderEnabled", setSuperSourceBorderEnabled, METH_VARARGS, "desc"},
	{"setSuperSourceBorderBevel", setSuperSourceBorderBevel, METH_VARARGS, "desc"},
	{"setSuperSourceBorderOuterWidth", setSuperSourceBorderOuterWidth, METH_VARARGS, "desc"},
	{"setSuperSourceBorderInnerWidth", setSuperSourceBorderInnerWidth, METH_VARARGS, "desc"},
	{"setSuperSourceBorderOuterSoftness", setSuperSourceBorderOuterSoftness, METH_VARARGS, "desc"},
	{"setSuperSourceBorderInnerSoftness", setSuperSourceBorderInnerSoftness, METH_VARARGS, "desc"},
	{"setSuperSourceBorderBevelSoftness", setSuperSourceBorderBevelSoftness, METH_VARARGS, "desc"},
	{"setSuperSourceBorderBevelPosition", setSuperSourceBorderBevelPosition, METH_VARARGS, "desc"},
	{"setSuperSourceBorderHue", setSuperSourceBorderHue, METH_VARARGS, "desc"},
	{"setSuperSourceBorderSaturation", setSuperSourceBorderSaturation, METH_VARARGS, "desc"},
	{"setSuperSourceBorderLuma", setSuperSourceBorderLuma, METH_VARARGS, "desc"},
	{"setSuperSourceLightSourceDirection", setSuperSourceLightSourceDirection, METH_VARARGS, "desc"},
	{"setSuperSourceLightSourceAltitude", setSuperSourceLightSourceAltitude, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersEnabled", setSuperSourceBoxParametersEnabled, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersInputSource", setSuperSourceBoxParametersInputSource, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersPositionX", setSuperSourceBoxParametersPositionX, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersPositionY", setSuperSourceBoxParametersPositionY, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersSize", setSuperSourceBoxParametersSize, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersCropped", setSuperSourceBoxParametersCropped, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersCropTop", setSuperSourceBoxParametersCropTop, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersCropBottom", setSuperSourceBoxParametersCropBottom, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersCropLeft", setSuperSourceBoxParametersCropLeft, METH_VARARGS, "desc"},
	{"setSuperSourceBoxParametersCropRight", setSuperSourceBoxParametersCropRight, METH_VARARGS, "desc"},
	{"setAudioMixerInputMixOption", setAudioMixerInputMixOption, METH_VARARGS, "desc"},
	{"setAudioMixerInputVolume", setAudioMixerInputVolume, METH_VARARGS, "desc"},
	{"setAudioMixerInputBalance", setAudioMixerInputBalance, METH_VARARGS, "desc"},
	{"setAudioMixerMasterVolume", setAudioMixerMasterVolume, METH_VARARGS, "desc"},
	{"setAudioMixerMonitorMonitorAudio", setAudioMixerMonitorMonitorAudio, METH_VARARGS, "desc"},
	{"setAudioMixerMonitorVolume", setAudioMixerMonitorVolume, METH_VARARGS, "desc"},
	{"setAudioMixerMonitorMute", setAudioMixerMonitorMute, METH_VARARGS, "desc"},
	{"setAudioMixerMonitorSolo", setAudioMixerMonitorSolo, METH_VARARGS, "desc"},
	{"setAudioMixerMonitorSoloInput", setAudioMixerMonitorSoloInput, METH_VARARGS, "desc"},
	{"setAudioMixerMonitorDim", setAudioMixerMonitorDim, METH_VARARGS, "desc"},
	{"setAudioLevelsEnable", setAudioLevelsEnable, METH_VARARGS, "desc"},
	{"setResetAudioMixerPeaksInputSource", setResetAudioMixerPeaksInputSource, METH_VARARGS, "desc"},
	{"setResetAudioMixerPeaksMaster", setResetAudioMixerPeaksMaster, METH_VARARGS, "desc"},
	{ NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
// https://docs.python.org/latest/c-api/module.html#c.PyModuleDef 
static struct PyModuleDef module_def = {
	PyModuleDef_HEAD_INIT,
	"demomodule",
	NULL,
	-1,
	module_methods
};

PyMODINIT_FUNC PyInit_ATEM(void) { // py3
#else
PyMODINIT_FUNC initATEM(void) { // py2
#endif
	PyObject *m; // shared
#if PY_MAJOR_VERSION >= 3
	// py3
	m = PyModule_Create(&module_def);
	if (m == NULL) {
		return NULL;
	}

	return m;
#else
	// py2
	m = Py_InitModule("ATEM", module_methods);
	if (m == NULL) {
		return;
	}
#endif
}

static PyObject *begin(PyObject *self, PyObject *args) {
	uint8_t octet1, octet2, octet3, octet4;
	if (!PyArg_ParseTuple(args, "iiii", &octet1, &octet2, &octet3, &octet4)) {
		return NULL;
	}

	AtemSwitcher.begin({octet1, octet2, octet3, octet4});
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *runLoop(PyObject *self, PyObject *args) {
	if (!PyArg_ParseTuple(args, "", NULL)) {
		return NULL;
	}

	AtemSwitcher.runLoop();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlVideomode(PyObject *self, PyObject *args) {
	uint8_t input;
	uint8_t fps;
	uint8_t resolution;
	uint8_t interlaced;

	if (!PyArg_ParseTuple(args, "bbbb", &input, &fps, &resolution, &interlaced)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlVideomode(input, fps, resolution, interlaced);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlLift(PyObject *self, PyObject *args) {
	uint8_t input;
	int liftR;
	int liftG;
	int liftB;
	int liftY;

	if (!PyArg_ParseTuple(args, "biiii", &input, &liftR, &liftG, &liftB, &liftY)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlLift(input, liftR, liftG, liftB, liftY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGamma(PyObject *self, PyObject *args) {
	uint8_t input;
	int gammaR;
	int gammaG;
	int gammaB;
	int gammaY;

	if (!PyArg_ParseTuple(args, "biiii", &input, &gammaR, &gammaG, &gammaB, &gammaY)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGamma(input, gammaR, gammaG, gammaB, gammaY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGainRGBY(PyObject *self, PyObject *args) {
	uint8_t input;
	int gainR;
	int gainG;
	int gainB;
	int gainY;

	if (!PyArg_ParseTuple(args, "biiii", &input, &gainR, &gainG, &gainB, &gainY)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGain(input, gainR, gainG, gainB, gainY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlHueSaturation(PyObject *self, PyObject *args) {
	uint8_t input;
	int hue;
	int saturation;

	if (!PyArg_ParseTuple(args, "bii", &input, &hue, &saturation)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlHueSaturation(input, hue, saturation);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownConverterMode(PyObject *self, PyObject *args) {
	uint8_t mode;

	if (!PyArg_ParseTuple(args, "b", &mode)) {
		return NULL;
	}

	AtemSwitcher.setDownConverterMode(mode);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setVideoModeFormat(PyObject *self, PyObject *args) {
	uint8_t format;

	if (!PyArg_ParseTuple(args, "b", &format)) {
		return NULL;
	}

	AtemSwitcher.setVideoModeFormat(format);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setInputLongName(PyObject *self, PyObject *args) {
	uint16_t videoSource;
	char *longName;

	if (!PyArg_ParseTuple(args, "hb", &videoSource, &longName)) {
		return NULL;
	}

	AtemSwitcher.setInputLongName(videoSource, longName);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setInputShortName(PyObject *self, PyObject *args) {
	uint16_t videoSource;
	char *shortName;

	if (!PyArg_ParseTuple(args, "hb", &videoSource, &shortName)) {
		return NULL;
	}

	AtemSwitcher.setInputShortName(videoSource, shortName);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setInputExternalPortType(PyObject *self, PyObject *args) {
	uint16_t videoSource;
	uint16_t externalPortType;

	if (!PyArg_ParseTuple(args, "hh", &videoSource, &externalPortType)) {
		return NULL;
	}

	AtemSwitcher.setInputExternalPortType(videoSource, externalPortType);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMultiViewerPropertiesLayout(PyObject *self, PyObject *args) {
	uint8_t multiViewer;
	uint8_t layout;

	if (!PyArg_ParseTuple(args, "bb", &multiViewer, &layout)) {
		return NULL;
	}

	AtemSwitcher.setMultiViewerPropertiesLayout(multiViewer, layout);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMultiViewerInputVideoSource(PyObject *self, PyObject *args) {
	uint8_t multiViewer;
	uint8_t windowIndex;
	uint16_t videoSource;

	if (!PyArg_ParseTuple(args, "bbh", &multiViewer, &windowIndex, &videoSource)) {
		return NULL;
	}

	AtemSwitcher.setMultiViewerInputVideoSource(multiViewer, windowIndex, videoSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setProgramInputVideoSource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t videoSource;

	if (!PyArg_ParseTuple(args, "bh", &mE, &videoSource)) {
		return NULL;
	}

	AtemSwitcher.setProgramInputVideoSource(mE, videoSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setPreviewInputVideoSource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t videoSource;

	if (!PyArg_ParseTuple(args, "bh", &mE, &videoSource)) {
		return NULL;
	}

	AtemSwitcher.setPreviewInputVideoSource(mE, videoSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStyle(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t style;

	if (!PyArg_ParseTuple(args, "bb", &mE, &style)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStyle(mE, style);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionNextTransition(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t nextTransition;

	if (!PyArg_ParseTuple(args, "bb", &mE, &nextTransition)) {
		return NULL;
	}

	AtemSwitcher.setTransitionNextTransition(mE, nextTransition);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionPreviewEnabled(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool enabled;

	if (!PyArg_ParseTuple(args, "bi", &mE, &enabled)) {
		return NULL;
	}

	AtemSwitcher.setTransitionPreviewEnabled(mE, enabled);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionPosition(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t position;

	if (!PyArg_ParseTuple(args, "bh", &mE, &position)) {
		return NULL;
	}

	AtemSwitcher.setTransitionPosition(mE, position);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionMixRate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bb", &mE, &rate)) {
		return NULL;
	}

	AtemSwitcher.setTransitionMixRate(mE, rate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDipRate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bb", &mE, &rate)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDipRate(mE, rate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDipInput(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t input;

	if (!PyArg_ParseTuple(args, "bh", &mE, &input)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDipInput(mE, input);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeRate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bb", &mE, &rate)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeRate(mE, rate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipePattern(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t pattern;

	if (!PyArg_ParseTuple(args, "bb", &mE, &pattern)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipePattern(mE, pattern);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeWidth(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t width;

	if (!PyArg_ParseTuple(args, "bh", &mE, &width)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeWidth(mE, width);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeFillSource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t fillSource;

	if (!PyArg_ParseTuple(args, "bh", &mE, &fillSource)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeFillSource(mE, fillSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeSymmetry(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t symmetry;

	if (!PyArg_ParseTuple(args, "bh", &mE, &symmetry)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeSymmetry(mE, symmetry);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeSoftness(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t softness;

	if (!PyArg_ParseTuple(args, "bh", &mE, &softness)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeSoftness(mE, softness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipePositionX(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t positionX;

	if (!PyArg_ParseTuple(args, "bh", &mE, &positionX)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipePositionX(mE, positionX);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipePositionY(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t positionY;

	if (!PyArg_ParseTuple(args, "bh", &mE, &positionY)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipePositionY(mE, positionY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeReverse(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool reverse;

	if (!PyArg_ParseTuple(args, "bi", &mE, &reverse)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeReverse(mE, reverse);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionWipeFlipFlop(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool flipFlop;

	if (!PyArg_ParseTuple(args, "bi", &mE, &flipFlop)) {
		return NULL;
	}

	AtemSwitcher.setTransitionWipeFlipFlop(mE, flipFlop);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVERate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bb", &mE, &rate)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVERate(mE, rate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEStyle(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t style;

	if (!PyArg_ParseTuple(args, "bb", &mE, &style)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEStyle(mE, style);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEFillSource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t fillSource;

	if (!PyArg_ParseTuple(args, "bh", &mE, &fillSource)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEFillSource(mE, fillSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEKeySource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t keySource;

	if (!PyArg_ParseTuple(args, "bh", &mE, &keySource)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEKeySource(mE, keySource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEEnableKey(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool enableKey;

	if (!PyArg_ParseTuple(args, "bi", &mE, &enableKey)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEEnableKey(mE, enableKey);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEPreMultiplied(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool preMultiplied;

	if (!PyArg_ParseTuple(args, "bi", &mE, &preMultiplied)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEPreMultiplied(mE, preMultiplied);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEClip(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t clip;

	if (!PyArg_ParseTuple(args, "bh", &mE, &clip)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEClip(mE, clip);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEGain(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t gain;

	if (!PyArg_ParseTuple(args, "bh", &mE, &gain)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEGain(mE, gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEInvertKey(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool invertKey;

	if (!PyArg_ParseTuple(args, "bi", &mE, &invertKey)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEInvertKey(mE, invertKey);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEReverse(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool reverse;

	if (!PyArg_ParseTuple(args, "bi", &mE, &reverse)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEReverse(mE, reverse);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionDVEFlipFlop(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool flipFlop;

	if (!PyArg_ParseTuple(args, "bi", &mE, &flipFlop)) {
		return NULL;
	}

	AtemSwitcher.setTransitionDVEFlipFlop(mE, flipFlop);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerSource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t source;

	if (!PyArg_ParseTuple(args, "bb", &mE, &source)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerSource(mE, source);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerPreMultiplied(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool preMultiplied;

	if (!PyArg_ParseTuple(args, "bi", &mE, &preMultiplied)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerPreMultiplied(mE, preMultiplied);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerClip(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t clip;

	if (!PyArg_ParseTuple(args, "bh", &mE, &clip)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerClip(mE, clip);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerGain(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t gain;

	if (!PyArg_ParseTuple(args, "bh", &mE, &gain)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerGain(mE, gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerInvertKey(PyObject *self, PyObject *args) {
	uint8_t mE;
	bool invertKey;

	if (!PyArg_ParseTuple(args, "bi", &mE, &invertKey)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerInvertKey(mE, invertKey);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerPreRoll(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t preRoll;

	if (!PyArg_ParseTuple(args, "bh", &mE, &preRoll)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerPreRoll(mE, preRoll);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerClipDuration(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t clipDuration;

	if (!PyArg_ParseTuple(args, "bh", &mE, &clipDuration)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerClipDuration(mE, clipDuration);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerTriggerPoint(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t triggerPoint;

	if (!PyArg_ParseTuple(args, "bh", &mE, &triggerPoint)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerTriggerPoint(mE, triggerPoint);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setTransitionStingerMixRate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint16_t mixRate;

	if (!PyArg_ParseTuple(args, "bh", &mE, &mixRate)) {
		return NULL;
	}

	AtemSwitcher.setTransitionStingerMixRate(mE, mixRate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerOnAirEnabled(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool enabled;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &enabled)) {
		return NULL;
	}

	AtemSwitcher.setKeyerOnAirEnabled(mE, keyer, enabled);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerType(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t type;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &type)) {
		return NULL;
	}

	AtemSwitcher.setKeyerType(mE, keyer, type);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerFlyEnabled(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool flyEnabled;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &flyEnabled)) {
		return NULL;
	}

	AtemSwitcher.setKeyerFlyEnabled(mE, keyer, flyEnabled);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerMasked(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool masked;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &masked)) {
		return NULL;
	}

	AtemSwitcher.setKeyerMasked(mE, keyer, masked);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerTop(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int top;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &top)) {
		return NULL;
	}

	AtemSwitcher.setKeyerTop(mE, keyer, top);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerBottom(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int bottom;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &bottom)) {
		return NULL;
	}

	AtemSwitcher.setKeyerBottom(mE, keyer, bottom);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerLeft(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int left;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &left)) {
		return NULL;
	}

	AtemSwitcher.setKeyerLeft(mE, keyer, left);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerRight(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int right;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &right)) {
		return NULL;
	}

	AtemSwitcher.setKeyerRight(mE, keyer, right);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerFillSource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t fillSource;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &fillSource)) {
		return NULL;
	}

	AtemSwitcher.setKeyerFillSource(mE, keyer, fillSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerKeySource(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t keySource;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &keySource)) {
		return NULL;
	}

	AtemSwitcher.setKeyerKeySource(mE, keyer, keySource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyLumaPreMultiplied(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool preMultiplied;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &preMultiplied)) {
		return NULL;
	}

	AtemSwitcher.setKeyLumaPreMultiplied(mE, keyer, preMultiplied);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyLumaClip(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t clip;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &clip)) {
		return NULL;
	}

	AtemSwitcher.setKeyLumaClip(mE, keyer, clip);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyLumaGain(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t gain;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &gain)) {
		return NULL;
	}

	AtemSwitcher.setKeyLumaGain(mE, keyer, gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyLumaInvertKey(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool invertKey;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &invertKey)) {
		return NULL;
	}

	AtemSwitcher.setKeyLumaInvertKey(mE, keyer, invertKey);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyChromaHue(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t hue;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &hue)) {
		return NULL;
	}

	AtemSwitcher.setKeyChromaHue(mE, keyer, hue);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyChromaGain(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t gain;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &gain)) {
		return NULL;
	}

	AtemSwitcher.setKeyChromaGain(mE, keyer, gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyChromaYSuppress(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t ySuppress;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &ySuppress)) {
		return NULL;
	}

	AtemSwitcher.setKeyChromaYSuppress(mE, keyer, ySuppress);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyChromaLift(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t lift;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &lift)) {
		return NULL;
	}

	AtemSwitcher.setKeyChromaLift(mE, keyer, lift);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyChromaNarrow(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool narrow;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &narrow)) {
		return NULL;
	}

	AtemSwitcher.setKeyChromaNarrow(mE, keyer, narrow);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternPattern(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t pattern;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &pattern)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternPattern(mE, keyer, pattern);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternSize(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t size;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &size)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternSize(mE, keyer, size);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternSymmetry(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t symmetry;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &symmetry)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternSymmetry(mE, keyer, symmetry);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternSoftness(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t softness;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &softness)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternSoftness(mE, keyer, softness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternPositionX(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t positionX;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &positionX)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternPositionX(mE, keyer, positionX);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternPositionY(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t positionY;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &positionY)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternPositionY(mE, keyer, positionY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyPatternInvertPattern(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool invertPattern;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &invertPattern)) {
		return NULL;
	}

	AtemSwitcher.setKeyPatternInvertPattern(mE, keyer, invertPattern);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVESizeX(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	long sizeX;

	if (!PyArg_ParseTuple(args, "bbl", &mE, &keyer, &sizeX)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVESizeX(mE, keyer, sizeX);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVESizeY(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	long sizeY;

	if (!PyArg_ParseTuple(args, "bbl", &mE, &keyer, &sizeY)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVESizeY(mE, keyer, sizeY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEPositionX(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	long positionX;

	if (!PyArg_ParseTuple(args, "bbl", &mE, &keyer, &positionX)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEPositionX(mE, keyer, positionX);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEPositionY(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	long positionY;

	if (!PyArg_ParseTuple(args, "bbl", &mE, &keyer, &positionY)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEPositionY(mE, keyer, positionY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVERotation(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	long rotation;

	if (!PyArg_ParseTuple(args, "bbl", &mE, &keyer, &rotation)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVERotation(mE, keyer, rotation);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderEnabled(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool borderEnabled;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &borderEnabled)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderEnabled(mE, keyer, borderEnabled);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEShadow(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool shadow;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &shadow)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEShadow(mE, keyer, shadow);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderBevel(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t borderBevel;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &borderBevel)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderBevel(mE, keyer, borderBevel);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderOuterWidth(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t borderOuterWidth;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &borderOuterWidth)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderOuterWidth(mE, keyer, borderOuterWidth);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderInnerWidth(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t borderInnerWidth;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &borderInnerWidth)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderInnerWidth(mE, keyer, borderInnerWidth);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderOuterSoftness(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t borderOuterSoftness;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &borderOuterSoftness)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderOuterSoftness(mE, keyer, borderOuterSoftness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderInnerSoftness(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t borderInnerSoftness;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &borderInnerSoftness)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderInnerSoftness(mE, keyer, borderInnerSoftness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderBevelSoftness(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t borderBevelSoftness;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &borderBevelSoftness)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderBevelSoftness(mE, keyer, borderBevelSoftness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderBevelPosition(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t borderBevelPosition;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &borderBevelPosition)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderBevelPosition(mE, keyer, borderBevelPosition);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderOpacity(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t borderOpacity;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &borderOpacity)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderOpacity(mE, keyer, borderOpacity);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderHue(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t borderHue;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &borderHue)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderHue(mE, keyer, borderHue);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderSaturation(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t borderSaturation;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &borderSaturation)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderSaturation(mE, keyer, borderSaturation);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBorderLuma(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t borderLuma;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &borderLuma)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBorderLuma(mE, keyer, borderLuma);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVELightSourceDirection(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint16_t lightSourceDirection;

	if (!PyArg_ParseTuple(args, "bbh", &mE, &keyer, &lightSourceDirection)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVELightSourceDirection(mE, keyer, lightSourceDirection);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVELightSourceAltitude(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t lightSourceAltitude;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &lightSourceAltitude)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVELightSourceAltitude(mE, keyer, lightSourceAltitude);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEMasked(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	bool masked;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &masked)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEMasked(mE, keyer, masked);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVETop(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int top;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &top)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVETop(mE, keyer, top);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVEBottom(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int bottom;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &bottom)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVEBottom(mE, keyer, bottom);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVELeft(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int left;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &left)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVELeft(mE, keyer, left);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVERight(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	int right;

	if (!PyArg_ParseTuple(args, "bbi", &mE, &keyer, &right)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVERight(mE, keyer, right);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyDVERate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &rate)) {
		return NULL;
	}

	AtemSwitcher.setKeyDVERate(mE, keyer, rate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setKeyerFlyKeyFrame(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t keyFrame;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &keyFrame)) {
		return NULL;
	}

	AtemSwitcher.setKeyerFlyKeyFrame(mE, keyer, keyFrame);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setRunFlyingKeyKeyFrame(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t keyFrame;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &keyFrame)) {
		return NULL;
	}

	AtemSwitcher.setRunFlyingKeyKeyFrame(mE, keyer, keyFrame);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setRunFlyingKeyRuntoInfiniteindex(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t keyer;
	uint8_t runtoInfiniteindex;

	if (!PyArg_ParseTuple(args, "bbb", &mE, &keyer, &runtoInfiniteindex)) {
		return NULL;
	}

	AtemSwitcher.setRunFlyingKeyRuntoInfiniteindex(mE, keyer, runtoInfiniteindex);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerFillSource(PyObject *self, PyObject *args) {
	uint8_t keyer;
	uint16_t fillSource;

	if (!PyArg_ParseTuple(args, "bh", &keyer, &fillSource)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerFillSource(keyer, fillSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerKeySource(PyObject *self, PyObject *args) {
	uint8_t keyer;
	uint16_t keySource;

	if (!PyArg_ParseTuple(args, "bh", &keyer, &keySource)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerKeySource(keyer, keySource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerTie(PyObject *self, PyObject *args) {
	uint8_t keyer;
	bool tie;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &tie)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerTie(keyer, tie);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerRate(PyObject *self, PyObject *args) {
	uint8_t keyer;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bb", &keyer, &rate)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerRate(keyer, rate);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerPreMultiplied(PyObject *self, PyObject *args) {
	uint8_t keyer;
	bool preMultiplied;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &preMultiplied)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerPreMultiplied(keyer, preMultiplied);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerClip(PyObject *self, PyObject *args) {
	uint8_t keyer;
	uint16_t clip;

	if (!PyArg_ParseTuple(args, "bh", &keyer, &clip)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerClip(keyer, clip);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerGain(PyObject *self, PyObject *args) {
	uint8_t keyer;
	uint16_t gain;

	if (!PyArg_ParseTuple(args, "bh", &keyer, &gain)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerGain(keyer, gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerInvertKey(PyObject *self, PyObject *args) {
	uint8_t keyer;
	bool invertKey;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &invertKey)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerInvertKey(keyer, invertKey);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerMasked(PyObject *self, PyObject *args) {
	uint8_t keyer;
	bool masked;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &masked)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerMasked(keyer, masked);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerTop(PyObject *self, PyObject *args) {
	uint8_t keyer;
	int top;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &top)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerTop(keyer, top);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerBottom(PyObject *self, PyObject *args) {
	uint8_t keyer;
	int bottom;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &bottom)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerBottom(keyer, bottom);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerLeft(PyObject *self, PyObject *args) {
	uint8_t keyer;
	int left;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &left)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerLeft(keyer, left);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerRight(PyObject *self, PyObject *args) {
	uint8_t keyer;
	int right;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &right)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerRight(keyer, right);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setDownstreamKeyerOnAir(PyObject *self, PyObject *args) {
	uint8_t keyer;
	bool onAir;

	if (!PyArg_ParseTuple(args, "bi", &keyer, &onAir)) {
		return NULL;
	}

	AtemSwitcher.setDownstreamKeyerOnAir(keyer, onAir);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setFadeToBlackRate(PyObject *self, PyObject *args) {
	uint8_t mE;
	uint8_t rate;

	if (!PyArg_ParseTuple(args, "bb", &mE, &rate)) {
		return NULL;
	}

	AtemSwitcher.setFadeToBlackRate(mE, rate);
	Py_INCREF(Py_None);
	return Py_None;
}
  
static PyObject *performFadeToBlackME(PyObject *self, PyObject *args) {
	uint8_t mE;


	AtemSwitcher.performFadeToBlackME(mE);
	Py_INCREF(Py_None);
	return Py_None;
}
  

static PyObject *getFadeToBlackStateFullyBlack(PyObject *self, PyObject *args) {
	uint8_t mE;
	return PyLong_FromLong(AtemSwitcher.getFadeToBlackStateFullyBlack(mE));
}

static PyObject *setColorGeneratorHue(PyObject *self, PyObject *args) {
	uint8_t colorGenerator;
	uint16_t hue;

	if (!PyArg_ParseTuple(args, "bh", &colorGenerator, &hue)) {
		return NULL;
	}

	AtemSwitcher.setColorGeneratorHue(colorGenerator, hue);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setColorGeneratorSaturation(PyObject *self, PyObject *args) {
	uint8_t colorGenerator;
	uint16_t saturation;

	if (!PyArg_ParseTuple(args, "bh", &colorGenerator, &saturation)) {
		return NULL;
	}

	AtemSwitcher.setColorGeneratorSaturation(colorGenerator, saturation);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setColorGeneratorLuma(PyObject *self, PyObject *args) {
	uint8_t colorGenerator;
	uint16_t luma;

	if (!PyArg_ParseTuple(args, "bh", &colorGenerator, &luma)) {
		return NULL;
	}

	AtemSwitcher.setColorGeneratorLuma(colorGenerator, luma);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAuxSourceInput(PyObject *self, PyObject *args) {
	uint8_t aUXChannel;
	uint16_t input;

	if (!PyArg_ParseTuple(args, "bh", &aUXChannel, &input)) {
		return NULL;
	}

	AtemSwitcher.setAuxSourceInput(aUXChannel, input);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlIris(PyObject *self, PyObject *args) {
	uint8_t input;
	int iris;

	if (!PyArg_ParseTuple(args, "bi", &input, &iris)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlIris(input, iris);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlFocus(PyObject *self, PyObject *args) {
	uint8_t input;
	int focus;

	if (!PyArg_ParseTuple(args, "bi", &input, &focus)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlFocus(input, focus);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlAutoFocus(PyObject *self, PyObject *args) {
	uint8_t input;
	int autoFocus;

	if (!PyArg_ParseTuple(args, "bi", &input, &autoFocus)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlAutoFocus(input, autoFocus);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlAutoIris(PyObject *self, PyObject *args) {
	uint8_t input;
	int autoIris;

	if (!PyArg_ParseTuple(args, "bi", &input, &autoIris)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlAutoIris(input, autoIris);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGain(PyObject *self, PyObject *args) {
	uint8_t input;
	int gain;

	if (!PyArg_ParseTuple(args, "bi", &input, &gain)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGain(input, gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlWhiteBalance(PyObject *self, PyObject *args) {
	uint8_t input;
	int whiteBalance;

	if (!PyArg_ParseTuple(args, "bi", &input, &whiteBalance)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlWhiteBalance(input, whiteBalance);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlSharpeningLevel(PyObject *self, PyObject *args) {
	uint8_t input;
	int sharpeningLevel;

	if (!PyArg_ParseTuple(args, "bi", &input, &sharpeningLevel)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlSharpeningLevel(input, sharpeningLevel);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlZoomSpeed(PyObject *self, PyObject *args) {
	uint8_t input;
	int zoomSpeed;

	if (!PyArg_ParseTuple(args, "bi", &input, &zoomSpeed)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlZoomSpeed(input, zoomSpeed);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlColorbars(PyObject *self, PyObject *args) {
	uint8_t input;
	int colorbars;

	if (!PyArg_ParseTuple(args, "bi", &input, &colorbars)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlColorbars(input, colorbars);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlLiftR(PyObject *self, PyObject *args) {
	uint8_t input;
	int liftR;

	if (!PyArg_ParseTuple(args, "bi", &input, &liftR)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlLiftR(input, liftR);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGammaR(PyObject *self, PyObject *args) {
	uint8_t input;
	int gammaR;

	if (!PyArg_ParseTuple(args, "bi", &input, &gammaR)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGammaR(input, gammaR);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGainR(PyObject *self, PyObject *args) {
	uint8_t input;
	int gainR;

	if (!PyArg_ParseTuple(args, "bi", &input, &gainR)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGainR(input, gainR);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlLumMix(PyObject *self, PyObject *args) {
	uint8_t input;
	int lumMix;

	if (!PyArg_ParseTuple(args, "bi", &input, &lumMix)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlLumMix(input, lumMix);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlHue(PyObject *self, PyObject *args) {
	uint8_t input;
	int hue;

	if (!PyArg_ParseTuple(args, "bi", &input, &hue)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlHue(input, hue);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlResetAll(PyObject *self, PyObject *args) {
	uint8_t input;
	int resetAll;

	if (!PyArg_ParseTuple(args, "bi", &input, &resetAll)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlResetAll(input, resetAll);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlShutter(PyObject *self, PyObject *args) {
	uint8_t input;
	int shutter;

	if (!PyArg_ParseTuple(args, "bi", &input, &shutter)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlShutter(input, shutter);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlLiftG(PyObject *self, PyObject *args) {
	uint8_t input;
	int liftG;

	if (!PyArg_ParseTuple(args, "bi", &input, &liftG)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlLiftG(input, liftG);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGammaG(PyObject *self, PyObject *args) {
	uint8_t input;
	int gammaG;

	if (!PyArg_ParseTuple(args, "bi", &input, &gammaG)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGammaG(input, gammaG);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGainG(PyObject *self, PyObject *args) {
	uint8_t input;
	int gainG;

	if (!PyArg_ParseTuple(args, "bi", &input, &gainG)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGainG(input, gainG);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlContrast(PyObject *self, PyObject *args) {
	uint8_t input;
	int contrast;

	if (!PyArg_ParseTuple(args, "bi", &input, &contrast)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlContrast(input, contrast);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlSaturation(PyObject *self, PyObject *args) {
	uint8_t input;
	int saturation;

	if (!PyArg_ParseTuple(args, "bi", &input, &saturation)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlSaturation(input, saturation);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlLiftB(PyObject *self, PyObject *args) {
	uint8_t input;
	int liftB;

	if (!PyArg_ParseTuple(args, "bi", &input, &liftB)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlLiftB(input, liftB);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGammaB(PyObject *self, PyObject *args) {
	uint8_t input;
	int gammaB;

	if (!PyArg_ParseTuple(args, "bi", &input, &gammaB)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGammaB(input, gammaB);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGainB(PyObject *self, PyObject *args) {
	uint8_t input;
	int gainB;

	if (!PyArg_ParseTuple(args, "bi", &input, &gainB)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGainB(input, gainB);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlLiftY(PyObject *self, PyObject *args) {
	uint8_t input;
	int liftY;

	if (!PyArg_ParseTuple(args, "bi", &input, &liftY)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlLiftY(input, liftY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGammaY(PyObject *self, PyObject *args) {
	uint8_t input;
	int gammaY;

	if (!PyArg_ParseTuple(args, "bi", &input, &gammaY)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGammaY(input, gammaY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setCameraControlGainY(PyObject *self, PyObject *args) {
	uint8_t input;
	int gainY;

	if (!PyArg_ParseTuple(args, "bi", &input, &gainY)) {
		return NULL;
	}

	AtemSwitcher.setCameraControlGainY(input, gainY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setClipPlayerPlaying(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	bool playing;

	if (!PyArg_ParseTuple(args, "bi", &mediaPlayer, &playing)) {
		return NULL;
	}

	AtemSwitcher.setClipPlayerPlaying(mediaPlayer, playing);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setClipPlayerLoop(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	bool loop;

	if (!PyArg_ParseTuple(args, "bi", &mediaPlayer, &loop)) {
		return NULL;
	}

	AtemSwitcher.setClipPlayerLoop(mediaPlayer, loop);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setClipPlayerAtBeginning(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	bool atBeginning;

	if (!PyArg_ParseTuple(args, "bi", &mediaPlayer, &atBeginning)) {
		return NULL;
	}

	AtemSwitcher.setClipPlayerAtBeginning(mediaPlayer, atBeginning);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setClipPlayerClipFrame(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	uint16_t clipFrame;

	if (!PyArg_ParseTuple(args, "bh", &mediaPlayer, &clipFrame)) {
		return NULL;
	}

	AtemSwitcher.setClipPlayerClipFrame(mediaPlayer, clipFrame);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMediaPlayerSourceType(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	uint8_t type;

	if (!PyArg_ParseTuple(args, "bb", &mediaPlayer, &type)) {
		return NULL;
	}

	AtemSwitcher.setMediaPlayerSourceType(mediaPlayer, type);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMediaPlayerSourceStillIndex(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	uint8_t stillIndex;

	if (!PyArg_ParseTuple(args, "bb", &mediaPlayer, &stillIndex)) {
		return NULL;
	}

	AtemSwitcher.setMediaPlayerSourceStillIndex(mediaPlayer, stillIndex);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMediaPlayerSourceClipIndex(PyObject *self, PyObject *args) {
	uint8_t mediaPlayer;
	uint8_t clipIndex;

	if (!PyArg_ParseTuple(args, "bb", &mediaPlayer, &clipIndex)) {
		return NULL;
	}

	AtemSwitcher.setMediaPlayerSourceClipIndex(mediaPlayer, clipIndex);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMediaPoolStorageClip1MaxLength(PyObject *self, PyObject *args) {
	uint16_t clip1MaxLength;

	if (!PyArg_ParseTuple(args, "h", &clip1MaxLength)) {
		return NULL;
	}

	AtemSwitcher.setMediaPoolStorageClip1MaxLength(clip1MaxLength);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMacroAction(PyObject *self, PyObject *args) {
	uint16_t index;
	uint8_t action;

	if (!PyArg_ParseTuple(args, "hb", &index, &action)) {
		return NULL;
	}

	AtemSwitcher.setMacroAction(index, action);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMacroRunChangePropertiesLooping(PyObject *self, PyObject *args) {
	bool looping;

	if (!PyArg_ParseTuple(args, "i", &looping)) {
		return NULL;
	}

	AtemSwitcher.setMacroRunChangePropertiesLooping(looping);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMacroStartRecordingIndex(PyObject *self, PyObject *args) {
	uint8_t index;

	if (!PyArg_ParseTuple(args, "b", &index)) {
		return NULL;
	}

	AtemSwitcher.setMacroStartRecordingIndex(index);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setMacroAddPauseFrames(PyObject *self, PyObject *args) {
	uint16_t frames;

	if (!PyArg_ParseTuple(args, "h", &frames)) {
		return NULL;
	}

	AtemSwitcher.setMacroAddPauseFrames(frames);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceFillSource(PyObject *self, PyObject *args) {
	uint16_t fillSource;

	if (!PyArg_ParseTuple(args, "h", &fillSource)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceFillSource(fillSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceKeySource(PyObject *self, PyObject *args) {
	uint16_t keySource;

	if (!PyArg_ParseTuple(args, "h", &keySource)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceKeySource(keySource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceForeground(PyObject *self, PyObject *args) {
	bool foreground;

	if (!PyArg_ParseTuple(args, "i", &foreground)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceForeground(foreground);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourcePreMultiplied(PyObject *self, PyObject *args) {
	bool preMultiplied;

	if (!PyArg_ParseTuple(args, "i", &preMultiplied)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourcePreMultiplied(preMultiplied);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceClip(PyObject *self, PyObject *args) {
	uint16_t clip;

	if (!PyArg_ParseTuple(args, "h", &clip)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceClip(clip);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceGain(PyObject *self, PyObject *args) {
	uint16_t gain;

	if (!PyArg_ParseTuple(args, "h", &gain)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceGain(gain);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceInvertKey(PyObject *self, PyObject *args) {
	bool invertKey;

	if (!PyArg_ParseTuple(args, "i", &invertKey)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceInvertKey(invertKey);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderEnabled(PyObject *self, PyObject *args) {
	bool borderEnabled;

	if (!PyArg_ParseTuple(args, "i", &borderEnabled)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderEnabled(borderEnabled);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderBevel(PyObject *self, PyObject *args) {
	uint8_t borderBevel;

	if (!PyArg_ParseTuple(args, "b", &borderBevel)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderBevel(borderBevel);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderOuterWidth(PyObject *self, PyObject *args) {
	uint16_t borderOuterWidth;

	if (!PyArg_ParseTuple(args, "h", &borderOuterWidth)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderOuterWidth(borderOuterWidth);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderInnerWidth(PyObject *self, PyObject *args) {
	uint16_t borderInnerWidth;

	if (!PyArg_ParseTuple(args, "h", &borderInnerWidth)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderInnerWidth(borderInnerWidth);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderOuterSoftness(PyObject *self, PyObject *args) {
	uint8_t borderOuterSoftness;

	if (!PyArg_ParseTuple(args, "b", &borderOuterSoftness)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderOuterSoftness(borderOuterSoftness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderInnerSoftness(PyObject *self, PyObject *args) {
	uint8_t borderInnerSoftness;

	if (!PyArg_ParseTuple(args, "b", &borderInnerSoftness)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderInnerSoftness(borderInnerSoftness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderBevelSoftness(PyObject *self, PyObject *args) {
	uint8_t borderBevelSoftness;

	if (!PyArg_ParseTuple(args, "b", &borderBevelSoftness)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderBevelSoftness(borderBevelSoftness);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderBevelPosition(PyObject *self, PyObject *args) {
	uint8_t borderBevelPosition;

	if (!PyArg_ParseTuple(args, "b", &borderBevelPosition)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderBevelPosition(borderBevelPosition);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderHue(PyObject *self, PyObject *args) {
	uint16_t borderHue;

	if (!PyArg_ParseTuple(args, "h", &borderHue)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderHue(borderHue);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderSaturation(PyObject *self, PyObject *args) {
	uint16_t borderSaturation;

	if (!PyArg_ParseTuple(args, "h", &borderSaturation)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderSaturation(borderSaturation);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBorderLuma(PyObject *self, PyObject *args) {
	uint16_t borderLuma;

	if (!PyArg_ParseTuple(args, "h", &borderLuma)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBorderLuma(borderLuma);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceLightSourceDirection(PyObject *self, PyObject *args) {
	uint16_t lightSourceDirection;

	if (!PyArg_ParseTuple(args, "h", &lightSourceDirection)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceLightSourceDirection(lightSourceDirection);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceLightSourceAltitude(PyObject *self, PyObject *args) {
	uint8_t lightSourceAltitude;

	if (!PyArg_ParseTuple(args, "b", &lightSourceAltitude)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceLightSourceAltitude(lightSourceAltitude);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersEnabled(PyObject *self, PyObject *args) {
	uint8_t box;
	bool enabled;

	if (!PyArg_ParseTuple(args, "bi", &box, &enabled)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersEnabled(box, enabled);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersInputSource(PyObject *self, PyObject *args) {
	uint8_t box;
	uint16_t inputSource;

	if (!PyArg_ParseTuple(args, "bh", &box, &inputSource)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersInputSource(box, inputSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersPositionX(PyObject *self, PyObject *args) {
	uint8_t box;
	int positionX;

	if (!PyArg_ParseTuple(args, "bi", &box, &positionX)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersPositionX(box, positionX);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersPositionY(PyObject *self, PyObject *args) {
	uint8_t box;
	int positionY;

	if (!PyArg_ParseTuple(args, "bi", &box, &positionY)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersPositionY(box, positionY);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersSize(PyObject *self, PyObject *args) {
	uint8_t box;
	uint16_t size;

	if (!PyArg_ParseTuple(args, "bh", &box, &size)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersSize(box, size);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersCropped(PyObject *self, PyObject *args) {
	uint8_t box;
	bool cropped;

	if (!PyArg_ParseTuple(args, "bi", &box, &cropped)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersCropped(box, cropped);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersCropTop(PyObject *self, PyObject *args) {
	uint8_t box;
	uint16_t cropTop;

	if (!PyArg_ParseTuple(args, "bh", &box, &cropTop)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersCropTop(box, cropTop);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersCropBottom(PyObject *self, PyObject *args) {
	uint8_t box;
	uint16_t cropBottom;

	if (!PyArg_ParseTuple(args, "bh", &box, &cropBottom)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersCropBottom(box, cropBottom);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersCropLeft(PyObject *self, PyObject *args) {
	uint8_t box;
	uint16_t cropLeft;

	if (!PyArg_ParseTuple(args, "bh", &box, &cropLeft)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersCropLeft(box, cropLeft);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setSuperSourceBoxParametersCropRight(PyObject *self, PyObject *args) {
	uint8_t box;
	uint16_t cropRight;

	if (!PyArg_ParseTuple(args, "bh", &box, &cropRight)) {
		return NULL;
	}

	AtemSwitcher.setSuperSourceBoxParametersCropRight(box, cropRight);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerInputMixOption(PyObject *self, PyObject *args) {
	uint16_t audioSource;
	uint8_t mixOption;

	if (!PyArg_ParseTuple(args, "hb", &audioSource, &mixOption)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerInputMixOption(audioSource, mixOption);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerInputVolume(PyObject *self, PyObject *args) {
	uint16_t audioSource;
	uint16_t volume;

	if (!PyArg_ParseTuple(args, "hh", &audioSource, &volume)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerInputVolume(audioSource, volume);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerInputBalance(PyObject *self, PyObject *args) {
	uint16_t audioSource;
	int balance;

	if (!PyArg_ParseTuple(args, "hi", &audioSource, &balance)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerInputBalance(audioSource, balance);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMasterVolume(PyObject *self, PyObject *args) {
	uint16_t volume;

	if (!PyArg_ParseTuple(args, "h", &volume)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMasterVolume(volume);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMonitorMonitorAudio(PyObject *self, PyObject *args) {
	bool monitorAudio;

	if (!PyArg_ParseTuple(args, "i", &monitorAudio)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMonitorMonitorAudio(monitorAudio);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMonitorVolume(PyObject *self, PyObject *args) {
	uint16_t volume;

	if (!PyArg_ParseTuple(args, "h", &volume)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMonitorVolume(volume);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMonitorMute(PyObject *self, PyObject *args) {
	bool mute;

	if (!PyArg_ParseTuple(args, "i", &mute)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMonitorMute(mute);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMonitorSolo(PyObject *self, PyObject *args) {
	bool solo;

	if (!PyArg_ParseTuple(args, "i", &solo)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMonitorSolo(solo);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMonitorSoloInput(PyObject *self, PyObject *args) {
	uint16_t soloInput;

	if (!PyArg_ParseTuple(args, "h", &soloInput)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMonitorSoloInput(soloInput);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioMixerMonitorDim(PyObject *self, PyObject *args) {
	bool dim;

	if (!PyArg_ParseTuple(args, "i", &dim)) {
		return NULL;
	}

	AtemSwitcher.setAudioMixerMonitorDim(dim);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setAudioLevelsEnable(PyObject *self, PyObject *args) {
	bool enable;

	if (!PyArg_ParseTuple(args, "i", &enable)) {
		return NULL;
	}

	AtemSwitcher.setAudioLevelsEnable(enable);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setResetAudioMixerPeaksInputSource(PyObject *self, PyObject *args) {
	uint16_t inputSource;

	if (!PyArg_ParseTuple(args, "h", &inputSource)) {
		return NULL;
	}

	AtemSwitcher.setResetAudioMixerPeaksInputSource(inputSource);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *setResetAudioMixerPeaksMaster(PyObject *self, PyObject *args) {
	bool master;

	if (!PyArg_ParseTuple(args, "i", &master)) {
		return NULL;
	}

	AtemSwitcher.setResetAudioMixerPeaksMaster(master);
	Py_INCREF(Py_None);
	return Py_None;
}
