# Overview

The Renesas Flash Programmer (hereafter referred to as the RFP) is software that uses an E1 emulator (hereafter referred to as the E1), E20 emulator (hereafter referred to as the E20), E2 emulator (hereafter referred to as the E2), E2 emulator Lite (hereafter referred to as the E2 Lite), or J-Link Debug Probe  (hereafter referred to as the J-Link) via a serial, USB or SWD interface to erase, write, and verify programs on a target system on which a Renesas Electronics MCU with on-chip flash memory is mounted.

This document describes the command line options for manipulating the RFP on Linux, Windows and macOS.
## Supported Operating Systems
* Linux (Ubuntu 22.04 LTS, x64/ARM32/ARM64)
* Linux (Ubuntu 24.04 LTS, x64/ARM64)
* Windows 10 (32-bit and 64-bit)
* Windows 11
* macOS 14 Sonoma (Apple Silicon)
* macOS 15 Sequoia (Apple Silicon)

## Operating Environment
This application require the following library, but it is already installed with macOS.
* libusb-1.0-0

This application uses .NET 8. 
.NET 8 libraries are included in this application, but additional libraries may be required.  
Refer to the following URL for details.  
https://docs.microsoft.com/dotnet/core/install/linux

## Restrictions
macOS does not support boot mode with the USB interface of the RA family.  
Linux and macOS does not support an E1 emulator, E20 emulator, and USB Direct interface.  
The UART connection via the serial port under macOS supports baud rates of up to 230400 bps.

## Installation
### To use the Renesas emulator on Linux (udev rules)
1. Type `sudo cp 99-renesas-emu.rules /etc/udev/rules.d/`
1. Type `sudo udevadm control --reload-rules` or `service udev restart`
1. Connect the emulator tool to your PC

## Command Line
The rfp-cli command makes control from a command line possible.

## Exit Code 
When the operation was successful, exit code 0 is returned.
Otherwise, exit code 1 is returned.

## Command-line Syntax 
`rfp-cli [option...] [hexfile...]`

Option names are prefixed by a hyphen (-) or a slash (/).

# Options for Help
Note that options in this group have higher priority than other options and stop processing successfully when the display is completed.

## -version, -ver
Shows the version messages.

## -help, -h, -?
Shows messages on usage.

## -list-devices, -ld 
Shows a list of supported devices.

## -list-tools, -lt 
Shows a list of connected tools.  
To use this option, the `-device` option must also be specified.

## -list-ports, -lp 
Shows a list of connected COM ports.  
To use this option, the `-device` option must also be specified.

## -list-interfaces, -li 
Shows a list of communications interfaces.  
To use this option, the `-device` option and the `-tool` or `-port` option must also be specified.

## -list-speeds, -ls 
Shows a list of supported communications speeds.  
To use this option, the `-device` option must also be specified.  
This option requires a connection between the RFP and the device.

## -list-flashoptions, -lfo 
Shows supported flash options.  
To use this option, the `-device` option must also be specified.  
This option requires a connection between the RFP and the device.

# Options for Connection

## -device \<name>, -d \<name>
Selects a device type.  

Example:
```
rfp-cli -d RA
```

### \<name>  
Specifies a device type string. If the device name includes spaces, enclose the string in double-quotation marks.  
The device type can be obtained with the `-list-devices` option.  

Refer to the list of supported devices for the type to be specified as the device name.  
This option is always required, except with some show options.

## -tool \<type>[:\<serial>], -t \<type>[:\<serial>]
Selects the emulator hardware and the serial number.  
If this option is omitted, the `-port` option is always required, except with some show options.

### \<type>
Select the type from the following list.
|Type|Meaning|
|---|---|
|e1|E1 emulator (Windows only)|
|e20|E20 emulator (Windows only)|
|e2|E2 emulator|
|e2l|E2 emulator Lite|
|jlink|J-Link|
|usb|USB Direct (Windows only)|

### \<serial> (Optional)  
Specifies all or part of the serial number of the connected hardware.  
If this option is omitted, the first tool to be found is connected to the RFP.

## -port \<name>
Selects the serial port (COM port) for communication.  
If this option is omitted, the `-tool` option is always required, except with some show options.

