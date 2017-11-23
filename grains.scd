NetAddr.localAddr;
n = NetAddr("localhost", 57110);
NetAddr.langPort;
s.meter.alwaysOnTop_(true);

b = Buffer.alloc(s, 131072, 6);

b.write("C:/Users/Carl/Desktop/multichannel.wav", "wav", "int16", 0, 0, true);

(
~setup = {
Server.local.options.numOutputBusChannels_(6);
////////////////////SETUP/////////////////////
s.waitForBoot(
	OSCdef.freeAll;
	MIDIdef.freeAll;

	//Control Parameters
	~numChannels = 6;
	~numGrains = 12;
	~lagTime = 3;
	~processingAdr = NetAddr("127.0.0.1", 12000);


	OSCdef(\pan, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\pan, msg[i+1].linlin(0, 1, 0, 2));
		};
	}, '/pan');

	OSCdef(\dens, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\dens, msg[i+1].linlin(0, 1, 8, 30));
		};
	}, '/dens');

	OSCdef(\ind, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\index, msg[i+1].linlin(0, 1, 0.5, 20));
		};
	}, '/ind');

	OSCdef(\rat, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\ratio, msg[i+1].linlin(0, 1, 1, 10));
		};
	}, '/rat');

	OSCdef(\dur, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\duration, msg[i+1].linlin(0, 1, 0.05, 0.3));
		};
	}, '/dur');

	OSCdef(\amp, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\amp, msg[i+1].linlin(0, 1, 0, 0.2));
		};
	}, '/amp');

	OSCdef(\freq, {|msg|
	~numGrains.do{ |i|
			~grains[i].set(\freq, msg[i+1].linlin(0, 1, 80, 120));
		};
	}, '/freq');

/////////////MIDI/////////////
	MIDIClient.init;
	MIDIIn.connectAll;

	MIDIdef.cc(\controller, {
		|val, num|
		if(num == 16, {~processingAdr.sendMsg('sc', 1, val)}, {});
		if(num == 20, {~processingAdr.sendMsg('sc', 2, val)}, {});
		if(num == 24, {~processingAdr.sendMsg('sc', 3, val)}, {});
		if(num == 28, {~processingAdr.sendMsg('sc', 4, val)}, {});
		if(num == 46, {~processingAdr.sendMsg('sc', 5, val)}, {});
		if(num == 50, {~processingAdr.sendMsg('sc', 6, val)}, {});
		if(num == 54, {~processingAdr.sendMsg('sc', 7, val)}, {});
		if(num == 58, {~processingAdr.sendMsg('sc', 8, val)}, {});
		if(num == 17, {~processingAdr.sendMsg('sc', 9, val)}, {}); //freq, need OSC

		[val, num].postln;

	}, [16, 20, 24, 28, 46, 50, 54, 58,
		17, 21, 25, 29, 47, 51, 55, 59,
		18, 22, 26, 30, 48, 52, 56, 60,
		19, 23, 27, 31, 49, 53, 57, 61
	]);


////////////\MIDI\////////////

/////////////SYNTHDEFS/////////////
//Sine percussion with pitch envelope
SynthDef(\percSine, {
	|freq = 100, out = 0, amp = 0.5, pAtk = 0.01, pRel = 0.01,
	pMult = 1.5, atk = 0.01, rel = 0.01, pan = 0.0, crv = (-4)|

	var sig, aEnv, pEnv;
	aEnv = Env.perc(atk, rel).ar(2);
	pEnv = Env([1, pMult, 1], [pAtk, pRel], crv).ar;
	sig = SinOsc.ar(freq*pEnv) * aEnv;
	Out.ar(out, PanAz.ar(~numChannels, sig*amp, pan));
}).add;

//A single FM grain voice
SynthDef(\grainFM, {
	|duration = 0.1, freq = 100, pan = 0.0, ratio = 1, envNo = (-1), index = 1, dens = 10, amp = 0.0, out = 0, t = 2|
		var trig = Impulse.kr(Lag.kr(dens, t));
		var f = Lag.kr(freq, t);
		var modFreq = f * Lag.kr(ratio, t);
		var ind = Lag.kr(index, t);
		var sig = GrainFM.ar(~numChannels, trig, Lag.kr(duration, t), f, modFreq, ind, Lag.kr(pan, t), envNo);
		sig = sig * Lag.kr(amp, t);
	Out.ar(out, sig);
}).add;

SynthDef(\record, {
		arg bufnum;
    DiskOut.ar(bufnum, In.ar(0,6));
}).add;
////////////\SYNTHDEFS\////////////


"Finished Setup".postln;
);
}
)

CmdPeriod.add(~setup);
////////////////////\SETUP\///////////////////

s.plotTree

//////MAKE SYNTHS//////
(
~grains = Array.newClear(~numGrains);

~numGrains.do{
	|i| ~grains[i] = Synth(\grainFM, [\t, 3]);
};
)

s.plotTree
(
~grains.do{
	|synth, i|
	synth.set(\amp, 0.1, \pan, rrand(0.0, 2.0), \t, 15);
};
)

(
~grains.do{
	|synth, i|
	synth.set(\t, 8);
};
)




