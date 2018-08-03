screen session is used to allow further debugging because it allows us to monitor the terminal output

to start a screen session
  screen -dmS acq sh -c 'cd /home/pi/acq && ./go 2>&1 | tee -a run.log'

The above commands also saves the screen session terminal output to run.log for future debugging

By adding the following line in front of screen, it makes the user pi
  sudo -H -u pi 

By adding this line to the  "etc/rc.local", a screen session is started and run a script called go upon boot

To see what sessions are on
  screen -ls
  
If only one session is on, to attach/connect/re-attach:
  screen -r

Once attached to the screen, you can see the execution of the current command. 

To terminate the screen session, ctrl+c

To detach or exit and leave the screen session running, ctrl+a first then d.


Below is a history of command Dr. Bletsch used to set up a screen session. Only for reference, in case something is wrong.

ss


  363  screen -r
  364  echo hello
  365  nano rc-local-launcher
  366  screen -r
  367  cat rc-local-launcher 
  368  cat /etc/rc.local 
  369  mkdir acq
  370  cd acq
  371  pwd
  372  gedit
  373  leafpad &
  374  pwd
  375  sudo nano /etc/rc.local 
  376  ls
  377  nano go
  378  chmod +x go
  379  ./go
  380  cat thelog 
  381  rm thelog 
  382  ls
  383  sudo reboot
  384  ping 4.2.2.2
  385  ssh x.dsss.be -ltkbletsc
  386  screen
  387  sudo apt install screen
  388  screen
  389  screen -ls
  390  screen -r
  391  ssh localhost
  392  screen -r
  393  screen -dr
  394  ssh x.dsss.be -ltkbletsc
  395  cd acq/
  396  ls
  397  cat thelog 
  398  screen -ls
  399  screen -r
  400  cat /etc/rc.local 
  401  screen -r
  402  screen -ls
  403  screen -dmS acq sh -c 'cd /home/pi/acq && ./go'
  404  screen -ls
  405  screen -r
  406  cat go
  407  nano go
  408  yes | gzip -c > mydata.gz
  409  ls -l
  410  zcat mydata.gz | wc -c
  411  yes
  412  zcat mydata.gz | wc -c
  413  ls -l
  414  rm mydata.gz 
  415  date +%Y%m%d%h%m%s
  416  date +%Y%m%d%H%m%s
  417  date +%Y%m%d%H%M%S
  418  date
  419  date +%Y%m%d-%H%M%S.dat
  420  FILENAME=`date +%Y%m%d-%H%M%S.dat`
  421  echo $FILENAME
  422  echo save to -o $FILENAME ok
  423  for A in `seq 000 100; do echo $A ; done
  424  for A in `seq 000 100`; do echo $A ; done
  425  for A in `seq 000 100`; do if [ ! -e $A ] ; then break; fi ; done
  426  echo $A
  427  touch 0
  428  for A in `seq 000 100`; do if [ ! -e $A ] ; then break; fi ; done
  429  echo $A
  430  for A in `seq 000 100`; do F=printf %03d.dat ; if [ ! -e $F ] ; then break; fi ; done
  431  for A in `seq 000 100`; do F=`printf %03d.dat` ; if [ ! -e $F ] ; then break; fi ; done
  432  echo $F
  433  touch 000.dat
  434  for A in `seq 000 100`; do F=`printf %03d.dat` ; if [ ! -e $F ] ; then break; fi ; done
  435  echo $F
  436  for A in `seq 000 100`; do F=`printf %03d.dat` ; if [ ! -e $F ] ; then break; fi ; done
  437  for A in `seq 000 100`; do F=`printf %03d.dat` ; if [ ! -e $F ] ; then break; fi ; echo $F ; done
  438  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; if [ ! -e $F ] ; then break; fi ; echo $F ; done
  439  touch 000.dat
  440  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; if [ ! -e $F ] ; then break; fi ; echo $F ; done
  441  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; echo $F ; if [ ! -e $F ] ; then break; fi ; echo $F ; done
  442  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; echo $F ; if [ ! -e $F ] ; then break; fi ; done
  443  echo $F
  444  touch 001.dat
  445  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; echo $F ; if [ ! -e $F ] ; then break; fi ; done
  446  echo $F
  447  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; echo $F ; if [ ! -e $F ] ; then break; fi ; done
  448  echo $F
  449  rm *.dat
  450  for A in `seq 000 100`; do F=`printf %03d.dat $A` ; echo $F ; if [ ! -e $F ] ; then break; fi ; done
  451  echo $F
  452  ls -l
  453  rm 0