Example:
```
rfp-cli -port COM0
rfp-cli -port /dev/ttyS0
```

## -interface \<type>, -if \<type>
Selects the communications interface.  
If this option is not specified, a value is automatically selected.

Example:
```
rfp-cli -if uart1
```

### \<type>
Select the type from the following list.
|Type|Meaning|
|---|---|
|uart1|1 wire UART|
|uart|2 wire UART|
|fine|FINE|
|csi|CSI|
|swd|SWD (*1)|

\*1)  
For the SWD interface, some functions are not available for some devices.  
For details, refer to Chapter 5, Points for Caution, in the Renesas Flash Programmer User's Manual. 


## -speed \<num>[K|M], -s \<num>[K|M]
Specifies the baud rate or communications speed.  
If this option is not specified, a value is automatically selected.

Example:
```
rfp-cli -s 9600
rfp-cli -s 1.5M
```

### \<num>
Specifies the baud rate [bps] or communications speed [Hz].  

## -voltage \<num>, -vo \<num>
Enables the supply of power.  
To use this option, the `-tool` option must also be specified.  
If this option is not specified, the output power is disabled and an external power supply is used.

Example:
```
rfp-cli -vo 3.3
```

### \<num>
Specifies the output voltage [V].  

## -widevoltage, -wv
Enables the wide voltage mode of an RL78 device that has this function.  
If it does not, this option is ignored.

## -iomode \<mode>
Selects the setting of the tool mode at device connection.  
To use this option, the `-tool` option must also be specified.

### \<mode>
Select the mode from the following list.
|Mode|Description|
|---|---|
|auto|Sets mode pins automatically (default).
|manual|If the `-io` option is not specified for all pins, pins not specified are in the hi-Z state.

## -io\<n> \<signal>
Sets mode pins manually.  
This option can be specified more than once.  
To use this option, the `-tool` and `-iomode` options must also be specified.  
The RFP ignores this option if the `-iomode` option is set for automatic mode.  

Each mode pin is in the hi-Z state by default.

Example:
```
rfp-cli -io0 high
```

### \<n>
Selects the mode pin number (0 to 5).  
For pin assignments of io0 to io5 for the E1, E20, E2, and E2 Lite, refer to the following URL for details. 
https://www.renesas.com/document/mat/pg-fp6-renesas-flash-programmer-additional-document-users-manual-recommended-circuits-connecting 


### \<signal>
Select the signal from the following list.  
|Signal|Meaning|
|---|---|
|low|Driven low|
|high|Driven high|

## -run
Releases the reset signal and causes the target device to run after disconnection. This option applies only if the operation was successful. In case of failure, this option is treated as the `-reset` option.  
If both the `-run` and `-reset` options are specified, the last option to have been specified is used.

## -reset
Resets the target device after disconnection. This option is enabled by default.  
If both the `-run` and `-reset` options are specified, the last option to have been specified is used.

## -dtr
Uses the DTR signal as the reset signal for the COM port.  
If both the -dtr and -dtr-inv options are specified, the last option to have been specified is used.  
To use this option, the `-port` option must also be specified.  

There is no reset signal on the COM port (default).

## -dtr-inv
Uses the DTR signal as the reset signal for the COM port (inverted reset signal).  
If both the "-dtr" and "-dtr-inv" options are specified, the last option to have been specified is used.  
To use this option, the `-port` option must also be specified.  

There is no reset signal on the COM port (default).

## -rts
Uses the RTS signal as the reset signal for the COM port.  
If both the "-rts" and "-rts-inv" options are specified, the last option to have been specified is used.  
To use this option, the `-port` option must also be specified.  

There is no reset signal on the COM port (default).

## -rts-inv
Uses the RTS signal as the reset signal for the COM port (inverted reset signal).  
If both the "-rts" and "-rts-inv" options are specified, the last option to have been specified is used.  
To use this option, the `-port` option must also be specified.  

There is no reset signal on the COM port (default).

## -osc \<freq>
Specifies the frequency of the main clock.  
This option is only required for some devices (e.g. RH850).  
The RFP ignores this option, if the target device does not require a main clock setting.  
If this option is not specified for a device that requires main clock configuration, a console prompt will be displayed.

