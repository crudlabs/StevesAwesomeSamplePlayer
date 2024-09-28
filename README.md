A sample playback object for the Teensy Audio Library based on the built-in AudioPlayMemory, but with some added features:

1) A musically useful pitch shifting function which works with semitones on the chromatic scale. 
2) Easy looping simply by setting the public **looping** variable true.
3) Playing back any segment of the sample.

Like AudioPlayMemory, this object currently only supports sample arrays created with [wav2sketch](http://crudlabs.org/wav2sketch/).

The **basic_playback** example in the examples folder shows the correct way to use all the features.
**Pitch shifting**

```samplePlayer.pitchShift(-12);``` to pitch the sample down one octave.

```samplePlayer.pitchShift(1);``` to pitch the sample up one semitone.

```samplePlayer.pitchShift(0);``` to play the original un-pitched sample.

The argument for pitchShift() is a float, not an int, so you can tune to a fraction of a cent if you'd like.

**Looping**

```samplePlayer.looping = true;``` to loop the sample, until you tell it to stop.

**Partial sample playback**
```
  samplePlayer.startPercent = 0.25;
  samplePlayer.endPercent = 0.75;
```
to start 25% of the way in and stop at 75%.

**Backwards playback**
```
  samplePlayer.backwards = true;
```
to make the sample play backwards.
