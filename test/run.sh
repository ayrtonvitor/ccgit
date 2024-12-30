set -e

(
  cd "$(dirname "$0")"
  PATH=$VCPKG_ROOT:$PATH \
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/cmocka/build/src/ \
    make
)
