if ( -f /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/etc/profile.d/dependencies-setup.csh ) source /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/etc/profile.d/dependencies-setup.csh; endif
set HLS_ROOT="/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf"
set HLS_VERSION="2019.08-bcolbf"
set HLS_REVISION="1"
set HLS_CATEGORY="external"
if ( -d /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/bin ) then
  if ( ${?PATH} ) then
    setenv PATH "/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/bin:$PATH"
  else
    setenv PATH "/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/bin"
  endif
endif
if ( -d /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/lib ) then
  if ( ${?LD_LIBRARY_PATH} ) then
    setenv LD_LIBRARY_PATH "/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/lib:$LD_LIBRARY_PATH"
  else
    setenv LD_LIBRARY_PATH "/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/lib"
  endif
endif

