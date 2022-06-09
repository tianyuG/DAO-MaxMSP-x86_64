# Summary

This is an adaptation of [DAO-MaxMSP-Pd](https://github.com/juandagilc/DAO-MaxMSP-Pd) by [Juan Gil](https://github.com/juandagilc) with the following changes:

* It will only create Max/MSP externals. As such, externals that are available natively to Max/MSP (cartopol~, poltocar~, windowvec~) are not included.
* Build supports for Visual Studio and GNU Make have been removed.
* The Max/MSP externals has been updated to support 64-bit audio processing. 
* The externals will be available for x86_64 (dropped i386 support as it cannot be used or built on newer macOS; **does not support Apple Silicon**).

Built with a MacBook Pro with Apple M1 Pro, with macOS Monterey (12.4), Xcode 13.4.1, and Max/MSP API 8.2.0.

Precompiled Max/MSP externals can be found here.

As Max/MSP SDK cannot be republished without permission of Cycling '74, you can download the SDK [from their website](https://cycling74.com/downloads/sdk).

To build, clone the repository, change into its directory and use ``ruby ./build.rb``. use ``-V`` or ``--verbose`` to see detailed error messages during the build.

Implementation is not guaranteed to be correct.

# Progress
## Completed
``bed``, ``cleaner~``.

## In Progress
``dynstoch~``, ``mirror~``, ``moogvcf~``, ``multy~``, ``oscil_attributes~``, ``oscil~``, ``retroseq~``, ``scrubber~``, ``vdelay~``, ``vpdelay~``.