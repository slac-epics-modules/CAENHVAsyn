# Release notes

Release notes for the CAENHVAsyn EPICS Module.

## Releases:
* __R1.0.0__: 2019-09-12 J. Vasquez
  * First stable release.
  * Includes support for parameters of type `PARAM_TYPE_CHSTATUS`, `PARAM_TYPE_BDSTATUS`, and `PARAM_TYPE_BINARY`.
  * Uses template base classes to avoid code duplication.
  * Bug fix: `ZNAM` and `ONAM` label were swapped on bi/bo records.
  * Add support for system parameters of type `SYSPROP_TYPE_REAL`.
  * Other minor bug fixes, and code cleanup.

* __R0.0.0__: 2019-09-06 J. Vasquez
  * First release candidate.