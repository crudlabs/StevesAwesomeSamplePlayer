<br/><br/>
A sample playback object for the Teensy Audio Library based on the built-in AudioPlayMemory, but with some added features:

1) A musically useful pitch shifting function which works with semitones on the chromatic scale
2) Easy looping simply by setting the public **looping** variable true
3) Playing back any segment of the sample
4) Playback of .raw audio files from SD card
5) Loading .raw files from an SD card onto an external PSRAM chip for up to 8 megabytes of samples

Like AudioPlayMemory, this object currently supports sample array files created with [wav2sketch](http://crudlabs.org/wav2sketch/).

<br/><br/>

**Pitch shifting**

```samplePlayer.pitchShift(-12);``` to pitch the sample down one octave.

```samplePlayer.pitchShift(1);``` to pitch the sample up one semitone.

```samplePlayer.pitchShift(0);``` to play the original un-pitched sample.

The argument for pitchShift() is a float, not an int, so you can tune to a fraction of a cent if you'd like.

<br/><br/>

**Looping**

```samplePlayer.looping = true;``` to loop the sample, until you tell it to stop.

<br/><br/>

**Partial sample playback**
```
  samplePlayer.startPercent = 0.25;
  samplePlayer.endPercent = 0.75;
```
to start 25% of the way in and stop at 75%.

<br/><br/>

**Backwards playback**
```
  samplePlayer.backwards = true;
```
to make the sample play backwards.

<br/><br/>

**SD Card playback**

Playback of .raw audio files from SD card. At the moment, files must be 16-bit PCM encoded .raw audio files. Info on how to covert other audio files into usable .raw files can be found in the **play_from_sd** example sketch. Files are not played off the SD card, but are loaded into arrays in RAM, which allows polyphonic playback (by using multiple objects, and loading a different file into each one), as well as pitch bending and the other features.
```
  samplePlayer.loadFromSD("cowbell.raw");
```
to load the file cowbell.raw from the SD card (this 808 cowbell sample is included in the example sketch).
```
  samplePlayer.play();
```
to play it, after you've loaded it.

<br/><br/>

**External PSRAM chip support**

This library supports use of these [8MB PSRAM chips](https://www.pjrc.com/store/psram.html). The **sd_to_external_ram_chip** example file shows how to load a .raw file from an SD card onto one. Simply call
```
  samplePlayer.useExternalRAMChip();
```
before the first time you loadFromSD.

