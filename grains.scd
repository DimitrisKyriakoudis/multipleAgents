p = ProxySpace.push(s.boot);
b = Buffer.readChannel(s,"C:/Users/Carl/Desktop/saxophone.wav", channels: 1);
b.play;
(
~grain.set(\wavebuf, b);
~trig = {Impulse.kr(MouseX.kr(10, 50))};
~graindur = {0.2};

~grain = {|wavebuf = 0, rate = #[0.5, 1, 1.5]|
	GrainBuf.ar(2, ~trig.kr, ~graindur.kr, wavebuf, rate, 0.5, 2, 0, -1) * 0.2
};

~grain.play;
)
s.plotTree
~grain.set(\density, 20);

s.meter

(
~gran.play;
~gran = {
	|buf = 0, dur = 0.1, pos = #[0.1, 0.5], envNo = (-1), dens = 10, rate = 1, amp = 0.2|
	var trig = Impulse.kr(dens);
	var sig = GrainBuf.ar(2, trig, dur, buf, rate, pos, 2, 0.5*WhiteNoise.kr, envNo) * amp;
	sig = Pan2.ar(sig, 0, 1);
	sig!2 * 0.2;
};
)
~y = {MouseX.kr(0.1, 1.0)}
~gran.set(\pos, [[0.1, ~y.kr]]);

(
SynthDef(\grain, {
	|buf = 0, dur = 0.1, pos = 0.5, envNo = (-1), dens = 10, rate = 1, amp = 0.2, out = 0|
	var trig = Impulse.kr(dens);
	var sig = GrainBuf.ar(2, trig, dur, buf, rate, pos, 2, 0.5*WhiteNoise.kr, envNo) * amp;
	Out.ar(out, sig!2);
}).add;
)
(
SynthDef(\sinez, {
	|freq = #[100, 200, 300], amp = 0.2, pan = 0, out = 0|
	var sig = 0;
	3.do{
		var temp = SinOsc.ar(freq);
		sig = sig + temp;
	};
	sig = sig * (1/3);
	Out.ar(out, sig!2 * amp);
}).add;
)
a = [100, 200, 325];
x = Synth(\sinez, [\freq, [[100, 200, 300]]]);
x.set(\freq, [~fregz.kr]);
s.plotTree


e = {MouseX.kr()}
~freqz = {[100, 200, 350]*SinOsc.kr(2).range(0.5, 1.5)};

(
p = Pbind(
	\instrument, \grain,

)
)

x = {|freq=440, amp=0.6| MoogFF.ar(PinkNoise.ar(amp), freq).dup}.play;

// In the following pattern, the first two keys are the ones that create the monophonic behaviour:
(
p = Pbind(
    \type, \set,    // This tells it we'll be setting parameters of an existing node...
    \id, x.nodeID,    // ...this tells it whose parameters we'll be setting
    \args, #[\freq, \amp],  // and this tells it which parameters to set
    \freq, Pwhite(100, 1000),
    \dur, 2,
    \amp, Pseq((1,0.99 .. 0.1), inf)
).play;
)

p.stop
x.free















x = Synth(\grain, [\buf, b]);
x.set(\pos, 0.62);
x.set(\dur, 0.7);




(
~test.set(\freq, 200);
~test = {|freq = 800|
	var sig = 0;
	3.do{|i|
		var temp = SinOsc.ar(freq*(i+1), 0, 0.3);
	sig = sig + temp;
	};
	sig = sig * 0.5;
};



~test.play;
)
