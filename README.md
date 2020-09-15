# PIC micro computer 16F1705 sample that reads analog inputs and output to UART

This is a project file for MPLAB X IDE x5.40.

Usage:
1. Connect RA0 (Pin13) to serial Rx

2. Connect RA1 (Pin12) to serial Tx

3. Connect GND to serial GND

4. Connect analog input (0v-Vdd) to at least one of the following analog pins

    | Analog ch | Pin name | Physical pin # |
    | :---: | :---: | :---: |
    | A2 | RA2 | Pin 11 |
    | A3 | RA4 | Pin 3 |
    | A4 | RC0 | Pin 10 |
    | A5 | RC1 | Pin 9 |
    | A6 | RC2 | Pin 8 |
    | A7 | RC3 | Pin 7  |

5. The serial port setting of the host is as follows:

    | Setting | Value |
    | :---: | :---: |
    | Speed | 9600 |
    | Data | 8 bit |
    | Parity | None |
    | Stop bit | 1 |
    | Flow ctrl | none |

6. Through the serial line, send one character '2' to '7' to request analog value (an ascii character, rather than a raw value).

7. The chip returns a comma-separated string, which shows the channel number with analog value, concatenated with ':' (ex: 4:625).