Example:
```
rfp-cli -osc 16.0
```

### \<freq>
Specifies the main clock frequency as a decimal number in MHz.

## -auth \<type> \<code>
Specifies authentication codes.  
This option can be specified more than once.  
The RFP ignores this option, if the target device does not require an authentication code.  
If this option is not specified for a device that requires authentication, a console prompt will be displayed.

Example:
```
rfp-cli -auth id 0123456789ABCDEF
```

### \<type>
Select the type from the following list.  
|Type|Meaning|
|---|---|
|id|ID code|
|cfpw|Code Flash Access Password|
|dfpw|Data Flash Access Password|
|oid|OCD ID|
|cid|Customer ID|
|cida|Customer ID A|
|cidb|Customer ID B|
|cidc|Customer ID C|
|ctid|C-Test ID|
|sifid|RHSIF ID|
|dfid|Data Flash ID|
|seckey|SECDBG Key|
|nonseckey|NONSECDBG Key|
|rmakey|RMA Key|
|al2key|AL2 Key|
|al1key|AL1 Key|

### \<code>
Specifies the authentication code in hexadecimal.

## -endian \<endian>
Selects the endian of a bi-endian device.

### \<endian>
Select the endian from the following list.  
|Endian|Meaning|
|---|---|
|little|Little-endian (default)|
|big|Big-endian|

## -svr-override
Override the SVR parameters using the parameters in the program file.  
For the "-svr-override" and "-svr-disable" options, the option specified last is used.  
If the target device does not support this function, this option is ignored.

## -svr-disable
Forcibly disable the SVR function.  
For the "-svr-override" and "-svr-disable" options, the option specified last is used.  
If the target device does not support this function, this option is ignored.

# Options for the Target Area
Note that the specifications are made in the order of `-fill`, `-range`, and `-range-exclude`.

## -range \<start addr>,\<end addr>
Specifies the target address range.  
This option can be specified more than once.  
The `-range-exclude` option takes priority over the `-range` option.

The whole flash address range is specified by default.

### \<start addr>
Specifies the start address of the target range in hexadecimal.

### \<end addr>
Specifies the end address of the target range in hexadecimal.

## -range-exclude \<start addr>,\<end addr>
Specifies the non-target address range.  
This option can be specified more than once.  
The `-range-exclude` option takes priority over the `-range` option.

### \<start addr>
Specifies the start address of the non-target range in hexadecimal.

### \<end addr>
Specifies the end address of the non-target range in hexadecimal.

## -fill \<area>
Fills the empty space with 0xFF when writing to the device.  
The `-range` and `-range-exclude` options take priority over the `-fill` option.

### \<area>
Select the area from the following list.  
|Area|Description|
|---|---|
|all|Fills code flash, user boot and data flash.|
|code|Fills code flash and user boot.|
|data|Fills data flash.|

# Options for Data
Note that files and data are applied in the order of "-file", "-bin", and "-data".

## [-file] \<hex file>
Loads and uses a specified hex file for writing to and verification in the device.  
This option can be specified more than once, and the option name can be omitted.  
Files cannot be specified with data for the same addresses.

Example:
```
rfp-cli data1.mot data2.mot
```

### \<hex file>
File path. If the file path includes spaces, enclose the string in double-quotation marks.  
The following file formats or encrypted files (RPE files) in these formats can be specified.  
\- Intel Hex  
\- Motorola S-Record  
\- RPI file (Renesas Flash Programmer Image File) (*1)  
\- HCUHEX (*1)  
\- SFP file (Secure Factory Programming File) (*1, *2)  

\*1) If this file is specified, the following restrictions apply.  
\- The following options cannot be specified:  
`-range`, `-range-exclude`, and `-flashoption`  
\- Multiple files cannot be specified with this option.

\*2) If this file is specified, the following restrictions apply.  
\- The following options cannot be specified:  
`-verify` and `-fill`

## -file-offset \<offset> \<hex file>
Add the specified offset value when reading a hex file.

### \<offset>
Offset value to be added (hexadecimal).

### \<hex file>
File path. If the file path includes spaces, enclose the string in double-quotation marks.  
The following file formats can be specified.  
\- Intel Hex  
\- Motorola S-Record

