    -----------------------------------------------------------------------------

                       --- CAEN SpA - Computing Division ---

    -----------------------------------------------------------------------------

    CAEN HV Wrapper Library Rel. 5.52

    Installation and Use Instructions

    -----------------------------------------------------------------------------

    January 2014

    -----------------------------------------------------------------------------

 This archive contains the last release of the CAEN HV Wrapper Library and the
 corresponding Release Notes.

 The complete documentation can be found in the CAEN HV Wrapper Library Manual
 available once installed the Library or on CAEN's Web Site
 at www.caen.it.



 Content of the archive
 ----------------------

 bin                            :  Directory containing the binary program
                                   of the CAEN HV Wrapper Library
 include                        :  Directory containing the header files
                                   of the CAEN HV Wrapper Library
 lib                            :  Directory containing the library file
                                   of the CAEN HV Wrapper Library
 HVWrapperDemo                  :  Directory containing the source code and
                                   the project of the HVWrapperDemo program
 labview                        :  Directory containing the LabVIEW VIs
                                   of the CAEN HV Wrapper Library
 CAENHVWrapperReadme.txt        :  This file
 CAENHVWrapperReleaseNotes.txt  :  Release Notes of the last software release


 System Requirements
 -------------------

 - Network Interface Card + TCP/IP protocol
   (to control SY 1527/ SY 2527 / SY4527 / SY 5527, NIM /DESKTOP HV, N568E)
 - USB Interface (to control V65xx, NIM /DESKTOP HV, DT55xx HV, N568E)
 - CAENComm library (to controll the V65xx or the DT55xx)
 - A303A/A1303 H.S. CAENET Controller Card (to control SY 527, SY 127, SY 403,
   N 470, N 570 and N568)
 - A128HS SY127 H.S. CAENET Controller installed on SY 127
 - SY 1527/ SY 2527 firmware version 1.10.0 or later (recommended 1.14.03)
 - SY403 firmware version 1.45 or later (recommended 1.46)
 - SY527 firmware version 4.03 or later


 Installation notes
 ------------------

 - Launch the setup program.
 - Follow the instructions of the setup program.
 - Once setup process has finished, the CAENHVWrapper.dll library is
   installed together with sources  and executable of a demo program.


 Note:
 -----
 Control of CAEN Power Supplies via CaeNet link requires the correct
 installation of the A303 and/or A1303 device driver.
 Control of CAEN Power Supplies via USB/OpycalLink link requires the correct
 installation of the USB/A2818 device driver and CAENComm library.

