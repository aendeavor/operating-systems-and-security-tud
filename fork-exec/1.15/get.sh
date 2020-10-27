#! /bin/bash

: '
# ? version   v0.1.0
# ? executed  manually (by ./get.sh)
# ? task      obtain the seminar package
'

# -->                   -->                   --> SETUP

set -euEo pipefail

CDIR="$(pwd)"
if realpath -e -L "${0}" &>/dev/null
then
  CDIR="$(realpath -e -L "${0}")"
  CDIR="${CDIR%/setup.sh}"
fi

# -->                   -->                   --> START

if [[ -d "${CDIR}/seminar" ]]
then
  echo "seminar directory already present."
  exit 0
fi

for PROGRAM in wget tar make bison gcc flex
do
  if ! command -v "${PROGRAM}" &>/dev/null
  then
    sudo apt-get -y install "${PROGRAM}"
  fi
done

(
  cd "${CDIR}"
  wget 'https://os.inf.tu-dresden.de/Studium/Bs/uebung/seminar.tar.gz' && tar xf seminar.tar.gz
)

unset NEEDED_PROGRAMS CDIR