## -bin \<addr> \<file>
Loads and uses a specified binary file for writing to and verification in the device.  
This option can be specified more than once.  
This option is processed after the "-file" option, and all data in the given range are overwritten.

Example:
```
rfp-cli -bin FF200000 data.bin
```

### \<addr>
Flash memory address (hexadecimal).

### \<file>
File path. If the file path includes spaces, enclose the string in double-quotation marks.

## -data \<addr> \<data>
Uses a specified data for writing to and verification in the device.  
This option can be specified more than once.  
This option is processed after `-file` and `-bin` options, and all data in the given range are  overwritten.

Example:
```
rfp-cli -data FF200000 0123456789ABCDEF
```

### \<addr>
Flash memory address (hexadecimal).

### \<data>
Data (hexadecimal).

## -rpe-password \<password>
Specifies a file password for opening an RPE file.

### \<password>
Specifies a password string.  
If the password includes symbols, enclose the string in double-quotation marks.

## -userkey \<addr> \<file>
Loads and uses a specified key file as the TSIP user key for writing to and verification in the device.  
This option can be specified more than once.  
This option can only be specified if the device supports this function. For more information, refer to the user's manual of the target device.

### \<addr>
Flash memory address (hexadecimal).

### \<file>
Renesas key file path. If the file path includes spaces, enclose the string in double-quotation marks.  
The key file can be created by the Security Key Management Tool.

## -flashoption \<type> \<data>, -fo \<type> \<data>
Uses a specified device flash options for writing to and verification in the device.  
This option can be specified more than once.  
Only options supported by the target device can be specified.

### \<type>
Refer to the "Flash options list" section.

### \<data>
Refer to the "Flash options list" section.

# Options for Flash Action
Note that specifying an option that is not supported by the device leads to an error.  
Note that these actions cannot be performed at the same time as those in from other groups.

## -auto, -a
Erases, writes, and verifies flash memory in the device.  
This option has the same effect as specifying `-erase`, `-program`, and `-verify`.

## -pv
Writes and verifies flash memory in the device.  
This option has the same effect as specifying `-program` and `-verify`.

## -erase, -e
Erases flash memory of the device.  
The range options determine the range for erasure.  
If the target device does not support this function, this option is ignored.

## -program, -p
Erases the range for writing to the device and writes to the device.  
The specified hex file and range options determine the ranges for erasure and writing.  

The following options can also be used to write data:  
`-file`, `-bin`, `-data`, `-flashoption`, and `-userkey`

## -verify, -v
Verifies the data that have been written to the device.  
The range for verification is the same as that for the `-program` option.

The following options can be used to restrict the range of verification:  
`-noverify-id` and `-noverify-fo`  
If the target device does not support this function, this option is ignored.

## -sig
Shows the device signature.

## -blankcheck
Checks if the flash memory of the device is blank and outputs the result to the console.  
The range options determine the range for blank checking.  
The `-blankcheck-mode` option can be used to stop processing depending on the result.

## -checksum, -c
Shows the checksum of the flash memory in the device.  
The range options determine the checksum range.  
If the device supports multiple checksum algorithms, use the `-crc` or `-checksum-type` option.  
To calculate the checksum of a file, specify the `-checksum-file` option.

## -checksum-file, -cf
Shows the flash memory checksum of a file.  
The range for calculation and algorithm are the same as those for the `-checksum` option.

## -checksum-type \<type>
Uses the specified checksum algorithm.  
If the target device does not support the specified algorithm, this option is ignored.

### \<type>
Selects the type from the following list.  
|Type|Meaning|
|---|---|
|auto|Set the type automatically (default).|
|crc|CRC method (*1)|
|add16|16bit additive method (*2)|

\*1) This type has the same effect as specifying the `-crc` option.   
\*2) This type is supported for the RL78 family (excluding the RL78/G10, G1M, G1N, G15, and G16).

## -crc
Uses the CRC algorithm in the checksum command.  
If the target device does not support this function, this option is ignored.

