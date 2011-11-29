## Server to Client

    [type:char][size:int32][message:buffer(size)]

- 'i': info
- 'e': error

## Client to Server

    [type:char][palettes:int32][boxes:int32][parts:int32][part_type:char]

- type: 'o' order
- part_type: 0, 1, 2

---

    [type:char]

- type: 's': stop, 'g': go
