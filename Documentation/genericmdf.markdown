Design Document
===============
Project:Ignition Controller \n
Version: v1.00.00 \n

Table of Contents
-----------------

@subpage Description

@subpage TermsAndAbbreviations 

@subpage Resources 

@subpage Exceptions 

@subpage Tests 

@subpage Links 



@page Description
Description 
==============================

# Ignition Controller for 2 Cylinder Bike
Ignition controller powered by STM32F407VGT6 MCU. 
### Implementation 
-	RPM is calculated out of Sensor input from Crank or Cam shaft
-	Firing of cylinders is performed in scheduled manner via FSM handling.
### Architecture Display 
TBD

@page TermsAndAbbreviations
Terms And Abbreviations 
=============================
**Ignition Controller is licensed under the GNU General Public License v3.0**
Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.

####Permissions
-	Commercial use
-	 Modification
-	 Distribution
-	Patent use
-	 Private use
####Limitations
-	 x Liability
-	 x Warranty

@page Resources
Resources
============================
**RAM Consumption**
- 1.79kB used out of 128kB

**ROM Consumption**

- 17.51kB used out of 1024kB 

@page Exceptions
Exception and Error Handling
============================
If error occurs error handler will put MCU in infinite loop and application will not function.

@page Tests
Tests 
============================


@page Links 
**Links**
-  Link to the repo is [Ignition Controller](https://github.com/MiroslavMitrovic/IgnitionController_STM32.git).

============================