//RECORDING
~rec = Synth.tail(nil, \record, [\bufnum, b]);
~rec.free;




















/////////////////Composition/////////////////
(
Pdef(\perc, Pbind(
	\instrument, \percSine,
	\dur, Pwrand([
		Pseq([1/4], 8),
		Pseq([1/8], 16),
		Pseq([1/16], 8)
	], [0.6, 0.25, 0.15], inf),
	\freq, Prand([20, 30, 60, 120, 95, 40, 60, 180], inf).trace*2,
	\crv, -50,
	\atk, 0.005,
	\rel, Pwhite(0.1, 0.8),
	\pan, Pwhite(-0.9, 0.9),
	\pAtk, 0.01,
	\pMult, 20
));
)

Pdef(\perc).play;
Pdef(\perc).stop;
////////////////\Composition\////////////////


















(
MIDIdef.cc(\test1, {arg ...args; args.postln}); // match cc 1

)





//SOME MISC STUFF
(
SynthDef(\sine, {
	|freq = 100, amp = 0.1, pan = 0, time = 3|

	var f = Lag.kr(freq, time);
	var sig = SinOsc.ar(f) * amp;
	var panL = Lag.kr(pan, time);
	//SendReply.kr(Impulse.kr(20), '/pan', panL);

	Out.ar(0, Pan2.ar(sig, panL));
}).add;
)

(
~n = Array.fill(3, {Synth(\sine)});
)

x = Synth(\sine);
x.set(\pan, -1);


~array = Array.fill(3, 0);


(
OSCdef(\panTracking, {
	|msg|
	msg.postln;
}, '/pan');

OSCdef(\processing, {
	|msg|
	msg = msg.drop(1);
	~n.do{
		|synth, i|
		synth.set(\pan, msg[i]);
	};
	msg.postln;

}, '/test');

OSCdef(\panUpdating, {
	|msg|
	msg.postln;
}, '/setControls');
)

s.meter
~freqs = [300, 150];
(
Pdef(\test,
	Pmono(\grainFM,
		\dur, 1,
		\duration, 0.1,
		\freq, 100,
		\pan, Pseq([0, 0.5, 0.75, 0.9, 1.6, 1.8], inf),
		\ratio, 8.9,
		\index, 0.1,
		\dens, 40,
		\amp, 0.1
	)
).play;
)




//MAKE SYNTHS
(
~n = 16;
~array = Array.newClear(~n);
~n.do{
	|i|
	~array[i] = Synth(\grainFM, [\amp, 0]);
};
)
~array.do{|s| s.free}


//CONTROL SYNTHS
(
~pans = Array.fill(~n, {|i| rrand(0.0, 2.0)});
~dens = Array.fill(~n, {|i| 10+((i/~n)*10)});
~rat = Array.fill(~n, {1});
~freqs = Array.fill(~n, {|i| 30 + (2*i)});
)

Scale.lydianMinor.degrees
(
~array.do{
	|synth, i|
	synth.set(
		\freq, ~freqs[i].midicps,
		\pan, ~pans[i],
		\amp, 0.02,
		\dens, ~dens[i]*2,
		\index, 1,
		\ratio, ~rat[i],
		\t, 10
	);
};
)
~num = 0;
~ind = 0;

(50 + [0, 4, 7]).midicps
(
Tdef(\update, {loop{
	7.wait;
	~num = ~num + rrand(0.1, 0.5);
	~ind = ~ind + rrand(0.2, 0.35);
	~ind.postln;
	~off = Array.fill(~n, {exprand(0.1, 0.5)});
	~off.postln;
	~pan2 = Array.fill(~n, {|i| ~num+~off[i]});
	~dens2 = Array.fill(~n, {|i| 20+rrand(0.1, 5)});
	~array.do{|s, i| s.set(\pan, ~pan2[i], \dens, ~dens2[i]*2.5, \t, 5, \index, ~ind)};
}}).play;
)
(
~pan2 = Array.fill(~n, {|i| rrand(0.0, 2.0)});
~array.do{|s, i| s.set(\pan, ~pan2[i])};
)

//PERC
(
Pdef(\perc, Pbind(
	\instrument, \percSine,
	\dur, Pxrand([
		Pseq([1/4], 6),
		Pseq([1/8], 24),
		Pseq([1/3], 12),
		Pseq([1/16], 16)
	], inf),
	\pan, Pseq([
		Pseq([0, 0, 1.5, 1.5, 1.5, 1.5, 0, 1.9, 1.9, 1.9, 0.75], 1),
		Pseq([1, 1, 1.5, 1.75, 1.75, 1.15, 2, 2, 0.25, 1.5], 1),
		Pseq([0.5, 0.5, 0.5, 1.5, 1.5, 0.5, 0.5, 1.5], 1)
	], inf),
	\freq, Prand([20, 30, 60, 120, 95, 40, 60, 180], inf)*0.8,
	\crv, -10,
	\atk, 0.02,
	\rel, Pwhite(0.2, 1.5),
	\pAtk, Pwhite(0.001, 0.006),
	\pMult, Pwhite(8, 15),
	\amp, 0.2
)).play;
)