## -write-rpi \<file>
Writes data to an RFP image file (RPI file).  
The data for writing are the same as for the `-program` option.  
If the target file already exists, it is overwritten.    
This operation requires a connection to the device.  
This option is not used when the image file is to be loaded.

### \<file>
Output file path. If the file path includes spaces, enclose the string in double-quotation marks.

## -output-file \<type> \<file>
This option will merge the specified user data and output them as a file.   
If the target file already exists, it is overwritten.  

The differences from the `-write-rpi` option are as follows:  
- No connection to the device is required for this operation.
- This option does not allow the `-fill` option to be specified.
- Even in the minimum unit of programming by the MCU, filling of 0xFF is not performed. 
- The address range is not checked.

### \<type>
Select the type from the following list.  
|Type|Meaning|
|---|---|
|srec|Motorola S-Record|
|hex|Intel Hex|
|rpi|RPI file|

### \<file>
Output file path. If the file path includes spaces, enclose the string in double-quotation marks.

## -blankcheck-mode \<mode>
Stops processing before erasure according to the result of a blankcheck.  
When processing is stopped, exit code 1 is returned.

### \<mode>
Select the mode from the following list.  
|Mode|Description|
|---|---|
|none|Shows the result only (default).|
|blank|Shows the result and stops processing when the result is not blank.|
|notblank|Shows the result and stops processing when the result is blank.|

## -verifybytransfer
Uses the retransfer verification method.  
If the target device does not support this function, this option is ignored.

## -noerase
Skips erasing of the device.

## -noverify-id
Skips verifying the device ID code.

## -noverify-fo
Skips verifying the device flash options.

## -nocheck-range
Processing is not stopped if the specified hex file exceeds the device's memory range.

## -read-flashoptions, -rfo
Reads flash options from the device and outputs the data that have been read to the console.  
No other options for flash memory operation can be specified at the same time as this read option.

## -read \<file>, -r \<file>
Reads all flash memory data from the device and outputs the data that have been read to the file.  
If the target file already exists, it is overwritten.  
No other options for flash memory operation can be specified at the same time as this read option.

This option does not support the RL78 family.

### \<file>
Output file path. If the file path includes spaces, enclose the string in double-quotation marks.

## -read-bin \<addr> \<size> \<file>, -rb \<addr> \<size> \<file>
Reads flash memory data within the specified range from the device and outputs the data that have been read to the file.  
If the target file already exists, it is overwritten.  
No other options for flash memory operation can be specified at the same time as this read option.

This option does not support the RL78 family.

### \<addr>
Flash memory address (hexadecimal).

### \<size>
Read size [byte] (decimal).

### \<file>
Output file path. If the file path includes spaces, enclose the string in double-quotation marks.

## -read-view \<addr> \<size>, -rv  \<addr> \<size>
Reads flash memory data within the specified range from the device and outputs the data that have been read to the console.  
No other options for flash memory operation can be specified at the same time as this read option.

This option does not support the RL78 family.

### \<addr>
Flash memory address (hexadecimal).

### \<size>
Read size [byte] (decimal, up to 4096).

## -format \<type>
Selects the file format for the `-read` option.

### \<type>
Select the type from the following list.  
|Type|Meaning|
|---|---|
|srec|Motorola S-Record (default)|
|hex|Intel Hex|

## -view-size \<size>
Selects the view size format for the `-read-view` option.  
If the size is 2 or 4, the endian of the displayed data depends on the `-endian` option. If the `-endian` option is not specified, the data will be displayed as little endian.

### \<size>
Select the size from the following list.  
|Size|Description|
|---|---|
|1|Displays data in 1-byte units (default).|
|2|Displays data in 2-byte units.|
|4|Displays data in 4-byte units.|

## -skip-blankread
Skips reading of blank areas in reading selected by the `-read` option.

## -erase-chip
Erases all data in the flash memory of the device and clears the configuration settings.  
If the device supports an initialization function, this option will also execute the initialization command. No other options for flash memory operation can be specified at the same time as this option.

**Caution:**  
This processing does not restore the device to its state at shipment. If correct settings are not programmed for the flash options after the memory in the chip has been erased, the device will not operate.

- For RH850 family products    
When a chip is erased, the configuration settings are cleared after all other data have been erased. In other words, the optional settings of the device are all erased. Since all settings, including the settings at the time of shipment, are erased at this time, be sure to make the required settings at the same time.

