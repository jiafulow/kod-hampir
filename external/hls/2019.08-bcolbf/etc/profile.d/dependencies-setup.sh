if [ "X${_CMSBUILD_BUILD_ENV_}" = "X" ] ; then
  true
  test X$GCC_ROOT != X || . /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/gcc/8.2.0-bcolbf/etc/profile.d/init.sh
  test X$GMAKE_ROOT != X || . /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/gmake/4.3/etc/profile.d/init.sh
fi
