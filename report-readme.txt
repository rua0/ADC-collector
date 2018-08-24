Author: Yao
Contact: yy123@duke.edu

Google doc version is here:
https://docs.google.com/document/d/1uIGNxXU2GL2qzeJzisK7td_w_6IaHDPdFriWnDsE1b4/edit?usp=sharing

Overview of this doc 

This document talks about the electronics that goes into the sonar data acquisition pod. It plans to talk about every aspect, including the details about realization with reference to source codes or people and more detailed set-up instructions.

Some terminology:
Pod: epoxyed system that goes under water and acquire necessary sonar data to construct a map of ocean floor

Feather ESP: I forgot the exact number. Maybe it's ESP8266. This is a wifi-enabled arduino compatible micro-controller

Transducer: Basically a speaker that makes sound when an ac voltage is applied

Hydrophone: Basically an underwater microphone that picks up sound.

ADC: analog to digital converter

Logic analyzer/Saleae Logic 16: A device used to acquire multiple bits of digital signal in parallel. It's used to acquire the 16-bit adc data.



System Overview

Here's the main idea. As the pod sinks down and up the ocean (with the help of winch system), it acquires time-stamped IMU and 3 channels of hydrophone data. The 600v circuit inside the pod triggers the transducer to make a 30khz sound intermittently, while the pi's inside the pod do the acquisition. The winch that's floating on the surface needs to have some mechanism for recording depth.

Hardware structure

