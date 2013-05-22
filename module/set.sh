# ELDK5 environment settings for Gnublin LPC3131
# <Hubert.Hoegl@hs-augsburg.de> 2011-12-12 
ELDK5X86=/opt/eldk-5.0/armv5te/sysroots/i686-oesdk-linux
P1=$ELDK5X86/usr/bin/armv5te-linux-gnueabi/
P2=$ELDK5X86/bin/armv5te-linux-gnueabi/
export ARCH=arm 
export CROSS_COMPILE=arm-linux-gnueabi-
export PATH=$P1:$P2:$PATH