## -dlm \<state>
Causes a transition to the specified DLM state.  
If the transition requires authentication, the console prompt will be displayed. The authentication code can be specified at the prompt with the `-auth` option.  
No other options for flash memory operation can be specified at the same time as this option.

### \<state>
Select the state from the following list.  
|State|Meaning|
|---|---|
|SSD|SSD state|
|NSECSD|NSECSD state|
|DPL|DPL state|
|LCK_DBG|LCK_DBG state|
|LCK_BOOT|LCK_BOOT state|
|RMA_REQ|RMA_REQ state|
|OEM_PL2|OEM(PL2) state|
|OEM_PL1|OEM(PL1) state|
|OEM_PL0|OEM(PL0) state|

## -use-uid
Uses the unique ID for authenticating a DLM transition.  
This option can be used in the RMA_REQ state.

## -write32 \<addr> \<data>[,\<data>...]
Writes additional data to the device in 32-bit units.  
This option overwrites data read from the device with the specified data and writes the result to the device.  
This option can be specified more than once and can be used with the `-writebit` option.  
If the endian is not specified, little endian will be used.  
No other options for flash memory operation can be specified at the same time as this read-modify-write option.

This option does not support the RL78 family.

Example:
```
rfp-cli -write32 FF200000 01020304,05060708
```

### \<addr>
Flash memory address (hexadecimal).

### \<data>
4-byte data to be written (hexadecimal).

## -writebit \<addr> \<pos> \<bitdata>
Writes additional data to the device in 1-bit units.  
This option overwrites data read from the device with the specified data and writes the result to the device.  
This option can be specified more than once and can be used with the `-write32` option.  
If the endian is not specified, little endian will be used.  
No other options for flash memory operation can be specified at the same time as this read-modify-write option.

This option does not support the RL78 family.

Example:
```
rfp-cli -writebit FF200000 15 1010101010101010
```

### \<addr>
Flash memory address (hexadecimal).

### \<pos>
Start bit number (decimal, 0 to 31). For 4-byte units of data, the most significant bit is 31 and the least significant bit is 0.

### \<bitdata>
Data to be written (binary). Write the bit data in descending order from the specified start bit number to the least significant bit (up to 32 characters are specifiable).  

## -key-password \<password>
Specifies the key password in hexadecimal.  
To use this option, the `-mac-password` option must also be specified.

## -mac-password \<password> 
Specifies the mac password in hexadecimal.  
To use this option, the `-key-password` option must also be specified.

## -create-write-header
Create and write the hex data with a Product Header and Image Header.

## -noquery
Suppresses the authentication code and the OSC console prompt.

## -log \<file>
Saves a log in a file.  
If the specified file already exists, the log is appended to the existing contents of the file.

### \<file>
File path. If the file path includes spaces, enclose the string in double-quotation marks.

## -nologo
Suppresses the display of the header message.

## -noprogress
Suppresses the display of the progress of processing.

# List of Flash Options
If an address range on which an operation is not possible is included, an error message is displayed.   
The indicated error will be a pre-check result or a boot firmware error.

## Lock-bit
### -fo `lb` \<start addr>,\<end addr>[,\<start addr>,\<end addr>...]  

\<start addr>  
Start address of flash memory blocks (hexadecimal).

\<end addr>  
End address of flash memory blocks (hexadecimal).

## OTP
### -fo `otp` \<start addr>,\<end addr>[,\<start addr>,\<end addr>...]

\<start addr>  
Start address of flash memory blocks (hexadecimal).

\<end addr>  
End address of flash memory blocks (hexadecimal).

## Access Window (Flash Shield Window)
### -fo `aw` \<start addr>,\<end addr>  
### -fo `aw-flags` \<flag>[,\<flag>...]

\<start addr>  
Start address of flash memory blocks (hexadecimal).

\<end addr>  
End address of flash memory blocks (hexadecimal).

\<flag>  
The `aw-flags` type option has to be specified with the `aw` type option.
This option cannot be used to clear flags. Some flags can be released with the `erase-chip` option.

