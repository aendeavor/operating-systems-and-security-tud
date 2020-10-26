#! /bin/bash

: '
# ? version   v0.1.0
# ? executed  manually
# ? task      obtain the seminar package
'

# -->                   -->                   --> SETUP

set -euEo pipefail

# a bit overkill, who cares
function _get_current_directory
{
  if dirname "$(readlink -f "${0}")" &>/dev/null
  then
    CDIR="$(cd "$(dirname "$(readlink -f "${0}")")" && pwd)"
  elif realpath -e -L "${0}" &>/dev/null
  then
    CDIR="$(realpath -e -L "${0}")"
    CDIR="${CDIR%/setup.sh}"
  fi
}

CDIR="$(pwd)"
_get_current_directory

# -->                   -->                   --> START

declare -a NEEDED_PROGRAMS
NEEDED_PROGRAMS=( 'wget' 'tar' )

for PROGRAM in "${NEEDED_PROGRAMS[@]}"
do
  if ! command -v "${PROGRAM}" &>/dev/null
  then
    echo "wget is not installed" >&2
  fi
done

if [[ -d "${CDIR}/seminar" ]]
then
  echo "seminar directory already present."
  exit 0
fi

(
  cd "${CDIR}"
  wget 'https://os.inf.tu-dresden.de/Studium/Bs/uebung/seminar.tar.gz'
  tar xf seminar.tar.gz
)

unset NEEDED_PROGRAMS CDIR

if ! command -v make &>/dev/null
then
  echo "Make sure to get make!"
fi