The pod contains a pack of 3s lipo batteries as the main power source and a separate 1s battery that powers a feather ESP. This feather is always powered by this separate battery (though it does enter sleep mode). It charges this 1s battery when it gets power from the 5v (I believe it's 5v) step-downs. It turns on and off the rest of the system by sending n-shut-down signals to step-downs in the system. The feather uses a hall effect sensor to decided whether to shut everything down or not. 

The feather (or a separate arduino) is connected to an IMU module through I2C. It sends acquired IMU data to a pi through usb serial, and pi saves the data to files. We want to use the usb connection, if possible (unverified), for the reprogramming as well.

The feather (or the separate arduino) is connected to trigger a 600v circuit to make 30khz pulses through the transducer.

3 hybrophones are connected to 3 250ksps ADC's. Each ADC is connected to a saleae logic 16 logic analyzer. Each logic analyzer is connected to a pi3 to save the data.

The is a router inside the pod the allows external access via wifi to the pi's and potentially also the feather.


Software structure

For feather or arduino, one needs to write his/her own codes to do all the things above. But each part shouldn't be too hard. There's an I2C link to the IMU, a serial link to pi, and a 30khz pulse generator. 

The IMU pi needs to have a serial link via usb to feather. Python's pyserial library can easily take care of it.

The data acquisition pi uses sigrok-cli tool to run acquisition process at 1MHz. The acquired data is piped to a filter program that extracts only data at clock rise edge. The filter program pipes the output to gzip to compress. These happens on the fly.

The acquisition process is wrapped in a bash script, that restarts another acquisition in the consecutive names if the previous dies (which actually is very common). The bash script is run in a screen session that starts on boot. A line that starts this session is added to /etc/rc.local, which runs on boot.


Different parts

Battery

When making the battery pack, one needs to remember to connect not only the whole 3s in paralell but also each cell. Ideally a balancer is also needed. One needs to be extremely careful about cutting off the existing connectors on the battery. Don't cut two wires with a single cut or leave any two wires exposed in the air simultaneously.

The current idea is to have all wires sticking out of the pod so the charging is easier. We have thought about wireless charging. It's viable but slow and requires more work. Maybe it could be used for the second pod. 

This is not done at all. One needs to work it out quickly.

This only takes 1-2 days with everything, I think.

Feather

As mentioned above in the software structure section: There's an I2C link to the IMU, a serial link to pi, and a 30khz pulse generator. 

Individual parts has been worked on. A serial link shouldn't be a probalematic at all. A high schooler worked on getting the IMU to work with an arduino at least. But the process is untimed at all. It was transfered as fast as possible in every transfer. It's just reading I2C as fast as possible and sent via serial as fast as possible. There's no telling how the timing is at all with this. 

You could possibly rely on the time on pi. But in an experiment I did using bash script, the overhead in reading system time and save it to a variable was 50ms-ish, regardless of IMU, I2C and Serial delay.

I think the best way is to at least read time on the feather and transfer along with the IMU data.

As for the 30khz wave, hardware support is definitely needed to generate something of this resolution. The current way of doing it is use the tone function and wait some time to have certain number of pulses. Remeber to turn the pin low after stopping the tone function, because otherwise the 600v circuit is always on and something will burn.

I think the best way, with less portability though, is to just use the hardware timer. I have hacked the arduino uno timer to generate pulse at any pulse width or period. This will be much more accurate and controllable. But tone works, so until it doesn't work, forget about this for now.

Another main or rather greatest difficulty is to integrate all the parts. Last time I checked, nobody worked on it.

This feather part should take 2-3 weeks for a team of 2-3 people.


One other thing is the turning on and off of power.

I think the current way is to have the hall effect sensor pin tied to feather's RESET pin, so that when magnet is around, the feather is always in reset mode and has its GPIO's grounded. Then the n-shut-down pin is 0 so the step downs are shut down.

Logic analyzer:

To get rid of the plastic housing, remove the fake qc sticker at the back of the logic analyzer and you will see a screw. Remove this screw, which is the only thing that's holding it in one piece.

This fake logic 16 supports 500k, 1m, 2m and above sample rate.

ADC:

When useing a new adc, switch the buffer jumper from in to out. Because we don't need the buffer.

Solder signal wires to the input pin, where a BNC socket is present. You might need to unsolder it, which is a huge pain in the butt.

It's power goes to the 9v step-down. The buffer (+-15V) is unpowered, since we aren't using it.

Transducer and Hydrophone:

Transducer is connected to the 600v circuit. Refer to Dr. Brooke for details about the 600v.

Hydrophone needs power from 9v.


5v step-downs:

The pi is powered by the 5v step downs through the 5v and gnd gpio pin.

One problem that we have is that pi3 may need up to 2-2.5A of current. And the best step-downs without electrolyte capacitors have only 1A capacity. Possibly pi3 only uses up to 1A for majority of time, but when it does, then we are doomed because these step-downs resets and pi just dies for a indeterministic while.

Two solutions. One is to replace the 5v5A step-downs capacitors. It have a 470uF and a 50uF capacitor. It costs about 50 bucks to get these ceramic capacitors, plus the difficulty to solder and its ridiculous size. The alternative is to parallel a couple 1A step downs. You can't just hook them in parallel and be down with it. A resistor is needed in series with each step-downs to account for the minor voltage difference of each step-downs before they are connected in parallel. The official website didn't give precision information. By experiments, these step-downs have found to have a .2V max difference at quiescent. The resistor needs to take on .2V when running 1A of current, which makes the resistance .2Ohm and power .2W. There's probably no big deal in this if the resistance vary by .1Ohm.

A proto-board as a verification of the concept in the pod bin with other ADC's. Each step-down dies when current draw is approximately 1.3A. Two of the step-downs are silmultaneously contribution current in this proto board except the bad one. In one experiment, they together contributed 2A., with one of them contributing .7A. This parallelism is viable.

One thing to be cautious about is the voltage drop. .2V drop is significant. Each of these step-downs gives 4.99 V at quiescent. with .2V gone just on the resistor, there's 4.79V. The wiring also has voltage drop. (The probe cable on the electric load can take .2-.3V.) I am concerned that this might cause unstability when powering pi. But please do experiments to verify that the parallel ones can power pi or that the pi can be powered when capacitors are changed on the 5A step-downs.

This should take 2-3 days?


Data acquisition

If the rest, like the power, is done, then the data acquisition is pretty much all down until we find another problem with it. It might take 2-3 days to set up for th actual pod.

As mentioned in the software structure section: 

"The data acquisition pi uses sigrok-cli tool to run acquisition process at 1MHz. The acquired data is piped to a filter program that extracts only data at clock rise edge. The filter program pipes the output to gzip to compress. These happens on the fly.

The acquisition process is wrapped in a bash script, that restarts another acquisition in the consecutive names if the previous dies (which actually is very common). The bash script is run in a screen session that starts on boot. A line that starts this session is added to /etc/rc.local, which runs on boot."

To get familiar with sigrok setup or usage, read sigrok-notes.txt in this repo. However, I highly doubt that you would ever need to go through this again, since it's already set up on the pi's and the worst you need to do is to copy the images. Unless something goes miraculously wrong, you don't need set it up again.

Similarly everything needed for screen related setup is in "Screen-stuffs" folder of this repo. The instructions is in a txt file named "readme_screen_report_instructions.txt"

If you need to change anything in a regular session, change the go script in folder ~/acq on the pi. If you want to do some experiments, make another script and change the line that starts the screen session in rc.local.

Beware that files in this repo might be outdated. Same goes for files in pi. Usually, pi#1 has the most up-to-date files. Just ls in the "~" or "home/pi" directory and a file will tell the pod's id.

To access the pi's via ssh, refers to this spreadsheet for IP addresses. I expect you to keep it up-to-date when changing pi or what not:

https://docs.google.com/spreadsheets/d/1UoC6Qh9yn1WyCbvKdxzHQ3g61Mfxf3prS7GSFPpDC5Q/edit?usp=sharing

To reserve address for the pi's in the tplink routers, login in to the router's admin page at tplinklogin.net with usr name: admin pswd: xprize. Go to the DHCP part to do address reservation.

I think the newer model of tplink router is actually faster. It gives 20mbps of data transfer rate while the old ones gives 10-12mbps. Changing of the wifi doggle might help as well but not really worth the fuss.


Data joining and synchronization:

The main idea is use pulses from the pin to make alignments, since these pulses are very short compare to the regular timerame.

Since the three channels of data are acquired in parallel, synchronization is necessary. The way we do synchronization between three channels is rather simple: just have a leading large interval of nothing. So the beginning is easily synced.

The second important mechanism of joining data when acquisition process dies is alternating inter-pulse interval. It has been verified by this very mechanism that a couple seconds of data are missing when one process dies and we restart another immediately due to overhead or more likely the clearing of some buffer. The duration is indefinite. One experiments showed 6s of missing data and the other showed 4s.

By having periodically different intervals between any 3 consecutive pulses, we are able to tell which pulse(s) are missing. As of now, the pattern of intervals is 1s, 2s, ..., 10s, 1s, 2s ... This has proven to work. We were trying to come up with alternative patterns because having a 10s there is probalmatic. The least we can do 1 2 3 4 5 6 5 4 3 2. Or have .5 in difference. But again this is pre-optimization.

Others:
The filter-ch15-clk.c in the repo is the source code for the filter program.

The adc-read_process2.m is the matlab script that plots the raw data file from acquired.

Known Problems

In this past we planned to just use pi-zeros. But on pi-zero the acquisition process dies really quickly (less than 10s) if the sampling rate is 1M. Pi-zero survives longer (up to a couple hour and down to a couple minutes) when rate is 500k while pi-3 can run 500k indefinitely. 

The pi-zero works if we only needed 500ksps for acquiring samples but to acquire a 250ksps data, without time sync, we need at least more than twice the rate to make sure all data at the clock rise edge are acquired.


To do in the future

Make a pod very soon and verify that it can acquire real data and produce sensible analysis. To do so with the points above done, we need to first verify that all the connectors that we are using can survive the podding process, including sd-card slot, usb connector, jumper connection and other other press-fit connection.

The breadboarding are ok. The next important thing is space budgeting inside the pod.