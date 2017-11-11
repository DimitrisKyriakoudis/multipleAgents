b = Buffer.readChannel(s,"C:/Users/Carl/Desktop/saxophone.wav", channels: 1);
b.play;
NetAddr.langPort;

n = NetAddr("127.0.0.1", 50112);
NetAddr.langPort;

//////////////////SYNTHDEFS//////////////////
(
//Sine percussion with pitch envelope
SynthDef(\percSine, {
	|freq = 100, out = 0, amp = 0.5, pAtk = 0.01, pRel = 0.01,
	pMult = 1.5, atk = 0.01, rel = 0.01, pan = 0.0, crv = (-4)|

	var sig, aEnv, pEnv;
	aEnv = Env.perc(atk, rel).ar(2);
	pEnv = Env([1, pMult, 1], [pAtk, pRel], crv).ar;
	sig = SinOsc.ar(freq*pEnv) * aEnv;
	Out.ar(out, Pan2.ar(sig*amp, pan));
}).add;

//A single grain voice
SynthDef(\grain, {
	|buf = 0, dur = 0.1, pos = 0.5, envNo = (-1), dens = 10, rate = 1, amp = 0.2, out = 0|
	var trig = Impulse.kr(dens);
	var sig = GrainBuf.ar(2, trig, dur, buf, rate, pos, 2, 0.5*WhiteNoise.kr, envNo) * amp;
	Out.ar(out, sig!2);
}).add;
)
/////////////////\SYNTHDEFS\/////////////////



/////////////////////OSC/////////////////////
(
NetAddr.localAddr;
//////////OSC//////////
OSCdef(\receiver, {|...args|
var msg = args[0].drop(1); // omit the address flag
msg.size.postln; // you get the full message just fine
}, "/test");

//OSCFunc.trace(true); // Turn posting on


n = NetAddr.new("127.0.0.1", 57120);    // create the NetAddr
//v = 1000.collect{|i| i};
)
////////////////////\OSC\////////////////////



n.sendMsg("/test", *v); // send as perform list


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