#!/bin/bash

TITLE="System Information Report for $HOSTNAME"
CURRENT_TIME=$(date +"%x %r %z")
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

report_uptime(){
#  echo "Reporting uptime..."
  cat <<EOF
System Uptime:
$(uptime)
EOF
  return$
}

report_disk_space(){
#  echo "Reporting disk space..."
  cat <<EOF
Disk space:
$(df | grep jacquelineguo)
EOF
  return$
}

report_home_space(){
#  echo "Reporting home space..."
  cat <<EOF
Home space:
$(du)
EOF
  return$
}

cat << EOF

# $TITLE

Hi $1!
## $TITLE

$(report_uptime)

$(report_disk_space)

$(report_home_space)

Data goes here

$TIME_STAMP
EOF
