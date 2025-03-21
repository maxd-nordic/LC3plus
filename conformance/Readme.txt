/******************************************************************************
*                        ETSI TS 103 634 V1.5.1                               *
*              Low Complexity Communication Codec Plus (LC3plus)              *
*                                                                             *
* Copyright licence is solely granted through ETSI Intellectual Property      *
* Rights Policy, 3rd April 2019. No patent licence is granted by implication, *
* estoppel or otherwise.                                                      *
******************************************************************************/

=================================
LC3plus Conformance script V1.2.6
=================================

Changelog
==============
    - V1.2.6 2024-03-13
        - Added BFI-check for SQAM tests
    - V1.2.5 2023-09-15
        - Changed order of preprocess/item generation step
    - V1.2.4 2023-05-03
        - added 7.5ms highres conformance tests
    - V1.2.3 2022-11-10
        - added plc test with 10% burst pattern
    - V1.2.2 2021-10-01
        - Added missing variable initialization in rms.c
    - V1.2.1 2021-06-23
        - fixed file generation for lfe tests.
        - set odg for encode default metric 
        - bitflip seed can be set from config file
    - V1.2.0 2021-05-20
        - added lfe test. (low-frequency effects)
        - made delta_odg threshold dependent on ref_odg.
        - fixed combined tests for hrmode, changed seed for epmode switching
        - added -bit_exact option, which sets thresholds to minimum
        - use PLC item set for channel coder tests
    - V1.1.6 2021-02-23
        - added logs for each operation point in link ('mode') in html file
        - Added hrmode test functionality
    - V1.1.4 2020-04-17
        - Added 24bit handling
        - fixed file alignment
        - new energy calculation
    - V1.1.3 2020-03-24
        - Fixed formula of energy difference and changed threshold to 70
    - V1.0.4 2019-07-17
        - Better command logging
    - V1.0.3 2019-07-01        
        - Added option to use system sox
    - V1.0.2 2019-06-28
        - Reduced disk space requirement
    - V1.0.1 2019-06-26
        - Removed channel coder flag comparison for encdec and encoder tests


