In this protocol we have 5 components:
 - SYNC
 - CMD
 - SIZE
 - PAYLOAD
 - CHECKSUM

 ## SYNC
 It marks the start of the protocol and it is always byte *0x24* (hexadecimal) or 36 (decimal)

 ## CMD
 This is the identification of the operation (command that we want to sent).
 It is one byte and could be:
  | CMD | NAME | Request payload |
  | --- | ---- | --------------- |
  | 0x01 | ATTITUDE | None |
  | 0x02 | IMU | None |
  | 0x03 | ALTITUDE | None |
  | 0x04 | BATTERY | None |
  | 0x05 | STATUS | None |
  | 0x06 | SET_CONTROL | Exactly 8 bytes |
  | 0x07 | GPS | None |

 ## SIZE
 Indicates number of payload bytes. It could be from 0 to 64

 ## PAYLOAD
 It is the data for the command (CMD). This component can be empty

 ## CHECKSUM
 A byte that is used to detect certain transmission erros. The checksum is the biwise XOR of CMD, SIZE and every payload byte. The SYNC byte is exluded.

