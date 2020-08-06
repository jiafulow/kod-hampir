if [ -f /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/etc/profile.d/dependencies-setup.sh ]; then . /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/etc/profile.d/dependencies-setup.sh; fi
HLS_ROOT="/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf"
HLS_VERSION="2019.08-bcolbf"
HLS_REVISION="1"
HLS_CATEGORY="external"
[ ! -d /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/bin ] || export PATH="/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/bin${PATH:+:$PATH}";
[ ! -d /cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/lib ] || export LD_LIBRARY_PATH="/cvmfs/cms.cern.ch/slc7_amd64_gcc820/external/hls/2019.08-bcolbf/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}";