Pre-requisites
==============

 - Unix based operating system
 - python3
 - python numpy module
 - SoX (http://sox.sourceforge.net), Windows binary, downloaded automatically
 - An ITU-BS.1387 (PEAQ - advanced) implementation
 - Wine; Win32 is the reference platform to ensure bit exact behavior
 - curl
 - gcc
 - make

To-Do's on first time usage
============================

If you are running the script for the very first time, please make sure to do
the following things:

-replace "peaq_bin" in desired configuration file by path to PEAQ executable
-adjust PEAQ regular expression ("peaq_odg_regex") in example_config.cfg to find
 ODG of PEAQ output. This is the regular expression to apply in order to grep the
 ODG value from the console output of the PEAQ tool.
-Build LC3plus fixed point reference executable, check that it operates correctly
 with the testvector package and place it in the same directory as the conformance
 script. Ensure that it is called 'LC3plus_FX.exe'.
 The reference executable for all non-high-resolution tests must be the fixed point executable without any modifications.
-Build LC3plus floating point reference executable, check that it operates correctly
 with the testvector package and place it in the same directory as the conformance
 script. Ensure that it is called 'LC3plus_FL.exe'.
 The reference executable for all high-resolution tests must be the floating point executable without any modifications.
-set paths to encoder and decoder executables under test in example_config.cfg
 [globals]
-if there is a delay between coded test file and original signal, set it under 'delay'
 in example_config.cfg in the [globals] section

Note: since the conformance script does compensate the delay and resamples the
      PEAQ input files to 48 kHz, the PEAQ binary should not do this.


What is the reference executable – Fixed Point or Floating Point?
==================================================================

For all Non-High-Resolution tests, the LC3plus fixed point executable shall be used as the reference. These tests are:
-LC3plus_DECT_AAP_service.cfg
-LC3plus_DECT_voice_service.cfg

For all High-Resolution tests, the LC3plus floating point executable shall be used as the reference. These tests are:
-LC3plus_DECT_AAP_HighResolution.cfg
-LC3plus_precision.cfg

Usage of the script:
====================

lc3plus_conformance.py [-h] [-v] [-w WORKERS] [-system_sox] [-keep] CONFIG

LC3plus conformance tool - checks if a vendor implementation of the LC3plus codec
is conforming to the reference provided by Fraunhofer & Ericsson using PEAQ, MLD
and RMS metrics.

optional arguments:
  -h, --help      show this help message and exit
  -v              Activate verbose output
  -keep           Keep all files produced in the test run
  -w              Number of workers (threads) for multithreaded execution. Equals
                  number of CPU cores by default.
  -system_sox     Use system version of sox instead of downloaded one for better speed

The script requires a configuration file which contains paths to executables and
operating points to be tested. Each test configuration is indicated by a
configuration name in squared brackets. The configuration to be tested is
selected by 'enabled_tests=CONFIG'. A detailed description of the configuration
file can be found in this readme.

On Windows the script must be executed from Cygwin!


Usage of configuration file
============================

The configuration file is separated in sections by square brackets. Within each
section, variables can be set by 'variable=value'. Text behind a hash # is a
comment and will be ignored.

In the [globals] section, general parameters are defined, e.g. which
configurations to process, paths and command line for the test executables and
additional codec under test parameters.
This section also specifies the command line for the PEAQ executable and the
regular expression to it's output. The example lists all global parameters:

[globals]
enabled_tests=NG1.7_LC3plus_nb_voice, NG1.8_LC3plus_wb_voice   # configurations to be tested
encoder = CutEnc.exe -E -formatG192 -frame_ms {frame_size} {input} {output} {bitrate} {options}  # test encoder command line
decoder = CutDec.exe -D -formatG192 {input} {output} {options}            # test decoder command line
peaq_bin = PEAQbinary {reference} {test}                   # PEAQ command line
peaq_odg_regex = Objective Difference Grade: (-?\d+\.\d+)  # regular expression parsing ODG
option_bandwidth = -bandwidth "{arg}"                      # command line option to trigger bandwidth controller, arg is a number or a switching file
option_ep_debug  = -ep_dbg "{arg}"                         # command line option to write out channel coder debug information, arg is a file name
option_ep_mode   = -epmode {arg}                           # command line option to specify error protection mode, arg is value between 0 and 4
delay            = 0                                       # global option to set delay between coded test and original signal (reference has delay=0)
hrmode           = 0                                       # global option to set hrmode. set hrmode=1 for aktivation, default is 0.d

Since all tests use the G192 format to create and decode bitstreams, be sure to
add the '-formatG192' option to your encoder and decoder under test command line.
The option '-frame_ms {frame_size}' is mandatory and must be accepted by the encoder
and decoder under test.

Please refer to [1] for information how the codec under test shall handle switching
files. All command line parameters of the reference executable can be shown by
typing './LC3plus.exe'.

Please note that the user is allowed to change the order of the parameters in
{}-brackets above. The script doesn't care about the order of those parameters.

After the globals section, a number of [test] sections can be
specified describing an individual test for a profile, including operating
points and threshold criteria. The following parameters define a test set:

[NG1.8_LC3plus_wb_voice]
# test modes
test_sqam                = 1                     # regular sqam test, testing set of files with conditions
test_band_limiting       = 0                     # test band limited signal, e.g. nb signal at 48 kHz, not applicable for 8 kHz
test_bandwidth_switching = 0                     # test for bandwidth switching, not applicable for 8 kHz
test_high_pass           = 1                     # test for high pass filter of codec for 20 kHz signal
test_rate_switching      = 1                     # test for bitrate switching
test_plc                 = 1                     # test for packet loss concealment with 10% random losses
test_plc_burst           = 1                     # test for packet loss concealment with 10% burst losses 
test_pc                  = 1                     # test for partial concealment
test_ep_correctable      = 1                     # test for channel coder and error protection/correction with a correctable amount of bit errors
test_ep_non_correctable  = 1                     # test for channel coder and error protection/correction with a non-correctable amount of bit errors
test_ep_mode_switching   = 1                     # test for error protection mode switching
test_ep_combined         = 0                     # test for combined channel coding with stereo input with correctable amount of bit errors
test_ep_combined_nc      = 0                     # test for combined channel coding with stereo input with a non-correctable amount of bit errors
test_lfe                 = 0                     # test for Low frequency effects mode

# configurations for most tests
#         Mode, Frame Size, Samplingrate, Bitrate
configs = encode, 10, 8000, 32000:8000:96000
          decode, 5, 8000, 32000
          encdec, 2.5, 8000, 64000

# change metric for test
# metric can be rms, odg, mld, eng
sqam_encode_metric = odg
sqam_encdec_metric = mld
The metric can be set separately for each test by using
TESTNAME_MODE_metric = METRIC where TESTNAME is the name of the test (e.g. sqam
or plc), MODE is one of encode, decode or encdec and METRIC is one of rms, odg,
mld or eng. The allowed metrics for each test are defined in [2]. Only one quality metric can be selected
for each test.

# change thresholds for test metrics
sqam_encode_odg_threshold = 0.06      # Delta ODG
sqam_encdec_mld_threshold = 4         # Maximum Loudness Difference
sqam_decode_rms_threshold = 15        # RMS threshold in bits, i.e. k = 15 bits

The thresholds can be set for separately for each test by using
TESTNAME_MODE_METRIC_threshold = VALUE where TESTNAME is the name of the test
(e.g. sqam or plc), MODE is one of encode, decode or encdec, METRIC is one of rms,
odg, mld or eng and VALUE is the threshold to be set. The predefined thresholds
for each test are stated in [3].

- each line in configs=... defines a new operating point and must be indented
- sampling rate can be 8000, 16000, 24000, 32000, 44100, 48000
- bitrate can be set as single integer or in form of start:step:end
  for example, configure bitrates 16000, 24000, 32000:
    'configs = decode,10,44100,16000:8000:32000'

By default, all test modes are inactive and all thresholds are set to their default
value. The user is able to (de)activate certain tests, to adjust the thresholds and
to use different quality metrics.

The detailed description of all tests can be found in [4].

Limitations
===========

The user can set up a test with a preferred sampling rate and bit rate. However
it is not advised to test narrow band signals at a bitrate higher than 64
kBit/s since most PEAQ implementations have trouble with such signals.
Therefore, the conformance script will reject such configurations.
Limitations are also present for the bitrate which is limited to the range of
[20 ... 400] bytes/frame. If error protection is active, the bitrate is limited
to the range of [40 ... 240] bytes/frame.
Not all tests can be executed at all operating points, e.g. the bandwidth switching
test cannot be executed for NB (8 kHz) files. Such configurations will therefore
be ignored and no result is produced.

What does the script produce?
=============================

1.) Command line output with 'passed' or 'failed' results
    - passed: if metric value < threshold
              for all tests and their respective metric
    - failed: if metric value > threshold
              for any test and their respective metric

2.) Detailed results are saved in html files. For each test the
    following columns are displayed:
	- Mode: encode, decode or encdec, etc...
	- Item: name of SQAM-item
	- Sampling rate
	- Bitrate
    - Frame Size
	- Metric

If a certain threshold has not been passed, the respective cell will appear marked as red. Otherwise it
will appear in blue.

Each test set will also contain statistics displaying the percentage of passed operating points.

Open points
===========

Troubleshooting
===============
Be careful when using quotes in additional arguments passed to the codec under
test, for example:
    RIGHT SYNTAX: var = -f pattern.txt
    WRONG SYNTAX: var = '-f pattern.txt'


References
==========
[1] ETSI TS 103 634 Chapter 6.3.2 'Switching profile'
[2] ETSI TS 103 634 Chapter 7.5 'Mapping conformance test, module and quality metric'
[3] ETSI TS 103 634 Chapter 7.7 'Quality metric thresholds'
[4] ETSI TS 103 634 Chapter 7.4 'Conformance Tests'
