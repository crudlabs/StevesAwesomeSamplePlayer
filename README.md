A sample playback object for the Teensy Audio Library with a musically useful pitch shifting function which works with semitones on the chromatic scale. It also currently has two other useful features: looping, and playing back any segment of the full sample.

This object currently only supports sample arrays created with [wav2sketch](http://crudlabs.org/wav2sketch/) **using 16 bit PCM encoding and a 44100 sample rate**. Don't use other setting! They don't work yet.

At the moment this is not a drop-in replacement for the AudioPlayMemory object, only because I was compelled to do things slightly differently. But it should be similarly simple and easy to use. The **basic_playback** example shows the correct way to use all the features.

```samplePlayer.pitchShift(-12);``` to pitch the sample down one octave.

```samplePlayer.pitchShift(1);``` to pitch the sample up one semitone.

```samplePlayer.pitchShift(0);``` to play the original un-pitched sample.

It also has a looping parameter:

```samplePlayer.looping = true;``` to loop the sample, until you tell it to stop.

As well as a way to play only a segment of the sample:

```
  samplePlayer.startPercent = 0.25;
  samplePlayer.endPercent = 0.75;
```
to start 25% of the way in and stop at 75%.
