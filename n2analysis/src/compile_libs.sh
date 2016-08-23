#!/bin/bash

COMPILE_LOGON="/projects/e15118/n2analysis/customize_root/compile_logon.C"

root.exe -n  $COMPILE_LOGON <<EOF
.L detector.hh++
.q
EOF

root.exe -n $COMPILE_LOGON <<EOF
.L utils.cc++
.q
EOF

root.exe -n $COMPILE_LOGON <<EOF
.L mona.cc++
.q
EOF

root.exe -n $COMPILE_LOGON <<EOF
.L sweeper.cc++
.q
EOF

root.exe -n $COMPILE_LOGON <<EOF
.L caesar.cc++
.q
EOF

root.exe -n $COMPILE_LOGON <<EOF
.L unpacker.cc++ 
.q
EOF

root.exe -n $COMPILE_LOGON <<EOF
.L tandem.cc++ 
.q
EOF


if [ $(file /bin/bash | awk '{ print $3 }') == "32-bit" ]; then
  mv -f detector_hh.* ../lib/lib32/root/
  mv -f utils_cc.* ../lib/lib32/root/
  mv -f mona_cc.* ../lib/lib32/root/
  mv -f sweeper_cc.* ../lib/lib32/root/
  mv -f caesar_cc.* ../lib/lib32/root/
  mv -f unpacker_cc.* ../lib/lib32/root/ 
  mv -f tandem_cc.* ../lib/lib32/root/ 
fi
if [ $(file /bin/bash | awk '{ print $3 }') == "64-bit" ]; then
  mv -f detector_hh.* ../lib/lib64/root/
  mv -f utils_cc.* ../lib/lib64/root/
  mv -f mona_cc.* ../lib/lib64/root/
  mv -f sweeper_cc.* ../lib/lib64/root/
  mv -f caesar_cc.* ../lib/lib64/root/
  mv -f unpacker_cc.* ../lib/lib64/root/ 
  mv -f tandem_cc.* ../lib/lib64/root/ 
  mv -f detector_hh_ACLiC_dict_rdict.pcm ../lib/lib64/root/
  mv -f utils_cc_ACLiC_dict_rdict.pcm ../lib/lib64/root/
  mv -f mona_cc_ACLiC_dict_rdict.pcm ../lib/lib64/root/
  mv -f sweeper_cc_ACLiC_dict_rdict.pcm ../lib/lib64/root/
  mv -f caesar_cc_ACLiC_dict_rdict.pcm ../lib/lib64/root/
  mv -f unpacker_cc_ACLiC_dict_rdict.pcm ../lib/lib64/root/
  mv -f tandem_cc_ACLiC_dict_rdict.pcm ../lib/lib64/root/
fi