Select the flag from the following list.  
|Flag|Description|
|---|---|
|inside|Protects memory within the range instead of outside the range.|
|protect|Prohibits rewriting of the access window.|

## Flash Read Protection
### -fo `rp` \<start addr>,\<end addr>
### -fo `rp-flags` \<flag>[,\<flag>...]

\<start addr>  
Start address of flash memory blocks (hexadecimal).

\<end addr>  
End address of flash memory blocks (hexadecimal).

\<flag>  
The `rp-flags` type option has to be specified with the `rp` type option.
This option cannot be used to clear flags. Some flags can be released with the `erase-chip` option.

If all blocks are readable and only flags are set, set <start address> and <end address> to the same value. (e.g. -fo rp 0,0 -fo rp-flags protect)

Select the flag from the following list.  
|Flag|Description|
|---|---|
|protect|Prohibits rewriting of the flash read protection.|

## Option Bytes
### -fo `opbt` \<opbt0>,\<opbt1>,...,\<opbt7>
OPBT0 to OPBT7 can be specified.  
Since writing to only some option bytes is not possible, write to all existing OPBTs.  
The RFP ignores non-existent OPBTs (0xFFFFFFFF is specified).

\<opbt>  
OPBT data (hexadecimal). (bit31 ... 0)

## Extended Option Bytes
### -fo `opbtex` \<opbt8>[,\<opbt9>,...,\<opbt15>]
OPBT8 to OPBT15 can be specified.  
Since writing to only some option bytes is not possible, write to all existing OPBTs.  
The RFP ignores non-existent OPBTs (0xFFFFFFFF is specified).

\<opbt>
OPBT data (hexadecimal). (bit31 ... 0)

## DLM State
### -fo `state` \<state>

\<state>  
This type of state transition does not allow authentication of the transition. If authentication is required, use the `-dlm` option alone.  
Select the state from the following list.  
|State|Meaning|
|---|---|
|SSD|SSD state|
|NSECSD|NSECSD state|
|DPL|DPL state|
|LCK_DBG|LCK_DBG state|
|LCK_BOOT|LCK_BOOT state|
|OEM_PL2|OEM_PL2 state|
|OEM_PL1|OEM_PL1 state|
|OEM_PL0|OEM_PL0 state|

## DLM Keys
### -fo `seckey` \<file>
### -fo `nonseckey` \<file>
### -fo `rmakey` \<file>
### -fo `al2key` \<file>
### -fo `al1key` \<file>

\<file>  
Renesas key file path. If the file path includes spaces, enclose the string in double-quotation marks.  
The key file can be created by the Security Key Management Tool.

## Boundary
### -fo `boundary` \<cs>,\<cnsc>,\<ds>,\<srs>,\<srnsc>
### -fo `boundary` \<cs>,\<ds>

\<cs>  
Size of Code Secure [KB] (decimal).

\<cnsc>  
Size of Code Non-Secure Callable [KB] (decimal).

\<ds>  
Size of Data Secure [KB] (decimal).

\<srs>  
Size of SRAM Secure [KB] (decimal).

\<srnsc>  
Size of SRAM Non-Secure Callable [KB] (decimal).

### -fo `boundary-file` \<file>

\<file>  
Renesas Partition Data file path. If the file path includes spaces, enclose the string in double-quotation marks.

## Security Flags
### -fo `flags` \<flag>[,\<flag>...]
This option cannot clear the flags. Some flags can be released with the `erase-chip` option.

\<flag>  
Select the flag from the following list.  
|Flag|Meaning|
|---|---|
|id|Enable ID Code Authentication|
|e|Disable Block Erase|
|p|Disable Program|
|r|Disable Read|
|b|Disable Rewriting boot cluster|
|ce|Disable Initialize Command|
|con|Disable Serial Programming<br>Disable Debugger and Serial Programming|
|icus|Enable ICU-S|
|t|Disable Test Mode|
|lckb|Disable LCK_BOOT|
|al2|Disable AL2 authentication|
|al1|Disable AL1 authentication|

#### Notes
- When specifying `b` in a device with variable boot swapping, be sure to specify BTBLS at the same time.

## Lock bit for Configuration Data
### -fo `optlb` \<lockbits>

\<lockbits>  
Specify 18-byte data concatenated with the following option setting memory data (hexadecimal).  

\- CFGD0LOCK (Configuration Data 0 Lock bit)  
\- CFGD1LOCK (Configuration Data 1 Lock bit)  
\- CFGD2LOCK (Configuration Data 2 Lock bit)  

Example:
```
CFGD0LOCK: 0001020304050607  
CFGD1LOCK: 08090A0B0C0D0E0F  
CFGD2LOCK: 1011  

-fo optlb 000102030405060708090A0B0C0D0E0F1011
```

## Anti-Rollback Counter Configuration
### -fo `arcc` \<arcc_data>

\<arcc_data>  
Specify 4-byte data concatenated with the following option setting memory data (hexadecimal). 

\- ARCCS (Anti-Rollback Counter Configuration Setting for Non-secure Application)  
\- ARCLS (Anti-Rollback Counter Lock Setting)  

Example:
```
ARCCS: 0102  
ARCLS: 0304  

-fo arcc 01020304
```

## OEM root public key
### -fo `oemrootkey0` \<file>
### -fo `oemrootkey1` \<file>
### -fo `oemrootkey2` \<file>
### -fo `oemrootkey3` \<file>
### -fo `oemrootkey-flags` \<flag>[,\<flag>...]

\<file>  
Renesas key file path. If the file path includes spaces, enclose the string in double-quotation marks.  
The key file can be created by the Security Key Management Tool.

\<flag>  
Select the flag from the following list.  
|Flag|Description|
|---|---|
|protect|Prohibits rewriting of oemrootkey0.|

## Certificate
### -fo `cert-code` \<file>
### -fo `cert-key` \<file>

\<file>  
Code certificate file and Key certificate file.  

## ID Code Setting
### -fo `id` \<code>  

All-0xFF code. (default)

\<code>  
Specifies the authentication code in hexadecimal.

## CFPW Setting
### -fo `cfpw` \<code>  

All-0xFF code. (default)

\<code>  
Specifies the authentication code in hexadecimal.

## DFPW Setting
### -fo `dfpw` \<code>  

All-0xFF code. (default)

\<code>  
Specifies the authentication code in hexadecimal.

## Extra Option
### -fo ex \<data>
### -fo ex-flags \<flag>[,\<flag>...]
The `ex-flags` type option has to be specified with the `ex` type option.  
This option cannot clear the flags. Some flags can be released with the `erase-chip` option.

\<data>  
Extra data (hexadecimal).

\<flag>  
Select the flag from the following list.  
|Flag|Description|
|---|---|
|protect|Prohibits rewriting of extra options.|

## BTBLS
### -fo `btbls` \<btbls>
### -fo `btbls-flags` \<flag>[,\<flag>...]
 
Specify the value of BTBLS[3:0] for the setting of the boot cluster size in an RL78 device.

\<btbls>  
Specify 1-byte data for BTBLS in hexadecimal. The four higher-order bits are ignored when writing data.

\<flag>  
The `btbls-flags` type option has to be specified with the `btbls` type option.

When the "btbls" option has been set, this flag is set as "protect" by default.  
Therefore, this flag does not usually require specification.
 
Select the flag from the following list. 
|Flag|Description|
|---|---|
|none|No protection. (BAPR = 1)|
|protect|Prohibits rewriting of BTBLS. (BAPR = 0) (default)|
 
Example:
```
-fo btbls 05
```

## CPU Settings
### -fo `cpuflags` \<flag>[,\<flag>...]
 
\<flag> 
Select the flag from the following list. 
|Flag|Description|
|---|---|
|cpu1|Change master CPU from CPU0 to CPU1.|
|nosecex|Disable security extension for CPU1.|

# Options for External Flash

## -external-loader \<name>
Enables external flash programming and loading of an external flash loader file.

\<name>  
Specify the Name key string. The Name key can be obtained with the `-list-external-loader` option.

## -show-external-loader \<name>
Shows detailed information on the settings of the external loader.

\<name>  
Specify the Name key string. The Name key can be obtained with the `-list-external-loader` option.

## -list-external-loader
Displays a list of name keys for use in setting the external loader.